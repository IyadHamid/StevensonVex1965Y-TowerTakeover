/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       actions.h                                                 */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      1 Jan 2020                                                */
/*    Description:  Controls specific to this robot                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/


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
 * @param int tower (0 -default, 1 -low, 2-mid)
 */
void gotoTower(int);

/**
 * @brief redirect to gotoTower with input of 2 
 */
void gotoTower2();

/**
 * @brief redirect to gotoTower with input of 1
 */
void gotoTower1();

/**
 * @brief redirect to gotoTower with input of 0
 */
void gotoTower0();

/**
 * @brief intake control
 * @param int velocity in rpm
*/
void intake(int);

/**
 * @brief redirect to stopIntake with input of 0
 */
void stopIntake();

/**
 * @brief move distance (relative system)
 * @param double rotation to travel
 * @param double precision (set to 2)
 * @param rotationUnits units (set to degrees)
*/
void travel(double, double = 2, vex::rotationUnits = vex::rotationUnits::deg);

/**
 * @brief make the robot face angle (absolute system)
 * @param double degrees
 * @param double precsion (set to 1)
*/
void faceAngle(double, double = 1);

/**
 * @brief Puts cubes above the line sensor
*/
void putAllCubesAboveLine();

/**
 * @brief Puts a cube directly beetween the intakes
*/
void putCubeInIntakes();