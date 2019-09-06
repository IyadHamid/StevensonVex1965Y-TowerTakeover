/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Stevenson 1965Y (Iyad H)                                  */
/*    Created:      4 Aug 2019                                                */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "components.h"
#include "display.h"

using namespace vex;

// A global instance of competition
competition Competition;


void pre_auton( void ) {
}


void autonomous( void ) {
}


void usercontrol( void ) {

  //Device check
  //=========================== TBD NEED TO ADD ==============================
  devices dvs = devices();

  while (1) {
    if (dvs.number() != devices().number()) {
      for (int i = 0; i < dvs.number(); i++) {

      }
    }
  
    task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}


int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
                      
    while(1) {
      task::sleep(100);
    }    
}