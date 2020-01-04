/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       actions.cpp                                               */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      1 Jan 2020                                                */
/*    Description:  Functionality for actions.h                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "actions.h"
#include "robot-config.h"

void setLift(int opt) {
  switch(opt) {
    case 1:
      cubeLift.setPosition(5.9, rotationUnits::rev);
      break;
    default:
      cubeLift.setPosition(.5, rotationUnits::rev);
      break;
  }
}

void gotoTower(int opt) {
  switch (opt) {
    case 1: //Low
      intakeLift.startRotateTo(3, rotationUnits::rev);
      break;
    case 2: //High
      intakeLift.startRotateTo(4, rotationUnits::rev);
      break;
    default: //Reset
      intakeLift.startRotateTo(0, rotationUnits::rev);
      break;
  }
}