#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor frontLeft = motor(PORT1, ratio18_1, false);
motor backLeft = motor(PORT2, ratio18_1, true);
motor frontRight = motor(PORT10, ratio18_1, true);
motor backRight = motor(PORT9, ratio18_1, false);
motor intakeLeft = motor(PORT5, ratio18_1, false);
motor intakeRight = motor(PORT6, ratio18_1, false);
motor cubeLift = motor(PORT15, ratio18_1, false);
motor intakeLift = motor(PORT16, ratio18_1, false);
pot PotentiometerA = pot(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}