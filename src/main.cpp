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

//Force running auton after init
#define FORCE_AUTON 0

using namespace vex;

// A global instance of competition
competition Competition;
double speedMultiplier = .8;

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
  
  topLeft    .resetRotation();
  bottomLeft .resetRotation();
  topRight   .resetRotation();
  bottomRight.resetRotation();
  intakeLeft .resetRotation();
  intakeRight.resetRotation();
  cubeLift   .resetRotation();
  intakeLift .resetRotation();

  intakeLift.stop(brakeType::coast);
  
  //wait until inertial is done calibrating
  //also calibrate indexer
  while (inert.isCalibrating()) {
    Brain.Screen.clearScreen(white);
    ambientLight = (ambientLight + indexer.value(analogUnits::mV)) / 2;
  }
  Brain.Screen.clearScreen(black);
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
  red4Cube();
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
  ControlGui cg = ControlGui({Controller1.Screen, Controller2.Screen});
  NotificationHandler nf = NotificationHandler({Controller1.Screen, Controller2.Screen});
  cg.update();

  int tower = 0;
  bool intakeRunning = false;
  bool liftUp = false;
  bool buttonXPressed = false;
  bool axis2Reset = false;
  //Used for multithreading ("blocking" code)
  thread macroThread = fn_null;
  //No need to stress motor
  intakeLift.stop(brakeType::coast);

  //Drive controls are for some reason locked
  //gotoTower(0) unlocks it
  gotoTower(0);

  Controller1.Axis3.changed(doArcade);
  Controller1.Axis4.changed(doArcade);
  while (true) {
    //Initialize incase for skills
    if (Controller1.ButtonY.pressing()) {
      macroThread.interrupt();
      macroThread = init;
    }

    //Set lift up/down in toggle mode
    if (Controller1.ButtonX.pressing()) {
      if (!buttonXPressed) {
        if (!liftUp) {
          macroThread.interrupt();
          macroThread = setLift1;
          liftUp = true;
        }
        else {
          macroThread.interrupt();
          macroThread = setLift0;
          liftUp = false;
        }
      }
      buttonXPressed = true;
    }
    else {
      buttonXPressed = false;
    }

    //goto tower macros
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
        intake(0);
        intakeRunning = false;
      }
    }
    if (Controller1.ButtonB.pressing()) {
      putCubeInIntakes(); //Is already non-blocking, no need for macro
    }
    
    //Precision placement controls
    if (Controller1.Axis2.position() != 0) {
      axis2Reset = true;
      if (Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing()) {
        intakeLift.spin(directionType::fwd, Controller1.Axis2.position(percent)/10, velocityUnits::rpm);
      }
      else if (liftUp) {
        cubeLift.spin(directionType::fwd, Controller1.Axis2.position(percent)/8, velocityUnits::rpm);
      }
    }
    else if (axis2Reset) {
      intakeLift.stop();
      cubeLift.stop();
      axis2Reset = false;
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

    if (cg.settings[ControlGui::Unjam] == true) {
      intakeRunning = false;

      macroThread.interrupt();
      macroThread = fn_null;
      
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
  pre_auton();
  
#if FORCE_AUTON
  autonomous();
#endif

  // Prevent main from exiting with an infinite loop.
  while (true) {
    //Brain.Screen.printAt(0, 50, "Raw: %f", ultraSonic.distance(distanceUnits::in));
    //
    //Brain.Screen.printAt(0, 75, "fn: %f", ultraSonic.distance(distanceUnits::in));
    wait(100, msec); //prevent wastage of resources
  }
}