/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonomous.cpp                                            */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      10 Oct 2019                                               */
/*    Description:  Autonomous function implementation                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include <vector>

#include "vex.h"
#include "auton.h"
#include "actions.h"
#include "controls.h"
#include "robot-config.h"

void init() {
  //intakeLift.rotateTo(.1, rotationUnits::rev, true);
  //this_thread::sleep_for(1);
  //cubeLift.rotateTo(.4, rotationUnits::rev, true);
  //intakeLift.rotateTo(2.5, rotationUnits::rev, true);
}

void blueUp() {/*Not Implemented*/}

void blueSide() {
  allDrive.rotateFor(directionType::fwd, 40 * WHEEL_RATIO, rotationUnits::deg);

  faceAngle(335);

  allDrive.rotateFor(directionType::rev, 41.75 * WHEEL_RATIO, rotationUnits::deg);
  leftDrive.rotateFor(directionType::rev, 9.25 * WHEEL_RATIO, rotationUnits::deg);

  allDrive.rotateFor(directionType::fwd, 40, rotationUnits::deg);

  faceAngle(45);

  allDrive.rotateFor(directionType::fwd, 55 * WHEEL_RATIO, rotationUnits::deg);

  setLift(1);

  allDrive.rotateFor(directionType::rev, 10 * WHEEL_RATIO, rotationUnits::deg);
}

void redUp() {/*Not Implemented*/}

void redSide() {
  allDrive.rotateFor(directionType::fwd, 40 * WHEEL_RATIO, rotationUnits::deg);

  faceAngle(25);

  allDrive.rotateFor(directionType::rev, 41.75 * WHEEL_RATIO, rotationUnits::deg);
  leftDrive.rotateFor(directionType::rev, 9.25 * WHEEL_RATIO, rotationUnits::deg);

  allDrive.rotateFor(directionType::fwd, 40, rotationUnits::deg);

  faceAngle(135);

  allDrive.rotateFor(directionType::fwd, 55 * WHEEL_RATIO, rotationUnits::deg);

  setLift(1);

  allDrive.rotateFor(directionType::rev, 10 * WHEEL_RATIO, rotationUnits::deg);
}

void skills() {
  redSide();
}