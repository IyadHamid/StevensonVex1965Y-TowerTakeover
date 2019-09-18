/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controls.cpp                                              */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      9 Aug 2019                                                */
/*    Description:  User controls implementation                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "controls.h"
#include "components.h"  

using namespace std;
using namespace vex;

void arcadeControl(controller Controller) {
  //left=(Axis3+Axis4)/2; right=(Axis3-Axis4)/2;
  frontLeft .spin(directionType::fwd, (Controller.Axis3.value() + Controller.Axis4.value())/2, velocityUnits::pct); 
  frontRight.spin(directionType::fwd, (Controller.Axis3.value() - Controller.Axis4.value())/2, velocityUnits::pct);
  backLeft  .spin(directionType::fwd, (Controller.Axis3.value() + Controller.Axis4.value())/2, velocityUnits::pct); 
  backRight .spin(directionType::fwd, (Controller.Axis3.value() - Controller.Axis4.value())/2, velocityUnits::pct);
}

void tankControl(controller Controller) {
  frontLeft .spin(directionType::fwd, Controller.Axis3.value(), velocityUnits::pct);
  backLeft  .spin(directionType::fwd, Controller.Axis3.value(), velocityUnits::pct);
  frontRight.spin(directionType::fwd, Controller.Axis2.value(), velocityUnits::pct);
  backRight .spin(directionType::fwd, Controller.Axis2.value(), velocityUnits::pct);
}