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
 * @brief move distance
 * @param double distance travel by left
 * @param double distance travel by right
 * @param double time to complete (sec)
 * @param bool wait?
*/
void travel(double, double, double, bool = true);

/**
 * @brief move distance
 * @param double distance to travel
 * @param double time to complete
 * @param bool wait?
*/
void travel(double, double, bool = true);