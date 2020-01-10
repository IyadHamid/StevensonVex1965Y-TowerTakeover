/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controls.cpp                                              */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      9 Aug 2019                                                */
/*    Description:  User controls implementation/movement                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "controls.h"
#include "actions.h"
#include "common.h"

using namespace std;
using namespace vex;

void arcadeControl(int vert, int hori) {
  // left=(Axis3+Axis4); right=(Axis3-Axis4);
  topLeft.spin(directionType::fwd, (vert + hori), velocityUnits::pct);
  bottomLeft.spin(directionType::fwd, (vert + hori), velocityUnits::pct);
  topRight.spin(directionType::fwd, (vert - hori),velocityUnits::pct);
  bottomRight.spin(directionType::fwd, (vert - hori), velocityUnits::pct);
}

void tankControl(int left, int right) {
  topLeft.spin(directionType::fwd, left, velocityUnits::pct);
  bottomLeft.spin(directionType::fwd, left, velocityUnits::pct);
  topRight.spin(directionType::fwd, right, velocityUnits::pct);
  bottomRight.spin(directionType::fwd, right, velocityUnits::pct);
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

void travel(double left, double right, double secs, bool wait) {
  left *= WHEEL_RATIO;
  right *= WHEEL_RATIO;
  double velL = 60.0 * left / secs;
  double velR = 60.0 * right / secs;
  leftDrive.rotateFor(directionType::fwd, left, rotationUnits::deg, velL,
                      velocityUnits::rpm, false);
  rightDrive.rotateFor(directionType::fwd, right, rotationUnits::deg, velR,
                       velocityUnits::rpm, wait);
}

void travel(double amount, double secs, bool wait) {
  amount *= WHEEL_RATIO;
  double vel = 60.0 * amount / secs;
  allDrive.rotateFor(directionType::fwd, amount, rotationUnits::deg, vel,
                      velocityUnits::rpm, wait);
}

LocationHandler::LocationHandler() {
  loc = {0, 0};
  deg = 0;
}

LocationHandler::LocationHandler(location nLoc, double nDeg) {
  loc = nLoc;
  deg = nDeg;
}

void LocationHandler::calcDisp() {
  const float w = 13.5; // ASSUMING WIDTH = 13.5"
  double radius = (w * (topRight.position(turns) + topLeft.position(turns)) /
                  (2 * (topRight.position(turns) - topLeft.position(turns))));
  deg += (180 * (topRight.position(turns) - topLeft.position(turns))) /
         (pi * w);
  loc.x += radius * cos(deg) - radius;
  loc.y += radius * sin(deg);
}