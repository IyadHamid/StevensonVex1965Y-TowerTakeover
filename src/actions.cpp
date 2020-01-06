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
  intakeLift.stop(brakeType::hold);
  switch(opt) {
    case 1:
      cubeLift.rotateTo(6, rotationUnits::rev);
      break;
    default:
      cubeLift.rotateTo(0, rotationUnits::rev);
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
      Brain.Screen.clearScreen(red);
      cubeLift.rotateTo(3.7, rotationUnits::rev, 100, velocityUnits::pct, false);
      waitUntil(cubeLift.position(rotationUnits::rev) > .1);
      intakeLift.rotateTo(6.8, rotationUnits::rev, 50, velocityUnits::rpm, false);
      waitUntil(intakeLift.position(rotationUnits::rev) > .9);
      intakeLift.stop(brakeType::hold);
      break;
    case 2: //Mid
      Brain.Screen.clearScreen(green);
      cubeLift.rotateTo(3.7, rotationUnits::rev, 100, velocityUnits::pct, false);
      waitUntil(cubeLift.position(rotationUnits::rev) > .1);
      intakeLift.rotateTo(6.8, rotationUnits::rev, 50, velocityUnits::rpm, false);
      waitUntil(intakeLift.position(rotationUnits::rev) > .9);
      intakeLift.stop(brakeType::hold);
      break;
    default: //Reset
      cubeLift.rotateTo(0, rotationUnits::rev, 100, velocityUnits::pct, false);
      intakeLift.rotateTo(0, rotationUnits::rev, false);
      waitUntil(intakeLift.position(rotationUnits::rev) < .1);
      break;
  }
}

void stopIntake() {
    intake(0);
}

void intake(int vel) {
  if (vel == 0) {
    //const double precision = 1000.0;
    //const double ratio = 43.0 / 24.0; // 43/24 = motor rev -> chain rev
    //double val;
    //if (intakeLeft.position(rotationUnits::rev) < -.1 || intakeLeft.position(rotationUnits::rev) > .1) {
    //  //pos % ratio = get amount after the last cycle
    //  val = (((long)round(intakeLeft.position(rotationUnits::rev) * precision) % 
    //          (long)round(ratio * precision))) / precision;
    //  //get value up to the next cycle
    //  val = ratio - val;
    //  intakeLeft.rotateFor(val, rotationUnits::rev);
    //  intakeLeft.resetPosition();
    //}
    intakeLeft.stop(brakeType::hold);

    //if (intakeRight.position(rotationUnits::rev) < -.1 || intakeRight.position(rotationUnits::rev) > .1) {
    //  //pos % ratio = get amount after the last cycle
    //  val = (((long)round(intakeRight.position(rotationUnits::rev) * precision) % 
    //          (long)round(ratio * precision))) / precision;
    //  //get value up to the next cycle
    //  val = ratio - val;
    //  intakeRight.rotateFor(val, rotationUnits::rev);
    //  intakeRight.resetPosition();
    //}
    intakeRight.stop(brakeType::hold);
  } 
  else {
    intakeLeft.spin(directionType::fwd, vel, velocityUnits::pct);
    intakeRight.spin(directionType::fwd, vel, velocityUnits::pct);
  }
}