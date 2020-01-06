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
 * @brief redirect to gotoTower with input of 2 
 */
void gotoTower2();

/**
 * @brief redirect to gotoTower with input of 1
 */
void gotoTower1();

/**
 * @brief set intake lift to a tower 
 * @param int tower (0 -default, 1 -low, 2-mid)
 */
void gotoTower(int);

/**
 * @brief redirect to stopIntake with input of 0
 */
void stopIntake();

/**
 * @brief intake control
 * @param int velocity pct
*/
void intake(int);
