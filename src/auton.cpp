/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonomous.cpp                                            */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      10 Oct 2019                                               */
/*    Description:  Autonomous function implementation                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "auton.h"
#include "actions.h"
#include "robot-config.h"

void init() {
  intakeLift.rotateTo(.1, rotationUnits::rev, true);
  this_thread::sleep_for(1);
  cubeLift.rotateTo(.4, rotationUnits::rev, true);
  intakeLift.rotateTo(2.5, rotationUnits::rev, true);
}

void blueUp() {/*Not Yet Implemented*/}

void blueSide() {/*Not Yet Implemented*/}

void redUp() {/*Not Yet Implemented*/}

void redSide() {/*Not Yet Implemented*/}

void skills() {/*Not Yet Implemented*/}