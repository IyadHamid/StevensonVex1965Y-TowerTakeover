using namespace vex;

#pragma once

//Motor -> Distance: Gear ratio*Circumference
#define WHEEL_RATIO 25.8
//#define WHEEL_RATIO 24.6104
extern brain Brain;

// VEXcode devices
//Primary Controller
extern controller Controller1;
//Secondary Controller
extern controller Controller2;

//Top left drive motor
extern motor topLeft;
//Bottom left drive motor
extern motor bottomLeft;
//Top right drive motor
extern motor topRight;
//Bottom right drive motor
extern motor bottomRight;

//Left intake motor
extern motor intakeLeft;
//Right intake motor
extern motor intakeRight;
//Tray motor
extern motor cubeLift;
//Intake Lift motor
extern motor intakeLift;

//Left drive motors
extern motor_group leftDrive;
//Right drive motors
extern motor_group rightDrive;
//All the drive motors
extern motor_group allDrive;
//Both intake motors
extern motor_group intakes;

//Intertial sensor
extern inertial inert;
//Line sensor to "see" cubes in front of the intakes
extern line indexer;
//Sonar sensor in the back
extern sonar ultraSonic;
extern pot PotentiometerA;

//Speed multiplier
extern double speedMultiplier;
//Ambient light level in mV
extern int ambientLight;

//Struct with 1 bit bools
struct motorUsed {
  bool driveMotors : 1;
};
//Are motors used
extern motorUsed isUsed;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );