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
    intake(100);
    //Put tray a bit forward
    cubeLift.rotateTo(.4, rotationUnits::rev, 100, velocityUnits::rpm, true);
    cubeLift.resetRotation();
    ambientLight = (ambientLight + indexer.value(analogUnits::mV)) / 2;
  }
  hasInit = true;
}

void oneCube() {
  wait(1, timeUnits::sec);
  travel(8 * WHEEL_RATIO, 800);
  intake(-100);
  wait(2, timeUnits::sec);
  intake(0);
  travel(-10 * WHEEL_RATIO, 400);
}

void blue4Cube() {
  intake(200);
  travel(45 * WHEEL_RATIO, 500);
  //faceAngle(-30, 50);
  //travel(7 * WHEEL_RATIO, 400);
  wait(200, timeUnits::msec);
  //travel(-7 * WHEEL_RATIO, 400);
  intake(0);
  wait(100, timeUnits::msec);
  travel(-35 * WHEEL_RATIO, 700);
  faceAngle(-125, 70);
  travel(21 * WHEEL_RATIO);
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
  //faceAngle(-30, 50);
  //travel(7 * WHEEL_RATIO, 400);
  wait(200, timeUnits::msec);
  //travel(-7 * WHEEL_RATIO, 400);
  intake(0);
  wait(100, timeUnits::msec);
  travel(-35 * WHEEL_RATIO);
  faceAngle(125, 40);
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