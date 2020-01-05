/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       actions.cpp                                               */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      1 Jan 2020                                                */
/*    Description:  Functionality for actions.h                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "actions.h"
#include "robot-config.h"

void setLift(int opt) {
  switch(opt) {
    case 1:
      cubeLift.setPosition(6, rotationUnits::rev);
      break;
    default:
      cubeLift.setPosition(0, rotationUnits::rev);
      break;
  }
}

void gotoTower2() {
  gotoTower(2);
}
void gotoTower1() {
  gotoTower(1);
}

void gotoTower(int opt) {
  switch (opt) {
    case 1: //Low
      cubeLift.rotateTo(3.7, rotationUnits::rev);
      intakeLift.rotateTo(.7, rotationUnits::rev);
      break;
    case 2: //Mid
      cubeLift.rotateTo(3.7, rotationUnits::rev);
      intakeLift.rotateTo(1.05, rotationUnits::rev);
      break;
    default: //Reset
      intakeLift.rotateTo(0, rotationUnits::rev);
      break;
  }
}


void intake(int vel) {
  if (vel == 0) {
    const double precision = 1000.0;
    const double ratio = 43.0 / 24.0; // 43/24 = motor rev -> chain rev
    double val;

    //pos % ratio = get amount after the last cycle
    val = (((long)round(intakeLeft.position(rotationUnits::rev) * precision) % 
            (long)round(ratio * precision))) / precision;
    //get value up to the next cycle
    val = ratio - val;
    intakeLeft.rotateFor(val, rotationUnits::rev);
    intakeLeft.resetPosition();
    intakeLeft.stop(brakeType::hold);

    //pos % ratio = get amount after the last cycle
    val = (((long)round(intakeRight.position(rotationUnits::rev) * precision) % 
            (long)round(ratio * precision))) / precision;
    //get value up to the next cycle
    val = ratio - val;
    intakeRight.rotateFor(val, rotationUnits::rev);
    intakeRight.resetPosition();
    intakeRight.stop(brakeType::hold);
  } 
  else {
    intakeLeft.spin(directionType::fwd, vel, velocityUnits::pct);
    intakeRight.spin(directionType::fwd, vel, velocityUnits::pct);
  }
}