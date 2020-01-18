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

bool hasInit = false;

void init() {
  //intakeLift.rotateTo(.1, rotationUnits::rev, true);
  //this_thread::sleep_for(1);
  //cubeLift.rotateTo(.4, rotationUnits::rev, true);
  //intakeLift.rotateTo(2.5, rotationUnits::rev, true);
  if (!hasInit) {
    cubeLift.rotateTo(.43, rotationUnits::rev, false);
    cubeLift.resetRotation();
  }
  hasInit = true;
}

void blueUp() {
  allDrive.rotateFor(directionType::fwd, 20 * WHEEL_RATIO, rotationUnits::deg);
  allDrive.rotateFor(directionType::rev, 14 * WHEEL_RATIO, rotationUnits::deg);
}

void blueSide() {
  intake(100);
  allDrive.rotateFor(directionType::fwd, 40 * WHEEL_RATIO, rotationUnits::deg);
  intake(0);

  faceAngle(335);

  allDrive.rotateFor(directionType::rev, 41.75 * WHEEL_RATIO, rotationUnits::deg);
  leftDrive.rotateFor(directionType::rev, 9.25 * WHEEL_RATIO, rotationUnits::deg);

  intake(100);
  allDrive.rotateFor(directionType::fwd, 40, rotationUnits::deg);
  intake(0);

  faceAngle(45);

  allDrive.rotateFor(directionType::fwd, 55 * WHEEL_RATIO, rotationUnits::deg);

  setLift(1);

  allDrive.rotateFor(directionType::rev, 10 * WHEEL_RATIO, rotationUnits::deg);
}

void redUp() {/*Not Implemented*/}

void redSide() {

  intake(100);
  allDrive.rotateFor(directionType::fwd, 40 * WHEEL_RATIO, rotationUnits::deg);
  intake(0);

  faceAngle(25);

  allDrive.rotateFor(directionType::rev, 41.75 * WHEEL_RATIO, rotationUnits::deg);
  leftDrive.rotateFor(directionType::rev, 9.25 * WHEEL_RATIO, rotationUnits::deg);

  intake(100);
  allDrive.rotateFor(directionType::fwd, 40, rotationUnits::deg);
  intake(0);

  faceAngle(135);

  allDrive.rotateFor(directionType::fwd, 55 * WHEEL_RATIO, rotationUnits::deg);

  setLift(1);

  allDrive.rotateFor(directionType::rev, 10 * WHEEL_RATIO, rotationUnits::deg);
}

void skills() {
  redSide();
}