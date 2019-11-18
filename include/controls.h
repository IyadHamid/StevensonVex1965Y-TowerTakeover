/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controls.h                                                */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      9 Aug 2019                                                */
/*    Description:  User controls                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include <math.h>

#include "common.h"
#include "vex.h"

using namespace vex;

/**
 *@brief arcade control
 *@param int vertical
 *@param int horizontal
 */
void arcadeControl(int, int);

/**
 *@brief tank control
 *@param int left side
 *@param int right side
 */
void tankControl(int, int);

/**
 *@brief lift control
 *@param motor which controller to use
 *@param bool go up?
 *@param bool go down?
 *@param int veloctiy in rpm
 */
void lift(motor, bool, bool, int = 50);

/**
 *@brief intake control
 *@param int velocity pct
 */
void intake(int);

/**
 *@brief move distance
 *@param double distance travel by left
 *@param double distance travel by right
 *@param double time to complete (sec)
 *@param bool wait?
 */
void travel(double, double, double, bool = true);

/**
 *@brief move distance
 *@param double distance to travel
 *@param double time to complete
 *@param bool wait?
 */
void travel(double, double, bool = true);

class locationHandler {
public:
  struct location {
    double x;
    double y;
  };

  locationHandler();
  locationHandler(location, double);
  ~locationHandler();

  void calcDisp();

private:
  double deg;
  location loc;
};