/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       lights.cpp                                                */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      3 Jan 2019                                                */
/*    Description:  Implementation for ws2812 lights                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
//TBA
using namespace vex;
pwm_out light_output = pwm_out(Brain.ThreeWirePort.A);

void lightStart() {
  light_output.state(50, percentUnits::pct);
}