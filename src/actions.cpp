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
#include "controls.h"
#include "common.h"
#include "robot-config.h"

//Put the tray to be perpendicular to the floor
#define CUBELIFT_UP 2.85
//Put the tray to the middle
#define CUBELIFT_MID 1.6
//Put intake lift to the mid tower
#define MID_TOWER 1.25
//Put intake lift to the low tower
#define LOW_TOWER .95

void doArcade() {
  //normal arcade control
  arcadeControl(Controller1.Axis3.position() * speedMultiplier, 
                Controller1.Axis4.position() * speedMultiplier / 1.2);
}

void setLift(int opt) {
  //Lock the intake lift
  intakeLift.stop(brakeType::hold);
  switch(opt) {
    case 1:
      intakes.spin(directionType::rev, 15, velocityUnits::rpm);
      //Needs interpolation to not launch cubes
      while (cubeLift.position(rotationUnits::rev) < 2.6) {
        cubeLift.spin(directionType::fwd,
                      //40*cos((2*pi/7)*[pos])+40
                      40.0*cos(((2.0*pi)/7)*cubeLift.position(rotationUnits::rev))+40,
                      velocityUnits::rpm);
      }
      cubeLift.stop(brakeType::hold);
      intakes.stop();
      break;
    default:
      //Put the cube lift down and back off
      intakes.spin(directionType::rev, 80, velocityUnits::rpm);
      cubeLift.rotateTo(0, rotationUnits::rev, 70, velocityUnits::rpm, false);
      allDrive.rotateFor(directionType::rev, 7 * WHEEL_RATIO, rotationUnits::deg, 80, velocityUnits::rpm);
      intakes.stop();
      break;
  }
}

void setLift1() {
  setLift(1);
}


void setLift0() {
  setLift(0);
}

void gotoTower(int opt) {
  switch (opt) {
    case 1: //Low
      //Lower the speed
      speedMultiplier = .3;
      Brain.Screen.clearScreen(red);
      //Move tray out of the way
      cubeLift.rotateTo(CUBELIFT_MID, rotationUnits::rev, 100, velocityUnits::pct, false);
      this_thread::sleep_for(1); //Sleep for 1 tick
      intakeLift.rotateTo(LOW_TOWER, rotationUnits::rev, 50, velocityUnits::rpm, true);
      intakeLift.stop(brakeType::hold);
      Brain.Screen.clearScreen();
      break;
    case 2: //Mid
      speedMultiplier = .3;
      Brain.Screen.clearScreen(green);
      //Move tray out of the way
      cubeLift.rotateTo(CUBELIFT_MID, rotationUnits::rev, 100, velocityUnits::pct, false);
      this_thread::sleep_for(1); //Sleep for 1 tick
      intakeLift.rotateTo(MID_TOWER, rotationUnits::rev, 50, velocityUnits::rpm, true);
      intakeLift.stop(brakeType::hold);
      Brain.Screen.clearScreen();
      break;
    default: //Reset
      speedMultiplier = .8;
      Brain.Screen.clearScreen(blue);
      //interpolate to not slam intakes into robot body
      while (intakeLift.position(rotationUnits::rev) > .01) {
        intakeLift.spin(directionType::rev,
                        //40*tanh(4*([pos]-.4))+40
                        40*tanh(4*(intakeLift.position(rotationUnits::rev)-.4))+40,
                        velocityUnits::rpm);
        //start to move tray down after intake lift has gone down enough
        if (intakeLift.position(rotationUnits::rev) < 1 && !cubeLift.isSpinning()) {
          cubeLift.rotateTo(0, rotationUnits::rev);     
        }
      }
      intakeLift.stop(brakeType::coast);
      cubeLift.rotateTo(0, rotationUnits::rev);
      Brain.Screen.clearScreen();
      break;
  }
}

void gotoTower2() {
  gotoTower(2);
}

void gotoTower1() {
  gotoTower(1);
}

void gotoTower0() {
  gotoTower(0);
}

void intake(int vel) {
  if (vel == 0) {
    intakes.stop(brakeType::hold);
  } 
  else {
    //Make the treads of the intakes to match
    if (intakeLeft.position(rotationUnits::deg) < intakeRight.position(rotationUnits::deg)) {
      intakeLeft.spin(directionType::fwd, vel, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, vel - 10, velocityUnits::pct);
    }
    else {
      intakeLeft.spin(directionType::fwd, vel - 10, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, vel, velocityUnits::pct);
    }
  }
}

void stopIntake() {
  intake(0);
}

void travel(double amount, double vel, double precision, rotationUnits rotUnits) {
  //Function is relative
  bottomLeft.resetRotation();

  //Convert to revolutions
  if (rotUnits == rotationUnits::rev) {
    amount *= 360.0;
    precision *= 360.0;
  }

  //Until within range of precision
  while (!(bottomLeft.rotation(rotationUnits::deg) < amount + precision &&
           bottomLeft.rotation(rotationUnits::deg) > amount - precision)) {
    Brain.Screen.printAt(0,75,"amt:%lf   encoder:%lf        ", amount, bottomLeft.rotation(rotationUnits::rev));
    Brain.Screen.printAt(0,200,"%lf  %lf", amount - precision, amount + precision);    
    //fn = displacement (revolutions) to target
    double fn = amount - bottomLeft.rotation(rotationUnits::deg);
    Brain.Screen.printAt(0,100,"Dist to move: %lf       ", fn);
    //fn can be represented as a piecewise function:
    //      / .001(x^2) + 100, x >= 0
    //fn = {
    //      \ -.001(x^2) + 100, x < 0
    fn = (fn < 0 ? -1 : 1)* (.00001 * pow(fn, 2) + .15);
    //wrap fn in tanh (makes it into a modified sigmoid function)
    //fn = vel * tanh((|x|/x) * (.00001(x^2) + .15))
    fn = vel * tanh(fn);
    //fn is used to interpolate the velocoity of the robot in rpm (for motors)
    Brain.Screen.printAt(0,125,"dps: %lf       ", fn);
    allDrive.spin(directionType::fwd, fn, velocityUnits::dps);
  }
  allDrive.stop(brakeType::brake);
}

void faceAngle(double deg, double vel, double precision) {
  //Get heading within [0,360)
  double dir = (int)round(inert.heading()) % 360; //Direction heading integer
  double fn;                                      //Math function
  double l;                                       //left rotation to deg
  double r;                                       //right rotation to deg

  //Account for negative angles
  deg = (int)round(deg + 360) % 360;
  //precision
  const int pR = (int)(deg + precision) % 360; //Right boundy
  const int pL = (int)(deg + 360 - ((int)precision % 360)) % 360; //Right boundry

  //Until within range of precision (in a circle [0,360))
  while (!((pL < dir && dir < pR) ||
          (dir < pR && pR < pL) ||
          (pR < pL && pL < dir))) {
    dir = (int)round(inert.heading()) % 360;
    Brain.Screen.printAt(0,75,"deg:%lf   heading:%lf          ", deg, inert.heading());
    Brain.Screen.printAt(0,100,"dir:%lf          ", dir);
    l = (int)round((360+deg) - dir) % 360; //Left rotation
    r = (int)round((360+dir) - deg) % 360; //Right rotation
    //fn = angular displacement (degree) from target degree
    fn = r > l ? l : -r;
    Brain.Screen.printAt(0,125,"Angle to rot: %lf       ", fn);
    //fn can be represented as a piecewise function:
    //      / .001(x^2) + 100, x >= 0
    //fn = {
    //      \ -.001(x^2) + 100, x < 0
    fn = (fn < 0 ? -1 : 1)* .001 * (pow(fn, 2) + 100);
    //wrap fn in tanh (makes it into a modified sigmoid function)
    //fn = vel * tanh((|x|/x) * .001((x^2) + 100))
    fn = vel * tanh(fn);
    //fn is used to interpolate the angular velocity of the robot rotating in rpm (for motors)
    Brain.Screen.printAt(0,150,"rpm on left: %lf", fn);
    leftDrive.spin(directionType::fwd, fn, velocityUnits::rpm);
    rightDrive.spin(directionType::rev, fn, velocityUnits::rpm);
  }
  allDrive.stop(brakeType::brake);
}

void putAllCubesAboveLine() {
  Brain.Screen.printAt(0,50,"ambient: %d        ", ambientLight);
  Brain.Screen.printAt(0,75,"light: %d        ", indexer.value(analogUnits::mV));
  while (indexer.value(analogUnits::mV) < ambientLight - 10) {
    Brain.Screen.printAt(0,75,"light: %d        ", indexer.value(analogUnits::mV));
    intakes.spin(directionType::fwd, 30, velocityUnits::rpm);
  }
  intakes.stop();
}

void putCubeInIntakes() {
  putAllCubesAboveLine();
  intakes.rotateFor(directionType::rev, .1, rotationUnits::rev, false);
}

void light() {
  Brain.ThreeWirePort.A.set(true);
  asm("");
}