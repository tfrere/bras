var five = require('johnny-five'),
    webSocket = require('ws'),
    ws = new webSocket('ws://127.0.0.1:6437'),
    board = new five.Board(),
    LeapFrame = require('./lib/leapFrame'),
    Joint = require('./lib/joint'),
    frame, i = 0;

board.on('ready', function() {

  var finger1 = new Joint({
    minPos: 0,
    maxPos: 180,
    pin: 10,
    range: [0,180]
  });

  var finger2 = new Joint({
    minPos: 0,
    maxPos: 180,
    pin: 5,
    range: [0,180]
  });

  var finger3 = new Joint({
    minPos: 0,
    maxPos: 180,
    pin: 3,
    range: [0,180]
  });

  var finger4 = new Joint({
    minPos: 0,
    maxPos: 180,
    pin: 6,
    range: [0,180]
  });

  var finger5 = new Joint({
    minPos: 0,
    maxPos: 180,
    pin: 9,
    range: [0,180]
  });

  ws.on('message', function(data, flags) {
    i++;
    // track only 40frame / s
    if (i%3 === 0) {
      frame = new LeapFrame(data);
      if(frame.valid) {
          finger1.move(Math.round(frame.fingerAngleX[0]));
          finger2.move(Math.round(frame.fingerAngleX[1]));
          finger3.move(Math.round(frame.fingerAngleX[2]));
          finger4.move(Math.round(frame.fingerAngleX[3]));
          finger5.move(Math.round(frame.fingerAngleX[4]));
      }
      i = 0;
    }
  });
});