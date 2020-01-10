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
#include "common.h"
#include "robot-config.h"

#define CUBELIFT_UP 2.8
#define CUBELIFT_MID 1.5
#define WHEEL_RATIO (60.0/36.0)

void setLift(int opt) {
  intakeLift.stop(brakeType::hold);
  switch(opt) {
    case 1:
      //Need interpolated
      while (cubeLift.position(rotationUnits::rev) < 2.6) {
        cubeLift.spin(directionType::fwd,
                      //40*cos((2*pi/7)*[pos])+40
                      40.0*cos(((2.0*pi)/7)*cubeLift.position(rotationUnits::rev))+40,
                      velocityUnits::rpm);
      }
      cubeLift.stop(brakeType::hold);
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
      while (intakeLift.position(rotationUnits::rev) > .01) {
        intakeLift.spin(directionType::rev,
                        //40*tanh(4*([pos]-.2))+40
                        40*tanh(4*(intakeLift.position(rotationUnits::rev)-.2))+40,
                        velocityUnits::rpm);
        if (intakeLift.position(rotationUnits::rev) < 1 && !cubeLift.isSpinning()) {
          cubeLift.rotateTo(0, rotationUnits::rev);     
        }
      }
      intakeLift.stop(brakeType::coast);
      cubeLift.rotateTo(0, rotationUnits::rev);
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

void travel(double left, double right, double secs, bool wait) {
  double velL = 60.0 * left * WHEEL_RATIO / secs;
  double velR = 60.0 * right * WHEEL_RATIO / secs;
  topLeft.rotateFor(directionType::fwd, left, rotationUnits::rev, velL,
                      velocityUnits::rpm, false);
  bottomLeft.rotateFor(directionType::fwd, left, rotationUnits::rev, velL,
                     velocityUnits::rpm, false);
  topRight.rotateFor(directionType::fwd, right, rotationUnits::rev, velR,
                       velocityUnits::rpm, false);
  bottomRight.rotateFor(directionType::fwd, right, rotationUnits::rev, velR,
                      velocityUnits::rpm, wait);
}

void travel(double amount, double secs, bool wait) {
  double vel = 60.0 * amount * WHEEL_RATIO / secs;
  topLeft.rotateFor(directionType::fwd, amount, rotationUnits::rev, vel,
                      velocityUnits::rpm, false);
  bottomLeft.rotateFor(directionType::fwd, amount, rotationUnits::rev, vel,
                     velocityUnits::rpm, false);
  topRight.rotateFor(directionType::fwd, amount, rotationUnits::rev, vel,
                       velocityUnits::rpm, false);
  bottomRight.rotateFor(directionType::fwd, amount, rotationUnits::rev, vel,
                      velocityUnits::rpm, wait);
}
void faceAngle(double deg, double precision) {
    if (inert.yaw() > deg + precision) { //Rotate left
      leftDrive.spin(directionType::fwd,
                     40*tanh(.04*((deg - inert.yaw())-40))+40, 
                     velocityUnits::rpm);
      rightDrive.spin(directionType::fwd,
                      -40*tanh(.04*((deg - inert.yaw())+40))+40, 
                      velocityUnits::rpm);
    }
    else if (inert.yaw() < deg - precision) { //Rotate right
      rightDrive.spin(directionType::fwd,
                      40*tanh(.04*((deg - inert.yaw())-40))+40, 
                      velocityUnits::rpm);
      leftDrive.spin(directionType::fwd,
                     -40*tanh(.04*((deg - inert.yaw())+40))+40, 
                     velocityUnits::rpm);
    }
  }
  allDrive.stop(brakeType::brake);
}
