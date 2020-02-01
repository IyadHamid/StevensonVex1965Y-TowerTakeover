/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       controls.cpp                                              */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      9 Aug 2019                                                */
/*    Description:  User controls implementation/movement                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include <vector>

#include "vex.h"
#include "controls.h"
#include "actions.h"
#include "common.h"

using namespace std;
using namespace vex;

void arcadeControl(int vert, int hori) {
  //left=(vert+hori)
  //right=(vert-hori)
  //Change to rpm
  vert *= 2;
  hori *= 2;
  topLeft.spin(directionType::fwd, (vert + hori), velocityUnits::rpm);
  bottomLeft.spin(directionType::fwd, (vert + hori), velocityUnits::rpm);
  topRight.spin(directionType::fwd, (vert - hori),velocityUnits::rpm);
  bottomRight.spin(directionType::fwd, (vert - hori), velocityUnits::rpm);
}

void tankControl(int left, int right) {
  //left=left
  //right=right
  topLeft.spin(directionType::fwd, left, velocityUnits::pct);
  bottomLeft.spin(directionType::fwd, left, velocityUnits::pct);
  topRight.spin(directionType::fwd, right, velocityUnits::pct);
  bottomRight.spin(directionType::fwd, right, velocityUnits::pct);
}

void lift(motor m, bool up, bool down, int vel) {
  if (up) {
    m.spin(directionType::fwd, vel, velocityUnits::rpm);
  } else if (down) {
    m.spin(directionType::rev, vel, velocityUnits::rpm);
  } else {
    m.stop(brakeType::hold);
  }
}

double getSafeSonarDistance(sonar s, double mSecTime, distanceUnits units) {
  double startTime = Brain.timer(timeUnits::msec);
  //Distances that the sonar sensor records
  vector<double> distances;
  while (Brain.timer(timeUnits::msec) > startTime + mSecTime) {
    distances.push_back(s.distance(units));
  }

  double max[2] = { *distances.data(), *distances.data()};
  double min[2] = { *distances.data(), *distances.data()};
  double avg = 0;
  int size = 0; //Get size w/ 1 loop
  for (vector<double>::iterator it = distances.begin(); it != distances.end(); ++it) {
    avg += *it;
    if (*it > max[0]) {
      if (*it > max[1]) {
        max[0] = max[1];
        max[1] = *it;
      }
      else {
        max[0] = *it;
      }
    }
    else if (*it < min[0]) {
      if (*it < min[1]) {
        min[0] = min[1];
        min[1] = *it;
      }
      else {
        min[0] = *it;
      }
    }
    size++;
  }
  //Remove 2 maxes and 2 mins from avg
  return (avg - max[0] - max[1] - min[0] - min[1]) / (size - 4);
}

LocationHandler::LocationHandler() {
  loc = {0, 0};
  deg = 0;
}

LocationHandler::LocationHandler(location nLoc, double nDeg) {
  loc = nLoc;
  deg = nDeg;
}

void LocationHandler::calcDisp() {
  const float w = 13.5; // ASSUMING WIDTH = 13.5"
  //R=right position value
  //L=left position value
  //radius = w*(R+L) / (2*(R-L))
  double radius = (w * (topRight.position(turns) + topLeft.position(turns)) /
                  (2 * (topRight.position(turns) - topLeft.position(turns))));
  //yaw/deg changed = 180 * (R-L) / (w*pi)
  deg += (180 * (topRight.position(turns) - topLeft.position(turns))) /
         (pi * w);

  //Basic trig to get x,y location change
  loc.x += radius * cos(deg) - radius;
  loc.y += radius * sin(deg);
}