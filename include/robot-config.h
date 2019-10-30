using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern motor frontLeft;
extern motor backLeft;
extern motor frontRight;
extern motor backRight;
extern motor intakeLeft;
extern motor intakeRight;
extern motor cubeLift;
extern motor intakeLift;
extern pot PotentiometerA;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );