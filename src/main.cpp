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
#include "common.h"

using namespace vex;

// A global instance of competition
competition Competition;
double speedMultiplier;

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
  
  topLeft    .resetPosition();
  bottomLeft .resetPosition();
  topRight   .resetPosition();
  bottomRight.resetPosition();
  intakeLeft .resetPosition();
  intakeRight.resetPosition();
  cubeLift   .resetPosition();
  intakeLift .resetPosition();

  intakeLift.stop(brakeType::hold);
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
  init();
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

  int tower = 0;
  bool intakeRunning = false;
  thread macroThread = fn_null;
  thread stopIntakeThread;
  
  //No need to stress motor
  intakeLift.stop(brakeType::coast);

  while (true) {
    if (cg.settings[cg.Arcade]) {
      arcadeControl(Controller1.Axis3.position(percent) * speedMultiplier, 
                    Controller1.Axis4.position(percent) * speedMultiplier / 1.2);
    }
    else {
      //drone control
      arcadeControl(Controller1.Axis3.position(percent) * speedMultiplier, 
                    Controller1.Axis1.position(percent) * speedMultiplier / 1.2);
      //tankControl(Controller1.Axis3.position(percent), Controller1.Axis2.position(percent));
    }

    if (Controller1.ButtonX.pressing()) {
      macroThread.interrupt();
      macroThread = setLift1;
    }
    else if (Controller1.ButtonA.pressing()) {
      macroThread.interrupt();
      macroThread = setLift0;
    }

    if (Controller1.ButtonL1.pressing()) {
      macroThread.interrupt();
      macroThread = gotoTower2;
      tower = 2;
    }
    else if (Controller1.ButtonL2.pressing()) {
      macroThread.interrupt();
      macroThread = gotoTower1;
      tower = 1;
    }
    else if (tower != 0) {
      macroThread.interrupt();
      macroThread = gotoTower0;
      tower = 0;
    }

    //Intake
    if (Controller1.ButtonR1.pressing()) {
      intake(100);
      intakeRunning = true;
    }
    else if (Controller1.ButtonR2.pressing()) {
      intake(-50);
      intakeRunning = true;
    }
    else {
      if (intakeRunning) {
        stopIntakeThread = stopIntake;
        intakeRunning = false;
      }
    }
    
    if (Controller1.Axis2.position(percent) != 0) {
      if (Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing()) {
        intakeLift.spin(directionType::fwd, Controller1.Axis2.position(percent)/10, velocityUnits::rpm);
      }
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

    if (cg.Unjam == true) {
      intakeRunning = false;

      macroThread.interrupt();
      macroThread = fn_null;
      stopIntakeThread.interrupt();
      stopIntakeThread = fn_null;
      
      topLeft    .stop(brakeType::coast);
      bottomLeft .stop(brakeType::coast);
      topRight   .stop(brakeType::coast);
      bottomRight.stop(brakeType::coast);
      intakeLeft .stop(brakeType::coast);
      intakeRight.stop(brakeType::coast);
      cubeLift   .stop(brakeType::coast);
      intakeLift .stop(brakeType::coast);

      cg.setOption(ControlGui::Unjam, false);
    }
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
    wait(100, msec); //prevent wastage of resources
  }
}
