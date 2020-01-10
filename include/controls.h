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
 * @brief arcade control
 * @param int vertical
 * @param int horizontal
*/
void arcadeControl(int, int);

/**
 * @brief tank control
 * @param int left side
 * @param int right side
*/
void tankControl(int, int);

/**
 * @brief lift control
 * @param motor which controller to use
 * @param bool go up?
 * @param bool go down?
 * @param int veloctiy in rpm
*/
void lift(motor, bool, bool, int = 50);

/**
  * @brief Tracks displacement with drivetrain setups
*/
class LocationHandler {
public:
  struct location {
    double x;
    double y;
  };

  /**
    * @brief Initializes empty LocationHandler
  */
  LocationHandler();

  /**
    * @brief Initializes LocationHandler
    * @param location starting location
    * @param double degree facing
  */
  LocationHandler(location, double);
  ~LocationHandler();

  /**
   * @brief calculate from last tick
  */
  void calcDisp();
  
private:
  double deg;

  location loc;
};