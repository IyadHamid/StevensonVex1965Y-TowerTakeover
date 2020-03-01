/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       reader.h                                                  */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      26 Feb 2020                                               */
/*    Description:  Reader header                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#pragma once

class Reader {
  public:
    Reader(vex::brain);

    void startRead();
    void stopRead();

    double driveTolerance = 100;
    double intakeTolerance = 10;
  private:
    vex::brain::sdcard sd;
    vex::timer timerR;
    bool read;
};