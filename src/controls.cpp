/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controls.cpp                                              */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      9 Aug 2019                                                */
/*    Description:  User controls implementation/movement                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "controls.h"
#include "robot-config.h"

using namespace std;
using namespace vex;

const double revRatio = 1;

void arcadeControl(int vert, int hori) {
  // left=(Axis3+Axis4)/2; right=(Axis3-Axis4)/2;
  frontLeft.spin(directionType::fwd, (vert + hori) / 2, velocityUnits::pct);
  frontRight.spin(directionType::fwd, (vert - hori) / 2, velocityUnits::pct);
  backLeft.spin(directionType::fwd, (vert + hori) / 2, velocityUnits::pct);
  backRight.spin(directionType::fwd, (vert - hori) / 2, velocityUnits::pct);
}

void tankControl(int left, int right) {
  frontLeft.spin(directionType::fwd, left, velocityUnits::pct);
  backLeft.spin(directionType::fwd, left, velocityUnits::pct);
  frontRight.spin(directionType::fwd, right, velocityUnits::pct);
  backRight.spin(directionType::fwd, right, velocityUnits::pct);
}

void lift(controller Controller) {
  if (Controller.ButtonL1.pressing()) {
    cubeLift.spin(directionType::fwd, 50, velocityUnits::rpm);
  } else if (Controller.ButtonL2.pressing()) {
    cubeLift.spin(directionType::rev, 50, velocityUnits::rpm);
  } else {
    cubeLift.stop(brakeType::hold);
  }

  if (Controller.ButtonR1.pressing()) {
    intakeLift.spin(directionType::fwd, 50, velocityUnits::rpm);
  } else if (Controller.ButtonR2.pressing()) {
    intakeLift.spin(directionType::rev, 50, velocityUnits::rpm);
  } else {
    intakeLift.stop(brakeType::hold);
  }
}

void intake(controller Controller) {
  int l = (pow(Controller.Axis1.value(), 3)) / 10000;
  int r = (pow(Controller.Axis4.value(), 3)) / 10000;

  intakeLeft.spin(directionType::fwd, l, velocityUnits::pct);
  intakeRight.spin(directionType::fwd, r, velocityUnits::pct);
}

void travel(double left, double right, double secs, bool wait) {
  double velL = 60.0 * left * revRatio / secs;
  double velR = 60.0 * right * revRatio / secs;
  frontLeft.rotateFor(directionType::fwd, left, rotationUnits::rev, velL,
                      velocityUnits::rpm, false);
  backLeft.rotateFor(directionType::fwd, left, rotationUnits::rev, velL,
                     velocityUnits::rpm, false);
  frontRight.rotateFor(directionType::fwd, right, rotationUnits::rev, velR,
                       velocityUnits::rpm, false);
  backRight.rotateFor(directionType::fwd, right, rotationUnits::rev, velR,
                      velocityUnits::rpm, wait);
}

void travel(double amount, double secs, bool wait) {
  double vel = 60.0 * amount * revRatio / secs;
  frontLeft.rotateFor(directionType::fwd, amount, rotationUnits::rev, vel,
                      velocityUnits::rpm, false);
  backLeft.rotateFor(directionType::fwd, amount, rotationUnits::rev, vel,
                     velocityUnits::rpm, false);
  frontRight.rotateFor(directionType::fwd, amount, rotationUnits::rev, vel,
                       velocityUnits::rpm, false);
  backRight.rotateFor(directionType::fwd, amount, rotationUnits::rev, vel,
                      velocityUnits::rpm, wait);
}

locationHandler::locationHandler() {
  loc = {0, 0};
  deg = 0;
}

locationHandler::locationHandler(location nLoc, double nDeg) {
  loc = nLoc;
  deg = nDeg;
}
void locationHandler::calcDisp() {
  const float w = 13.5; // ASSUMING WIDTH = 13.5"
  double radius =
      (w * (frontRight.position(turns) + frontLeft.position(turns)) /
       (2 * (frontRight.position(turns) - frontLeft.position(turns))));
  deg += (180 * (frontRight.position(turns) - frontLeft.position(turns))) /
         (pi * w);
  loc.x += radius * cos(deg) - radius;
  loc.y += radius * sin(deg);
}