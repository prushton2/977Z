// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Gyro                 inertial      17              
// LiftPot              pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// gyro                 inertial      17              
// ArmPot               pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// gyro                 inertial      17              
// ---- END VEXCODE CONFIGURED DEVICES ----
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
#include "robot-config.h"
#include "motor-config.h"
// A global instance of vex::competition

bool running = false;
int ticks = 0;

Drivetrain driver;
Mech mech(0, 100); //The first integer is the lower limit of the lift, the second integer is the upper limit of the lift. This is temporarily disabled because it doesnt work
Auton auton;
UI ui;



void pre_auton( void ) {
  Controller1.Screen.setCursor(1, 1);
  while(!Competition.isEnabled()) {
    ui.swap();
    ui.renderDisplay();
  }
}

void autonomous( void ) {
  auton.auton = ui.auton;
  auton.Init();
}



void usercontrol( void ) {
  while (1) {
    driver.Drive(Controller1.Axis3.value(), 0);
    driver.Drive(Controller1.Axis2.value(), 1);

    mech.dLift( //This drives the lift. If both buttons are pressed at the same time, nothing happens
      (Controller1.ButtonR1.pressing() ? 60 : 0) + //The number in front of the colon is the move speed when pressing R1
      (Controller1.ButtonR2.pressing() ? -60 : 0) ); //The number in front of the colon is the move speed when pressing R2

    mech.dIntake( //This drives the intake. If both buttons are pressed at the same time, nothing happens
      (Controller1.ButtonL1.pressing() ? -90 : 0) + //The number in front of the colon is the move speed when pressing L1
      (Controller1.ButtonL2.pressing() ? 90 : 0) ); //The number in front of the colon is the move speed when pressing L2

    mech.dTilter( //This drives the intake. If both buttons are pressed at the same time, nothing happens
      (Controller1.ButtonX.pressing() ? -60 : 0) + //The number in front of the colon is the move speed when pressing L1
      (Controller1.ButtonB.pressing() ? 60 : 0) ); //The number in front of the colon is the move speed when pressing L2
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


