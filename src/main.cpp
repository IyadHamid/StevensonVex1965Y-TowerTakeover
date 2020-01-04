/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      4 Aug 2019                                                */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "display.h"
#include "controls.h"
#include "auton.h"
#include "actions.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  //blueUp();
  //blueSide();
  //redUp();
  //redSide();
  skills();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop 
  ControlGui cg = ControlGui({Controller1.Screen, Controller2.Screen});
  NotificationHandler nf = NotificationHandler({Controller1.Screen, Controller2.Screen});
  cg.update();

  while (true) {
    if (cg.settings[cg.Arcade]) {
      //Drone control
      arcadeControl(Controller1.Axis3.position(percent), Controller1.Axis1.position(percent));
    }
    else {
      tankControl(Controller1.Axis3.position(percent), Controller1.Axis2.position(percent));
    }

    if (Controller1.ButtonX.pressing()) {
      setLift(1);
    }
    else if (Controller1.ButtonA.pressing()) {
      setLift(0);
    }

    //Intake lift
    if (Controller1.ButtonL1.pressing()) {
      gotoTower(2);
    }
    else if (Controller1.ButtonL2.pressing()) {
      gotoTower(1);
    }
    else {
      gotoTower(0);
    }

    //Intake
    if (Controller1.ButtonR1.pressing()) {
      intake(75);
    }
    else if (Controller1.ButtonR2.pressing()) {
      intake(-50);
    }
    else {
      intake(0);
    }
    

    //Control gui controls
    if (Controller1.ButtonLeft.pressing() || Controller2.ButtonLeft.pressing()) {
      cg.shift(ControlGui::direction::left, 1);
    }
    else if (Controller1.ButtonRight.pressing() || Controller2.ButtonRight.pressing()) {
      cg.shift(ControlGui::direction::right, 1);
    }
    else if (Controller1.ButtonDown.pressing() || Controller2.ButtonDown.pressing()) {
      cg.toggle();
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  vexcodeInit();
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    if (Controller1.ButtonUp.pressing()) {
      goto end;
    }
    wait(100, msec); //prevent wastage of resources
  }
  end:
  wait(0, msec); 
}
