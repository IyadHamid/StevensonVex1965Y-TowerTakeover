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

#define CUBELIFT_UP 3.3
#define CUBELIFT_MID 1.65

void setLift(int opt) {
  intakeLift.stop(brakeType::hold);
  switch(opt) {
    case 1:
      cubeLift.rotateTo(CUBELIFT_UP, rotationUnits::rev, 70, velocityUnits::rpm);
      break;
    default:
      cubeLift.rotateTo(0, rotationUnits::rev, 70, velocityUnits::rpm);
      break;
  }
}

void setLift1() {
  setLift(1);
}


void setLift0() {
  setLift(0);
}

void gotoTower(int opt) {
  switch (opt) {
    case 1: //Low
      speedMultiplier = .3;
      Brain.Screen.clearScreen(red);
      cubeLift.rotateTo(CUBELIFT_MID, rotationUnits::rev, 100, velocityUnits::pct, false);
      this_thread::sleep_for(1);
      intakeLift.rotateTo(.85, rotationUnits::rev, 50, velocityUnits::rpm, true);
      intakeLift.stop(brakeType::hold);
      Brain.Screen.clearScreen();
      break;
    case 2: //Mid
      speedMultiplier = .3;
      Brain.Screen.clearScreen(green);
      cubeLift.rotateTo(CUBELIFT_MID, rotationUnits::rev, 100, velocityUnits::pct, false);
      this_thread::sleep_for(1);
      intakeLift.rotateTo(1.15, rotationUnits::rev, 50, velocityUnits::rpm, true);
      intakeLift.stop(brakeType::hold);
      Brain.Screen.clearScreen();
      break;
    default: //Reset
      speedMultiplier = 1;
      Brain.Screen.clearScreen(blue);
      intakeLift.setStopping(brakeType::coast);
      intakeLift.rotateTo(.15, rotationUnits::rev, 80, velocityUnits::pct, false);
      waitUntil(intakeLift.position(rotationUnits::rev) < .9);
      cubeLift.rotateTo(0, rotationUnits::rev, 100, velocityUnits::pct, false);
      waitUntil(intakeLift.position(rotationUnits::rev) < .2);
      this_thread::sleep_for(10);
      intakeLift.rotateTo(0, rotationUnits::rev, 10, velocityUnits::pct, false);
      intakeLift.setStopping(brakeType::brake);
      Brain.Screen.clearScreen();
      break;
  }
}

void gotoTower2() {
  gotoTower(2);
}

void gotoTower1() {
  gotoTower(1);
}

void gotoTower0() {
  gotoTower(0);
}

void intake(int vel) {
  if (vel == 0) {
    intakeLeft.stop(brakeType::hold);

    intakeRight.rotateFor(intakeLeft.position(rotationUnits::deg) - intakeRight.position(rotationUnits::deg), rotationUnits::deg);
    intakeRight.stop(brakeType::hold);
  } 
  else {
    if (intakeLeft.position(rotationUnits::deg) < intakeRight.position(rotationUnits::deg)) {
      intakeLeft.spin(directionType::fwd, vel, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, vel - 10, velocityUnits::pct);
    }
    else {
      intakeLeft.spin(directionType::fwd, vel - 10, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, vel, velocityUnits::pct);
    }
  }
}

void stopIntake() {
  intake(0);
}
