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

using namespace std;
using namespace vex;

// A global instance of competition
competition Competition;

controller Controller1 = controller(controllerType::primary);
controller Controller2 = controller(controllerType::partner);

motor frontLeft        = motor(PORT1, true);
motor backLeft         = motor(PORT2, true);
motor frontRight       = motor(PORT10);
motor backRight        = motor(PORT9);

bool pickOrange = false;
bool pickGreen  = false;
bool pickPurple = false;

void pre_auton(void) {}

void autonomous(void) {}

void usercontrol(void) {

  notifier nf({Controller1.Screen, Controller2.Screen});
  cGUI cg1(Controller1.Screen);
  
  while (1) {

    tankControl(Controller1);
    if (Controller1.ButtonRight.pressing()) {
      cg1.shift(cGUI::direction::right);
    }
    else if (Controller1.ButtonLeft.pressing()) {
      cg1.shift(cGUI::direction::left);
    }
    else if (Controller1.ButtonB.pressing()) {
      cg1.toggle();
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