/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonomous.h                                              */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      10 Oct 2019                                               */
/*    Description:  Autonomous function definition                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/**
 * @brief Prior to ALL autons
*/
void init();

/**
 * @brief Auton to get a single cube
*/
void oneCube();

/**
 * @brief Auton for side blue (from stands)
*/
void blueSide();

/**
 * @brief Auton for side red (from stands)
*/
void redSide();

/**
 * @brief Auton for skills
*/
void skills();

/**
 * @brief debug Auton
*/
void debug();