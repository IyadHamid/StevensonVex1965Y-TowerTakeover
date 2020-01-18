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
#define CUBELIFT_MID 1.6

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
      intakeLift.rotateTo(.95, rotationUnits::rev, 50, velocityUnits::rpm, true);
      intakeLift.stop(brakeType::hold);
      Brain.Screen.clearScreen();
      break;
    case 2: //Mid
      speedMultiplier = .3;
      Brain.Screen.clearScreen(green);
      cubeLift.rotateTo(CUBELIFT_MID, rotationUnits::rev, 100, velocityUnits::pct, false);
      this_thread::sleep_for(1);
      intakeLift.rotateTo(1.25, rotationUnits::rev, 50, velocityUnits::rpm, true);
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
    intakes.stop(brakeType::hold);
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
  double opposite = (int)round(inert.heading() + 180) % 360;
  double fn;
  double l;
  double r;
  //precision
  const int pR = (int)(deg + precision) % 360;
  const int pL = (int)(deg + 360 - ((int)precision % 360)) % 360;

  //Until within range (in a circle [0,360))
  while (!((pL < opposite && opposite < pR) ||
          (opposite < pR && pR < pL) ||
          (pR < pL && pL < opposite))) {
    opposite = (int)round(inert.heading() + 180) % 360;

    Brain.Screen.printAt(0,175,"%d %d %d", 
        (int)(pL < opposite && opposite < pR), 
        (int)(opposite < pR && pR < pL), 
        (int)(pR < pL && pL < opposite));
    Brain.Screen.printAt(0,75,"deg:%lf   heading:%lf          ", deg, inert.heading());
    Brain.Screen.printAt(0,100,"opp:%lf          ", opposite);
    l = (int)round((360+deg) - opposite) % 360; //Left rotation
    r = (int)round((360+opposite) - deg) % 360; //Right rotation
    //fn = distance from target degree
    fn = r > l ? l : -r;
    Brain.Screen.printAt(0,125,"Angle to rot: %lf", fn);
    //fn now looks like x^3 with a gap at 0,0 (similar to piecewise w/ 2 x^2)
    fn = .001 * (fn < 0 ? -1 : 1) * (pow(fn, 2) + 100);
    //wrap fn in tanh (makes it into a modified sigmoid function)
    fn = 60 * tanh(fn);
    Brain.Screen.printAt(0,150,"rpm on left: %lf", fn);
      leftDrive.spin(directionType::fwd,
                     fn, 
                     velocityUnits::rpm);
      rightDrive.spin(directionType::rev,
                      fn,
                      velocityUnits::rpm);
  }
  allDrive.stop(brakeType::brake);
}