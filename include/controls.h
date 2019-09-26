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

/*
 *@brief arcade control
 *@return none
 *@param controller which controller to use
 */
void arcadeControl(controller Controller);

/*
 *@brief tank control
 *@return none
 *@param controller which controller to use
 */
void tankControl(controller);

/*
 *@brief move distance
 *@return none
 *@param double distance travel by left
 *@param double distance travel by right
 *@param double time to complete (sec)
 *@param bool wait?
 */
void travel(double, double, double, bool = true);

/*
 *@brief move distance
 *@return none
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