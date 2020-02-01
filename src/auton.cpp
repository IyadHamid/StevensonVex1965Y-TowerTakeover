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

//Initalize once
bool hasInit = false;

void init() {
  if (!hasInit) {
    Brain.Screen.print("INIT");
    intake(-100);
    //Put tray a bit forward
    intakeLift.rotateTo(.35, rotationUnits::rev, false);
    cubeLift.rotateTo(.6, rotationUnits::rev, true);
    cubeLift.resetRotation();
    ambientLight = (ambientLight + indexer.value(analogUnits::mV)) / 2;
  
    gotoTower(2);
    intake(0);
    gotoTower(0);
  }
  hasInit = true;
}

void oneCube() {
  allDrive.rotateFor(directionType::fwd, 20 * WHEEL_RATIO, rotationUnits::deg);
  allDrive.rotateFor(directionType::rev, 14 * WHEEL_RATIO, rotationUnits::deg);
}

void blue4Cube() {
  intake(170);
  travel(-45 * WHEEL_RATIO, 200);
  faceAngle(30, 50);
  travel(7 * WHEEL_RATIO, 200);
  wait(200, timeUnits::msec);
  intake(0);
  travel(-7 * WHEEL_RATIO, 200);
  wait(100, timeUnits::msec);
  faceAngle(180);
  travel(25 * WHEEL_RATIO);
  faceAngle(-135);
  travel(22 * WHEEL_RATIO);
  setLift(1);
  setLift(0);
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

void red4Cube() {
  intake(170);
  travel(45 * WHEEL_RATIO, 400);
  faceAngle(-30, 50);
  travel(7 * WHEEL_RATIO, 400);
  wait(200, timeUnits::msec);
  travel(-7 * WHEEL_RATIO, 400);
  intake(0);
  wait(100, timeUnits::msec);
  faceAngle(180);
  travel(35 * WHEEL_RATIO);
  faceAngle(125);
  travel(22 * WHEEL_RATIO, 3);
  setLift(1);
  setLift(0);
}

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
  oneCube();
}

void debug() {
  Brain.Screen.print("DEBUG AUTON");
  waitUntil(Brain.Screen.pressing());
  travel(0 * WHEEL_RATIO);
  Brain.Screen.print("GOODBYE");
}