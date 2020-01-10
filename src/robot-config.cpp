#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor topLeft      = motor(PORT2, ratio18_1, false);
motor bottomLeft   = motor(PORT3, ratio18_1, true);
motor topRight     = motor(PORT10, ratio18_1, true);
motor bottomRight  = motor(PORT9, ratio18_1, false);
motor intakeLeft   = motor(PORT19, ratio36_1, false);
motor intakeRight  = motor(PORT20, ratio36_1, true);
motor cubeLift     = motor(PORT16, ratio36_1, false);
motor intakeLift   = motor(PORT17, ratio36_1, true);

motor_group leftDrive(topLeft, bottomLeft);
motor_group rightDrive(topRight, bottomRight);
motor_group allDrive(topLeft, bottomLeft, topRight, bottomRight);
motor_group intakes(intakeLeft, intakeRight);

inertial inert     = inertial(PORT18);
pot PotentiometerA = pot(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  gyrometer.calibrate();
}