import Cylon from "cylon";
import LeapFrame from "./lib/LeapFrame.js";

const convertRange = (value, r1, r2) => {
  value = ((value - r1[0]) * (r2[1] - r2[0])) / (r1[1] - r1[0]) + r2[0];
  return (value * 1000) / 1000;
};

Cylon.robot({
  connections: {
    leapmotion: { adaptor: "leapmotion" },
    arduino: { adaptor: "firmata", port: "/dev/cu.usbmodem145301" },
  },

  devices: {
    leapmotion: { driver: "leapmotion" },
    servo1: { driver: "servo", pin: 3, connection: "arduino" },
    servo2: { driver: "servo", pin: 5, connection: "arduino" },
    servo3: { driver: "servo", pin: 6, connection: "arduino" },
    servo4: { driver: "servo", pin: 9, connection: "arduino" },
    servo5: { driver: "servo", pin: 10, connection: "arduino" },
  },

  work: function (my) {
    my.leapmotion.on("hand", function (payload) {
      let frame = new LeapFrame(payload);
      const positions = frame.run();
      console.clear();
      console.log("angles", positions);
      my.servo1.angle(convertRange(positions[0], [0, 180], [0, 135]));
      my.servo2.angle(convertRange(positions[1], [0, 180], [0, 135]));
      my.servo3.angle(convertRange(positions[2], [0, 180], [0, 135]));
      my.servo4.angle(convertRange(positions[3], [0, 180], [0, 135]));
      my.servo5.angle(convertRange(positions[4], [0, 180], [0, 135]));
    });
  },
}).start();
