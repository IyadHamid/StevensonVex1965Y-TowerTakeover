/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controls.cpp                                              */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      9 Aug 2019                                                */
/*    Description:  User controls implementation/movement                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "controls.h"
#include "components.h"

#define WIDTH 13.5

using namespace std;
using namespace vex;

void arcadeControl(controller Controller) {
  // left=(Axis3+Axis4)/2; right=(Axis3-Axis4)/2;
  frontLeft.spin(directionType::fwd,
                 (Controller.Axis3.value() + Controller.Axis4.value()) / 2,
                 velocityUnits::pct);
  frontRight.spin(directionType::fwd,
                  (Controller.Axis3.value() - Controller.Axis4.value()) / 2,
                  velocityUnits::pct);
  backLeft.spin(directionType::fwd,
                (Controller.Axis3.value() + Controller.Axis4.value()) / 2,
                velocityUnits::pct);
  backRight.spin(directionType::fwd,
                 (Controller.Axis3.value() - Controller.Axis4.value()) / 2,
                 velocityUnits::pct);
}

void tankControl(controller Controller) {
  int l = (pow(Controller.Axis3.value(), 3)) / (pow(10.0, 4));
  int r = (pow(Controller.Axis2.value(), 3)) / (pow(10.0, 4));

  frontLeft.spin(directionType::fwd, l, velocityUnits::pct);
  backLeft.spin(directionType::fwd, l, velocityUnits::pct);
  frontRight.spin(directionType::fwd, r, velocityUnits::pct);
  backRight.spin(directionType::fwd, r, velocityUnits::pct);
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
  loc = {0,0};
  deg = 0;
}

locationHandler::locationHandler(location nLoc, double nDeg) {
  loc = nLoc;
  deg = nDeg;
}
void locationHandler::calcDisp() {
  double radius = (WIDTH * (encRight.value() + encLeft.value())) / (2 * (encRight.value() - encLeft.value()));
  deg += (180 * (encRight.value() - encLeft.value())) / (pi * WIDTH);
  loc.x += radius * cos(deg) - radius;
  loc.y += radius * sin(deg);
}