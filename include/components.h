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

brain Brain;

// motor name = motor( port, reversed? );
controller Controller1 = controller();
controller Controller2 = controller();