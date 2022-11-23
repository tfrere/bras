import Cylon from "cylon";
import LeapFrame from "./lib/LeapFrame.js";

const convertRange = (value, r1, r2) => {
  value = ((value - r1[0]) * (r2[1] - r2[0])) / (r1[1] - r1[0]) + r2[0];
  return value;
};

const LEAPMOTION_FINGER_ANGLE_RANGE = [0, 120];
const SERVO_MOTOR_ANGLE_RANGE = [0, 270];

Cylon.robot({
  connections: {
    leapmotion: { adaptor: "leapmotion" },
    arduino: { adaptor: "firmata", port: "/dev/cu.usbmodem145101" },
  },

  devices: {
    leapmotion: { driver: "leapmotion" },
    servo1: {
      driver: "servo",
      pin: 3,
      connection: "arduino",
      range: {
        min: 0,
        max: 270,
      },
    },
    servo2: {
      driver: "servo",
      pin: 5,
      connection: "arduino",
      range: {
        min: 0,
        max: 270,
      },
    },
    servo3: {
      driver: "servo",
      pin: 6,
      connection: "arduino",
      range: {
        min: 0,
        max: 270,
      },
    },
    servo4: {
      driver: "servo",
      pin: 9,
      connection: "arduino",
      range: {
        min: 0,
        max: 270,
      },
    },
    servo5: {
      driver: "servo",
      pin: 10,
      connection: "arduino",
      range: {
        min: 0,
        max: 270,
      },
    },
  },

  work: function (my) {
    let fingers = [my.servo1, my.servo2, my.servo3, my.servo4, my.servo5];

    fingers.forEach((finger, index) => {
      finger.angle(0);
    });

    // When no hands detected : Set all servos to position 0
    my.leapmotion.on("frame", function (payload) {
      if (payload.hands.length < 1) {
        console.clear();
        console.log("No hands detected");
        fingers.forEach((finger, index) => {
          finger.angle(0);
        });
      }
    });

    // When one hand is detected : Do stuff
    my.leapmotion.on("hand", function (payload) {
      let frame = new LeapFrame(payload);
      let positions = frame.run();

      console.clear();
      fingers.forEach((finger, index) => {
        console.log(
          `Finger ${index} - leap-angle : ${
            positions[index]
          } | motor-angle : ${convertRange(
            positions[index],
            LEAPMOTION_FINGER_ANGLE_RANGE,
            SERVO_MOTOR_ANGLE_RANGE
          )}`
        );
        finger.angle(
          convertRange(
            positions[index],
            LEAPMOTION_FINGER_ANGLE_RANGE,
            SERVO_MOTOR_ANGLE_RANGE
          )
        );
      });
    });
  },
}).start();
