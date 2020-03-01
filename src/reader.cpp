/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       reader.cpp                                                */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      26 Feb 2020                                               */
/*    Description:  Reader Functionality                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include <string>
#include "common.h"
#include "actions.h"
#include "reader.h"
#include "robot-config.h"

using namespace vex;
using namespace std;

Reader::Reader(brain b) {
  brain::sdcard sd = b.SDcard;
  timerR = b.Timer;
}

int foo(void *a){return 0;}

void Reader::startRead() {
  read = true;
  string buffer = "//This was auto-generated through Reader\n";
  buffer += "task leftTask, rightTask;\n";
  buffer += "travelInputs inputs = {0, 0, 0, bottomLeft, allDrive, rotationUnits::deg};\n";
  timerR.reset();

  //Old right rotations, old left rotations, current right rotations, current left rotations
  double dR, dL;
  //Check left/right
  bool left = true, right = true;
  //waits
  string waitLeft = "", waitRight = "";
  //Intake velocity
  double oldintake = 0, intake;
  while (read) {

    //Drive train
    dL = bottomLeft.velocity(velocityUnits::dps);
    dR = bottomRight.velocity(velocityUnits::dps);
    if (within_tolerance(dL, driveTolerance, 0)) {
      if (left) {
        buffer += waitLeft;
        buffer += "inputs = {";
        buffer += to_string(bottomLeft.rotation(rotationUnits::deg)) + ", "; //Rotations
        buffer += to_string(dL + 400) + ", "; //Dps
        buffer += "10, "; //Percision
        buffer += "bottomLeft, "; //Encoder Motor
        buffer += "leftDrive, "; //Driver
        buffer += "rotationUnits::deg"; //Units
        buffer += "};\n";
        buffer += "leftTask = task(travel, &inputs);\n";
        
        waitLeft = "waitUntil(bottomLeft.rotation(rotationUnits::deg)" + to_string(dL >= 0 ? " >= " : " <= ") + to_string(bottomLeft.rotation(rotationUnits::deg)) + ");\n";
      }
      left = false;
    }
    else {
      left = true;
    }
    if (within_tolerance(dR, driveTolerance, 0)) {
      if (right) {
        buffer += waitRight;
        buffer += "inputs = {";
        buffer += to_string(bottomRight.rotation(rotationUnits::deg)) + ", "; //Rotations
        buffer += to_string(dR + 400) + ", "; //Dps
        buffer += "10, "; //Percision
        buffer += "bottomRight, "; //Encoder Motor
        buffer += "rightDrive, "; //Driver
        buffer += "rotationUnits::deg"; //Units
        buffer += "};\n";
        buffer += "rightTask = task(travel, &inputs);\n";

        waitRight = "waitUntil(bottomRight.rotation(rotationUnits::deg)" + to_string(dL >= 0 ? " >= " : " <= ") + to_string(bottomRight.rotation(rotationUnits::deg)) + ");\n";
      }
      right = false;
    }
    else {
      right = true;
    }

    //Intakes
    intake = intakeLeft.rotation(rotationUnits::deg);
    if (!within_tolerance(intake, intakeTolerance, oldintake)) {
      oldintake = intake;
      buffer += "intake(" + to_string(intake) + ", velocityUnits::dps);\n";
    }
  }


  //Name = day.mon.year_hour.min
  struct time pTime;
  struct date pDate;
  vexGettime(&pTime);
  vexGetdate(&pDate);
  string name = to_string(pDate.da_day) + "." + to_string(pDate.da_mon) + "." + to_string(pDate.da_year) + "_";
  name += to_string(pTime.ti_hour) + "." + to_string(pTime.ti_min);
  name = "Auton.txt";
  sd.savefile(name.c_str(), (uint8_t *)buffer.c_str(), buffer.length());
  name = "Read saved as " + name;
  Brain.Screen.printAt(0,50, name.c_str());
}

void Reader::stopRead() {
  read = false;
}