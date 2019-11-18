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
  // left=(Axis3+Axis4); right=(Axis3-Axis4);
  frontLeft.spin(directionType::fwd, (vert + hori), velocityUnits::pct);
  backLeft.spin(directionType::fwd, (vert + hori), velocityUnits::pct);
  frontRight.spin(directionType::fwd, (vert - hori),velocityUnits::pct);
  backRight.spin(directionType::fwd, (vert - hori), velocityUnits::pct);
}

void tankControl(int left, int right) {
  frontLeft.spin(directionType::fwd, left, velocityUnits::pct);
  backLeft.spin(directionType::fwd, left, velocityUnits::pct);
  frontRight.spin(directionType::fwd, right, velocityUnits::pct);
  backRight.spin(directionType::fwd, right, velocityUnits::pct);
}

void lift(motor m, bool up, bool down, int vel) {
  if (up) {
    m.spin(directionType::fwd, vel, velocityUnits::rpm);
  } else if (down) {
    m.spin(directionType::rev, vel, velocityUnits::rpm);
  } else {
    m.stop(brakeType::hold);
  }
}

void intake(int vel) {
  intakeLeft.spin(directionType::fwd, vel, velocityUnits::pct);
  intakeRight.spin(directionType::fwd, vel, velocityUnits::pct);
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