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
#include "reader.h"

//Force running auton after init
#define FORCE_AUTON 0
#define READER_MODE 0

using namespace vex;

// A global instance of competition
competition Competition;
double speedMultiplier = DEFAULT_SPEED_MULTIPLIER;
#if READER_MODE
Reader r = Reader(Brain);
#endif

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
  tray       .resetRotation();
  intakeLift .resetRotation();

  intakeLift.stop(brakeType::coast);
  
  //wait until inertial is done calibrating
  //also calibrate indexer
  while (inert.isCalibrating() && inert.installed()) {
    Brain.Screen.clearScreen(white);
    ambientLight = (ambientLight + indexer.value(analogUnits::mV)) / 2;
  }
  Brain.Screen.clearScreen(black);
}

/*
*/
void autonomous(void) {
  //init();
  //oneCube();
  //redSide();
  debug();
}

/*
*/
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
  task macroTask = task(task_cast fn_null);
  //No need to stress motor
  intakeLift.stop(brakeType::coast);

  Brain.Screen.print("User has control");
  Controller1.Axis3.changed(doArcade);
  Controller1.Axis4.changed(doArcade);
  //Check for buttons do not need to be multi-threaded
  while (true) {
    //Initialize incase for skills
    if (Controller1.ButtonY.pressing()) {
      macroTask.stop();
      macroTask = task(task_cast init);
    }

    //Set lift up/down in toggle mode
    if (Controller1.ButtonX.pressing()) {
      if (!buttonXPressed) {
        if (!liftUp) {
          macroTask.stop();
          macroTask = task(setLift1);
          liftUp = true;
        }
        else {
          macroTask.stop();
          macroTask = task(setLift0);
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
      macroTask.stop();
      macroTask = task(task_cast gotoTower2);
      tower = 2;
    }
    else if (Controller1.ButtonL2.pressing()) {
      macroTask.stop();
      macroTask = task(task_cast gotoTower1);
      tower = 1;
    }
    else if (tower != 0) {
      macroTask.stop();
      macroTask = task(task_cast gotoTower0);
      tower = 0;
    }

    //Intake
    if (Controller1.ButtonR1.pressing()) {
      intake(100);
      intakeRunning = true;
    }
    else if (Controller1.ButtonR2.pressing()) {
      intake(-100);
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
        tray.spin(directionType::fwd, Controller1.Axis2.position(percent)/8, velocityUnits::rpm);
      }
    }
    else if (axis2Reset) {
      intakeLift.stop();
      tray.stop();
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

      macroTask.stop();
      
      topLeft    .stop(brakeType::coast);
      bottomLeft .stop(brakeType::coast);
      topRight   .stop(brakeType::coast);
      bottomRight.stop(brakeType::coast);
      intakeLeft .stop(brakeType::coast);
      intakeRight.stop(brakeType::coast);
      tray       .stop(brakeType::coast);
      intakeLift .stop(brakeType::coast);

      cg.setOption(ControlGui::Unjam, false);
    }
#if READER_MODE
    if (Brain.Screen.pressing()) {
      Brain.Screen.clearScreen(white);
      r.stopRead();
      wait(1, timeUnits::sec);
      Brain.Screen.clearScreen(black);
    }
#endif
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Run the pre-autonomous function.
  pre_auton();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

#if FORCE_AUTON
  autonomous();
#endif
#if READER_MODE
  r.startRead();
#endif

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec); //prevent wastage of resources
  }
}