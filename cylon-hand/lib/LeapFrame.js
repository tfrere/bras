/**
 * Calculate the angle between 2 vectors in degrees
 * @param {Array} v1 - coordinates of the first vector
 * @param {Array} v2 - coordinates of the second vector
 * @return the angle in degrees
 */
const vectorAngle = function (v1, v2) {
  const vectorProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  const v1Norm = Math.sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
  const v2Norm = Math.sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
  const cos = Math.acos(vectorProduct / (v1Norm * v2Norm));
  return (cos * 180) / Math.PI;
};

class LeapFrame {
  constructor(payload) {
    this.frame = payload.frame;
  }

  /**
   * Check if frame is valid
   * @return true if so, false else
   */
  isValid() {
    if (this.frame.pointables && this.frame.pointables.length > 0) {
      console.log(this.frame.hands[0].palmPosition);
      var pointableId = this.frame.pointables[0].handId;
      if (this.frame.hands && this.frame.hands[0]) {
        console.log(2);

        var handId = this.frame.hands[0].id;
        if (handId === pointableId) {
          return true;
        }
      }
    }
    return false;
  }

  /**
   * Check if fingers are present
   * @return true if so, false else
   */
  isValidFinger(frame) {
    if (this.frame.fingers && this.frame.fingers.length === 4) {
      return true;
    }
    return false;
  }

  palmPosition() {
    return {
      x: this.frame.hands[0].palmPosition[0],
      y: this.frame.hands[0].palmPosition[1],
      z: this.frame.hands[0].palmPosition[2],
    };
  }

  palmDirection() {
    return {
      x: this.frame.hands[0].direction[0],
      y: this.frame.hands[0].direction[1],
      z: this.frame.hands[0].direction[2],
    };
  }

  palmNormal() {
    return {
      x: this.frame.hands[0].palmNormal[0],
      y: this.frame.hands[0].palmNormal[1],
      z: this.frame.hands[0].palmNormal[2],
    };
  }

  fingerPosition(fingerIndex) {
    return {
      x: this.frame.pointables[fingerIndex].tipPosition[0],
      y: this.frame.pointables[fingerIndex].tipPosition[1],
      z: this.frame.pointables[fingerIndex].tipPosition[2],
    };
  }

  fingerDirection(fingerIndex) {
    return {
      x: this.frame.pointables[fingerIndex].direction[0],
      y: this.frame.pointables[fingerIndex].direction[1],
      z: this.frame.pointables[fingerIndex].direction[2],
    };
  }

  fingerAngleY(fingerIndex) {
    return vectorAngle(palmNormal(fingerIndex), fingerDirection(fingerIndex));
  }

  fingerAngleX(fingerIndex) {
    return vectorAngle(
      this.palmDirection(fingerIndex),
      this.fingerDirection(fingerIndex)
    );
  }

  deltaHandFinger(frame, fingerIndex) {
    return {
      x:
        this.palmPosition(frame, fingerIndex).x -
        this.fingerPosition(fingerIndex).x,
      y:
        this.palmPosition(frame, fingerIndex).y -
        this.fingerPosition(fingerIndex).y,
      z:
        this.palmPosition(frame, fingerIndex).z -
        this.fingerPosition(fingerIndex).z,
    };
  }

  run() {
    if (this.isValid()) {
      this.fingerAngleX = new Array(5);
      this.fingerAngleY = new Array(5);
      for (
        var fingerIndex = 0;
        fingerIndex < this.frame.pointables.length;
        fingerIndex++
      ) {
        this.fingerAngleX[fingerIndex] =
          this.deltaHandFinger(this.frame, fingerIndex).y * 2.8;
      }
    }

    return this.fingerAngleX;
  }
}

export default LeapFrame;

// var LeapFrame = function (data) {
//   this.frame = data;

//   /**
//    * Check if there is exploitable data in the current frame to move the servos
//    * @return true if so, false else
//    */
//   var _isValid = function (frame) {
//     if (frame.pointables && frame.pointables.length > 0) {
//       var pointableId = frame.pointables[0].handId;
//       if (frame.hands && frame.hands[0]) {
//         var handId = frame.hands[0].id;
//         if (handId === pointableId) {
//           return true;
//         }
//       }
//     }
//     return false;
//   };

//   /**
//    * Check if fingers are present
//    * @return true if so, false else
//    */
//   var _isValidFinger = function (frame) {
//     if (frame.fingers && frame.fingers.length === 4) {
//       return true;
//     }
//     return false;
//   };

//   /**
//    * Calculate the angle between 2 vectors in degrees
//    * @param {Array} v1 - coordinates of the first vector
//    * @param {Array} v2 - coordinates of the second vector
//    * @return the angle in degrees
//    */
//   var _vectorAngle = function (v1, v2) {
//     var vectorProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
//     var v1Norm = Math.sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
//     var v2Norm = Math.sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
//     var cos = Math.acos(vectorProduct / (v1Norm * v2Norm));
//     return (cos * 180) / Math.PI;
//   };

//   var _palmPosition = function (frame) {
//     return {
//       x: frame.hands[0].palmPosition[0],
//       y: frame.hands[0].palmPosition[1],
//       z: frame.hands[0].palmPosition[2],
//     };
//   };

//   var _palmDirection = function (frame) {
//     return {
//       x: frame.hands[0].direction[0],
//       y: frame.hands[0].direction[1],
//       z: frame.hands[0].direction[2],
//     };
//   };

//   var _palmNormal = function (frame) {
//     return {
//       x: frame.hands[0].palmNormal[0],
//       y: frame.hands[0].palmNormal[1],
//       z: frame.hands[0].palmNormal[2],
//     };
//   };

//   var _fingerPosition = function (frame, fingerIndex) {
//     return {
//       x: frame.pointables[fingerIndex].tipPosition[0],
//       y: frame.pointables[fingerIndex].tipPosition[1],
//       z: frame.pointables[fingerIndex].tipPosition[2],
//     };
//   };

//   var _fingerDirection = function (frame, fingerIndex) {
//     return {
//       x: frame.pointables[fingerIndex].direction[0],
//       y: frame.pointables[fingerIndex].direction[1],
//       z: frame.pointables[fingerIndex].direction[2],
//     };
//   };

//   var _fingerAngleY = function (frame, fingerIndex) {
//     return _vectorAngle(
//       _palmNormal(frame, fingerIndex),
//       _fingerDirection(frame, fingerIndex)
//     );
//   };

//   var _fingerAngleX = function (frame, fingerIndex) {
//     return _vectorAngle(
//       _palmDirection(frame, fingerIndex),
//       _fingerDirection(frame, fingerIndex)
//     );
//   };

//   var _deltaHandFinger = function (frame, fingerIndex) {
//     return {
//       x:
//         _palmPosition(frame, fingerIndex).x -
//         _fingerPosition(frame, fingerIndex).x,
//       y:
//         _palmPosition(frame, fingerIndex).y -
//         _fingerPosition(frame, fingerIndex).y,
//       z:
//         _palmPosition(frame, fingerIndex).z -
//         _fingerPosition(frame, fingerIndex).z,
//     };
//   };

//   if (_isValid(this.frame)) {
//     this.valid = true;
//     this.fingerAngleX = new Array(5);
//     this.fingerAngleY = new Array(5);
//     this.deltaHandFinger = new Array(5);
//     for (
//       var fingerIndex = 0;
//       fingerIndex < this.frame.pointables.length;
//       fingerIndex++
//     ) {
//       this.fingerAngleX[fingerIndex] =
//         _deltaHandFinger(this.frame, fingerIndex).y * 2.8;
//       //   console.log(this.fingerAngleX[fingerIndex]);
//       // this.fingerAngleY[fingerIndex] = _fingerAngleY(this.frame, fingerIndex);
//       // this.deltaHandFinger[fingerIndex] = _deltaHandFinger(this.frame, fingerIndex);
//     }
//   } else {
//     this.valid = false;
//   }

// };

// module.exports = LeapFrame;
