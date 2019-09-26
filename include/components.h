/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       components.h                                              */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      4 Aug 2019                                                */
/*    Description:  Initalize Components                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include "vex.h"

using namespace vex;

extern brain Brain;

// motor name = motor( port, reversed? );
extern controller Controller1;
extern controller Controller2;

extern motor frontLeft;
extern motor backLeft;
extern motor frontRight;       
extern motor backRight;

extern motor cubeLift;

extern encoder encLeft;
extern encoder encRight;

extern bool pickOrange;
extern bool pickGreen;
extern bool pickPurple;

extern double revRatio;