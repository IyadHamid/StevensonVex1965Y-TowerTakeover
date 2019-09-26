/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      4 Aug 2019                                                */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "common.h"
#include "components.h"
#include "controls.h"
#include "display.h"
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

brain Brain;

controller Controller1 = controller(controllerType::primary);
controller Controller2 = controller(controllerType::partner);

motor frontLeft        = motor(PORT1 , gearSetting::ratio18_1, true);
motor backLeft         = motor(PORT2 , gearSetting::ratio18_1, true);
motor frontRight       = motor(PORT10, gearSetting::ratio18_1);
motor backRight        = motor(PORT9 , gearSetting::ratio18_1);

motor cubeLift         = motor(PORT5 , gearSetting::ratio36_1, true);

encoder encLeft        = encoder(Brain.ThreeWirePort.A);
encoder encRight       = encoder(Brain.ThreeWirePort.C);

bool pickOrange = false;
bool pickGreen  = false;
bool pickPurple = false;

//revs*(5/3)*2.75" = revs*(5/3)*(11/4)" => revs*(55/12) = distance => distance*12/55 = revs
double revRatio = 12.0/55.0; //distance to revs

void pre_auton(void) {}

void autonomous(void) {}

void usercontrol(void) {

  notifier nf({Controller1.Screen, Controller2.Screen});
  locationHandler lh;

  cGUI cg1(Controller1);
  travel(10, 10, 1, true);
  encLeft.resetRotation();
  while (1) {

    tankControl(Controller1);
    cg1.control();
    
    if (Controller1.ButtonL1.pressing()) {
      cubeLift.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    else if (Controller1.ButtonL2.pressing()) {
      cubeLift.spin(directionType::rev, 100, velocityUnits::pct);
    }
    else {
      cubeLift.setBrake(brakeType::hold);
    }
    task::sleep(20); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();
  while (1) {
    task::sleep(100);
  }
}