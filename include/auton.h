/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonomous.h                                              */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      10 Oct 2019                                               */
/*    Description:  Autonomous function definition                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once 

/**
 * @brief Prior to ALL autons
*/
void init();

/**
 * @brief Auton to get a single cube
*/
void oneCube();

/**
 * @brief 4 point for side red
*/
void blue4Cube();

/**
 * @brief Auton for side blue
*/
void blueSide();

/**
 * @brief 4 point for side red
*/
void red4Cube();

/**
 * @brief Auton for side red
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