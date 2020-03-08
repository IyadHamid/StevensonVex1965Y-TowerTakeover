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
#define TRAY_UP 1.7
//Put intake lift to the mid tower
#define MID_TOWER 1.85
//Put intake lift to the low tower
#define LOW_TOWER .9

void doArcade() {
  //normal arcade control
  arcadeControl(Controller1.Axis3.position() * speedMultiplier, 
                Controller1.Axis4.position() * speedMultiplier / 2);
}

void doSpeedArcade() {
  //normal arcade control
  arcadeControl(Controller1.Axis3.position(), 
                Controller1.Axis4.position());
}

void doTank() {
  tankControl(Controller1.Axis3.position() * speedMultiplier, 
              Controller1.Axis2.position() * speedMultiplier);
}

void doDrone() {
  //normal arcade control
  arcadeControl(Controller1.Axis3.position() * speedMultiplier, 
                Controller1.Axis1.position() * speedMultiplier / 1.2);
}

void setLift(int opt) {
  //Lock the intake lift
  intakeLift.stop(brakeType::hold);
  switch(opt) {
    case 1:
      intakes.spin(directionType::rev, 15, velocityUnits::rpm);
      //Needs interpolation to not launch cubes
      while (tray.position(rotationUnits::rev) < TRAY_UP) {
        tray.spin(directionType::fwd,
                      //40*cos((2*pi/7)*[pos])+40
                      60.0*cos(((2.0*pi)/7)*tray.position(rotationUnits::rev))+60.0,
                      velocityUnits::rpm);
      }
      tray.stop(brakeType::hold);
      intakes.stop();
      break;
    default:
      //Put the cube lift down and back off
      intakes.spin(directionType::rev, 80, velocityUnits::rpm);
      tray.rotateTo(0, rotationUnits::rev, 70, velocityUnits::rpm, false);
      allDrive.rotateFor(directionType::rev, 7 * WHEEL_RATIO, rotationUnits::deg, 80, velocityUnits::rpm);
      intakes.stop();
      break;
  }
}

int setLift1() {
  setLift(1);
  return 0;
}


int setLift0() {
  setLift(0);
  return 0;
}

void gotoTower(int opt, double custom) {
  switch (opt) {
    case 1: //Low
      //Lower the speed
      speedMultiplier = .3;
      Brain.Screen.clearScreen(red);
      intakeLift.rotateTo(LOW_TOWER, rotationUnits::rev, 100, velocityUnits::rpm, true);
      intakeLift.stop(brakeType::hold);
      Brain.Screen.clearScreen();
      break;
    case 2: //Mid
      speedMultiplier = .3;
      Brain.Screen.clearScreen(green);
      intakeLift.rotateTo(MID_TOWER, rotationUnits::rev, 100, velocityUnits::rpm, true);
      intakeLift.stop(brakeType::hold);
      Brain.Screen.clearScreen();
      break;
    case 0: //Reset
      speedMultiplier = DEFAULT_SPEED_MULTIPLIER;
      Brain.Screen.clearScreen(blue);
      //interpolate to not slam intakes into robot body
      while (intakeLift.position(rotationUnits::rev) > .01) {
        intakeLift.spin(directionType::rev,
                        //40*tanh(8*([pos]-.3))+40
                        40*tanh(12*(intakeLift.position(rotationUnits::rev)-.1))+40,
                        velocityUnits::rpm);
      }
      intakeLift.stop(brakeType::coast);
      Brain.Screen.clearScreen();
      break;
    case 3:
      intakeLift.rotateTo(custom, rotationUnits::rev, 100, velocityUnits::rpm, true);
      intakeLift.stop(brakeType::hold);
  }
}

int gotoTower2() {
  gotoTower(2);
  return 0;
}

int gotoTower1() {
  gotoTower(1);
  return 0;
}

int gotoTower0() {
  gotoTower(0);
  return 0;
}

void intake(double vel, velocityUnits units) {
  if (vel == 0) {
    intakes.stop(brakeType::hold);
  } 
  else {
    //Make the treads of the intakes to match
    if (intakeLeft.position(rotationUnits::deg) < intakeRight.position(rotationUnits::deg)) {
      intakeLeft.spin(directionType::fwd, vel, units);
      intakeRight.spin(directionType::fwd, vel - 10, units);
    }
    else {
      intakeLeft.spin(directionType::fwd, vel - 10, units);
      intakeRight.spin(directionType::fwd, vel, units);
    }
  }
}

void intake(double vel, voltageUnits units) {
  if (vel == 0) {
    intakes.stop(brakeType::hold);
  } 
  else {
    //Make the treads of the intakes to match
    if (intakeLeft.position(rotationUnits::deg) < intakeRight.position(rotationUnits::deg)) {
      intakeLeft.spin(directionType::fwd, vel, units);
      intakeRight.spin(directionType::fwd, vel - 10, units);
    }
    else {
      intakeLeft.spin(directionType::fwd, vel - 10, units);
      intakeRight.spin(directionType::fwd, vel, units);
    }
  }
}

void stopIntake() {
  intake(0);
}

void travel(double amount, double vel, double precision, motor encoderMotor, motor_group driveGroup, rotationUnits rotUnits, bool verbose) {
  //Function is relative
  encoderMotor.resetRotation();

  //Convert to revolutions
  if (rotUnits == rotationUnits::rev) {
    amount *= 360.0;
    precision *= 360.0;
  }

  //Until within range of precision
  while (!(encoderMotor.rotation(rotationUnits::deg) < amount + precision &&
           encoderMotor.rotation(rotationUnits::deg) > amount - precision)) {
    if (verbose) {
      Brain.Screen.printAt(0,75,"amt:%lf   encoder:%lf        ", amount, encoderMotor.rotation(rotationUnits::rev));
      Brain.Screen.printAt(0,200,"%lf  %lf", amount - precision, amount + precision);    
    }
    //fn = displacement (revolutions) to target
    double fn = amount - encoderMotor.rotation(rotationUnits::deg);
    if (verbose) {
      Brain.Screen.printAt(0,100,"Dist to move: %lf       ", fn);
    }
    //fn can be represented as a piecewise function:
    //      / .001(x^2) + 100, x >= 0
    //fn = {
    //      \ -.001(x^2) + 100, x < 0
    fn = (fn < 0 ? -1 : 1)* (.00001 * pow(fn, 2) + .15);
    //wrap fn in tanh (makes it into a modified sigmoid function)
    //fn = vel * tanh((|x|/x) * (.00001(x^2) + .15))
    fn = vel * tanh(fn);
    //fn is used to interpolate the velocoity of the robot in rpm (for motors)
    if (verbose) {
      Brain.Screen.printAt(0,125,"dps: %lf       ", fn);
    }
    driveGroup.spin(directionType::fwd, fn, velocityUnits::dps);
  }
  driveGroup.stop(brakeType::brake);
}

int travel(void * inputs) {
  convertTravelInputs cti;
  cti.voidptr = inputs;
  travel(cti.inputptr->dist, cti.inputptr->vel, cti.inputptr->precision, cti.inputptr->encoderMotor, cti.inputptr->motorGroup, cti.inputptr->rUnits, false);
  return 0;
}

void sCurve(double vel, double dist, double curve, motor_group side, motor_group other, motor encoderMotor, bool verbose) {

  encoderMotor.resetRotation();
  double rot = encoderMotor.rotation(rotationUnits::rev);
  double fn;
  double deg = inert.heading();
  double precision =  15;
  const int pR = (int)(deg + precision) % 360; //Right boundry
  const int pL = (int)(deg + 360 - ((int)precision % 360)) % 360; //Left boundry

  while (!(rot <= -1 &&
            ((pL < deg && deg < pR) ||
             (deg < pR && pR < pL) ||
             (pR < pL && pL < deg)))) {
               
    deg = inert.heading();
    fn = -vel * tanh(curve * (-rot - dist)) + vel + 5;
    fn *= -1;
    if (verbose) {
      Brain.Screen.printAt(0, 50, "Rot: %f Deg: %f    ", rot, deg);
      Brain.Screen.printAt(0, 75, "left rpm: %f     ", fn);
    }
    other.spin(directionType::fwd, fn, velocityUnits::rpm);
    //Flip for other side f(-x + 2)
    fn = -vel * tanh(curve * ((rot + dist * 2) - dist)) + vel + 5;
    fn *= -1;
    if (verbose) {
      Brain.Screen.printAt(0, 100, "right rpm: %f     ", fn);
    }
    side.spin(directionType::fwd, fn, velocityUnits::rpm);
    rot = encoderMotor.rotation(rotationUnits::rev);
  }
  allDrive.stop(brakeType::brake);
  faceAngle(0, vel);
}

void jCurve(double vel, double ang, double curve, double dist, double offset, motor_group inside, motor_group outside, double precision, bool verbose) {
  bottomLeft.resetRotation();
  bottomRight.resetPosition();
  double rot = bottomLeft.rotation(rotationUnits::rev) + bottomRight.rotation(rotationUnits::rev);
  double fn;
  double deg = inert.heading();
  const int pR = (int)(ang + precision * 2) % 360; //Right boundry
  const int pL = (int)(ang + 360 - ((int)precision * 2 % 360)) % 360; //Left boundry

  while (!((pL < deg && deg < pR) ||
           (deg < pR && pR < pL) ||
           (pR < pL && pL < deg))) {
    rot = bottomLeft.rotation(rotationUnits::rev) + bottomRight.rotation(rotationUnits::rev);
    deg = inert.heading();
    fn = -vel * tanh(curve * (offset + rot));
    if (verbose) {
      Brain.Screen.printAt(0, 50, "Rot: %f", rot);
      Brain.Screen.printAt(0, 75, "Left dps: %f", fn);
      Brain.Screen.printAt(0, 100, "Deg: %f", deg);
    }
    inside.spin(directionType::fwd, fn, velocityUnits::dps);
    fn = -vel * tanh(curve * (offset + rot + dist));
    outside.spin(directionType::fwd, fn, velocityUnits::dps);

  }
  allDrive.stop();
  faceAngle(ang, 50, precision);
}

void faceAngle(double deg, double vel, double precision, bool verbose) {
  //Get heading within [0,360)
  double dir = (int)round(inert.heading()) % 360; //Direction heading integer
  double fn;                                      //Math function
  double l;                                       //left rotation to deg
  double r;                                       //right rotation to deg

  //Account for negative angles
  deg = (int)round(deg + 360) % 360;
  //precision
  const int pR = (int)(deg + precision) % 360; //Right boundy
  const int pL = (int)(deg + 360 - ((int)precision % 360)) % 360; //Left boundry

  //Until within range of precision (in a circle [0,360))
  while (!((pL < dir && dir < pR) ||
          (dir < pR && pR < pL) ||
          (pR < pL && pL < dir))) {
    dir = (int)round(inert.heading()) % 360;
    if (verbose) {
      Brain.Screen.printAt(0,75,"deg:%lf   heading:%lf          ", deg, inert.heading());
      Brain.Screen.printAt(0,100,"dir:%lf          ", dir);
    }
    l = (int)round((360+deg) - dir) % 360; //Left rotation
    r = (int)round((360+dir) - deg) % 360; //Right rotation
    //fn = angular displacement (degree) from target degree
    fn = r > l ? l : -r;
    if (verbose) {
      Brain.Screen.printAt(0,125,"Angle to rot: %lf       ", fn);
    }
    //fn can be represented as a piecewise function:
    //      / .001(x^2) + 300, x >= 0
    //fn = {
    //      \ -.001(x^2) + 300, x < 0
    fn = (.0001 * fn * fn);
    //wrap fn in tanh (makes it into a modified sigmoid function)
    //fn = vel * tanh((|x|/x) * .001((x^2) + 300))
    
    fn = (r < l ? -1 : 1) * ((vel * tanh(fn)) + 5);
    //fn is used to interpolate the angular velocity of the robot rotating in rpm (for motors)
    if (verbose) {
      Brain.Screen.printAt(0,150,"rpm on left: %lf", fn);
    }
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