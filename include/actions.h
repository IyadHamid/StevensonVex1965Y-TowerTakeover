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
 * @brief redirect to gotoTower 
 */
void gotoTower2();
void gotoTower1();

/**
 * @brief set intake lift to a tower 
 * @param int tower (0 -default, 1 -low, 2-mid)
 */
void gotoTower(int);

/**
 * @brief intake control
 * @param int velocity pct
*/
void intake(int);
