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

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Gyro                 inertial      17              
// ArmPot               pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "Vision1.h"
#include "vex_units.h"
#include "Movement.cpp"
using namespace vex;

//A global instance of vex::brain used for printing to the V5 brain screen
//vex::brain       Brain;

// brain  Brain;

// VEXcode device constructors
vex::controller Controller1 = vex::controller();
vex::vision Vision       = vex::vision( PORT8   );

vex::motor LeftFront     = vex::motor(  PORT11,  true);
vex::motor LeftMiddle    = vex::motor(  PORT12,  false );
vex::motor LeftBack      = vex::motor(  PORT13,  true );

vex::motor RightFront    = vex::motor(  PORT18,  false );
vex::motor RightMiddle   = vex::motor(  PORT19,  true );
vex::motor RightBack     = vex::motor(  PORT20,  false );

vex::motor LiftMotor     = vex::motor(  PORT10,  true );
vex::motor IntakeMotor   = vex::motor(  PORT4    );

// A global instance of vex::competition
vex::competition Competition;
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