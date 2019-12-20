/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Not You probably                                          */
/*    Created:      Thu May 16 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//#include "Config.cpp"
#include "vex.h"
#include "vex_units.h"
#include "Movement.h"
#include "ConfigInstances.cpp"
using namespace vex;

//A global instance of vex::brain used for printing to the V5 brain screen
//vex::brain       Brain;

// brain  Brain;

// VEXcode device constructors

//Some sensor instances are mande in the robot-config.h file

int auton = 0;
bool running = false;
int ticks = 0;
bool developer = true;

void pre_auton( void ) {
  
}

void autonomous( void ) {

}



void usercontrol( void ) {
  while (1) {
    
  }
}


int main() {
  //Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );
  //render();
  pre_auton();
  //Prevent main from exiting with an infinite loop.                        

  vex::task::sleep(10);//Sleep the task for a short amount of time to prevent wasted resources.
}