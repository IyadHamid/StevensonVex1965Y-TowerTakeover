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
    tray.rotateTo(.4, rotationUnits::rev, 100, velocityUnits::rpm, true);
    tray.resetRotation();
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
  travelInputs inputs = {0, 500, 2, bottomLeft, allDrive, rotationUnits::deg};
  task autonTask0, autonTask1;
  intake(100);
  allDrive.stop();
  allDrive.spin(directionType::fwd, 600, velocityUnits::dps);
  waitUntil(bottomRight.rotation(rotationUnits::deg) >= 18*WHEEL_RATIO);
  inputs.dist = 20*WHEEL_RATIO;
  autonTask0 = task(travel, &inputs);
  waitUntil(bottomRight.rotation(rotationUnits::deg) >= 33*WHEEL_RATIO);
  gotoTower(3, .25);
  wait(300, timeUnits::msec);
  autonTask1 = task(gotoTower0);
  wait(300, timeUnits::msec);
  autonTask0.stop();
  //38"
  travel(-13*WHEEL_RATIO, 1000);
  intakes.stop(brakeType::hold);
  sCurve();
  wait(80, timeUnits::msec);
  faceAngle(0, 30);
  allDrive.spin(directionType::fwd, 600, velocityUnits::dps);
  intake(100);
  waitUntil(bottomRight.rotation(rotationUnits::deg) >= 12*WHEEL_RATIO);
  travel(22 * WHEEL_RATIO);
  wait(1, timeUnits::sec);

  intake(0);
Brain.Screen.print("GOODBYE");
}