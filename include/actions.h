/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       actions.h                                                 */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      1 Jan 2020                                                */
/*    Description:  Controls specific to this robot                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once
#include "vex.h"

/**
 * @brief callback for arcade control
 */
void doArcade();

/**
 * @brief callback for arcade controls with no limits
 */
void doSpeedArcade();

/**
 * @brief callback for tank control
 */
void doTank();

/**
 * @brief callback for drone control
 */
void doDrone();

/**
 * @brief set intake lift to a tower 
 * @param int lift location (0 -back, 1 -forward)
 */
void setLift(int);

/**
 * @brief redirect to setLift with input of 1
 */
void setLift1();

/**
 * @brief redirect to setLift with input of 0
 */
void setLift0();

/**
 * @brief set intake lift to a tower 
 * @param int tower (0 -default, 1 -low, 2 -mid, 3 -custom)
 * @param double custom amount (set to 0.0)
 */
void gotoTower(int, double = 0.0);

/**
 * @brief redirect to gotoTower with input of 2 
 */
int gotoTower2();

/**
 * @brief redirect to gotoTower with input of 1
 */
int gotoTower1();

/**
 * @brief redirect to gotoTower with input of 0
 */
int gotoTower0();

/**
 * @brief intake control
 * @param int velocity in pct
*/
void intake(double, vex::velocityUnits = vex::velocityUnits::pct);

/**
 * @brief intake control with voltage
 * @param int voltage
*/
void intake(double, vex::voltageUnits);

/**
 * @brief redirect to stopIntake with input of 0
 */
void stopIntake();

/**
 * @brief move distance (relative system)
 * @param double rotation to travel
 * @param double velocity in dps (set to 500)
 * @param double precision (set to 2)
 * @param motor encoder motor (set to bottomLeft)
 * @param motor_group motor group (set to allDrive)
 * @param rotationUnits units (set to degrees)
 * @param bool verbose (set to true)
*/
void travel(double, double = 500, double = 2, vex::motor = bottomLeft, vex::motor_group = allDrive, vex::rotationUnits = vex::rotationUnits::deg, bool = true);

struct travelInputs {
  double dist;
  double vel;
  double precision;
  motor encoderMotor;
  motor_group motorGroup;
  rotationUnits rUnits;
};

void sCurve();

union convertTravelInputs {
  travelInputs * inputptr;
  void * voidptr;
};

/**
 * @brief Task redirector to travel
 * @param void * (travelInputs *)
 * @return int 0
*/
int travel(void *);

/**
 * @brief make the robot face angle (absolute system)
 * @param double degrees
 * @param double percesion (set to 1)
 * @param bool verbose (set to true)
*/
void faceAngle(double, double = 60, double = 1, bool = true);

/**
 * @brief Puts cubes above the line sensor
*/
void putAllCubesAboveLine();

/**
 * @brief Puts a cube directly beetween the intakes
*/
void putCubeInIntakes();