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

 

int auton = 0;
bool running = false;
int ticks = 0;

Drivetrain driver;
Mech mech(0, 100); //The first integer is the lower limit of the lift, the second integer is the upper limit of the lift.

void renderDisplay(int auton);
int swap();

void pre_auton( void ) {
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.clearLine(1);
  Controller1.Screen.print("Starting...");
  inertial::quaternion  Inertial_quaternion;
  Gyro.calibrate();
  
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Gyro");

  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Calibrating Gyro");

  while(Gyro.isCalibrating()) {
    task::sleep(100);
  }

  Brain.Screen.clearLine(1);
  Controller1.Screen.clearLine(1);
  while(!Competition.isEnabled()) {
    auton = swap();
    renderDisplay(auton);
    
  }
}

void autonomous( void ) {
}



void usercontrol( void ) {
  // Red1();
  while (1) {
    driver.Drive(Controller1.Axis3.value(), 0);
    driver.Drive(Controller1.Axis2.value(), 1);

    mech.dLift( //This drives the lift. If both buttons are pressed at the same time, nothing happens
      (Controller1.ButtonR1.pressing() ? 60 : 0) + //The number in front of the colon is the move speed when pressing R1
      (Controller1.ButtonR2.pressing() ? -60 : 0) ); //The number in front of the colon is the move speed when pressing R2

    mech.dIntake( //This drives the intake. If both buttons are pressed at the same time, nothing happens
      (Controller1.ButtonL1.pressing() ? 60 : 0) + //The number in front of the colon is the move speed when pressing L1
      (Controller1.ButtonL2.pressing() ? -60 : 0) ); //The number in front of the colon is the move speed when pressing L2

    mech.dTilter( //This drives the intake. If both buttons are pressed at the same time, nothing happens
      (Controller1.ButtonX.pressing() ? 60 : 0) + //The number in front of the colon is the move speed when pressing L1
      (Controller1.ButtonB.pressing() ? -60 : 0) ); //The number in front of the colon is the move speed when pressing L2

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


void renderDisplay(int auton) {
  // if(developer) {}
  Brain.Screen.setPenColor(color::blue);
  Brain.Screen.drawLine(0, 73, 250, 73);
  Brain.Screen.drawLine(0, 146, 250, 146);

  Brain.Screen.setCursor(2, 5);//blue
  if (auton == 0) {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::white);}
  Brain.Screen.print("No Autonomous");
  Brain.Screen.setPenColor(color::blue);
  Brain.Screen.setCursor(6, 5);
  if (auton == 2) {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::blue);}
  Brain.Screen.print("Large Autonomous");
  Brain.Screen.setCursor(10, 5);
  if (auton == 4) {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::blue);}
  Brain.Screen.print("Small Autonomous");
  Brain.Screen.setPenColor(color::white);

  Brain.Screen.setPenColor(color::white);
  Brain.Screen.drawLine(250, 0, 250, 250);
  
  Brain.Screen.setPenColor(color::red);//red
  Brain.Screen.drawLine(250, 73, 500, 73);
  Brain.Screen.drawLine(250, 146, 500, 146);
  Brain.Screen.setCursor(2, 30);
  if (auton == 1) {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::white);}
  Brain.Screen.print("Skills Autonomous");
  Brain.Screen.setCursor(6, 30);
  if (auton == 3) {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::red);}
  Brain.Screen.print("Large Autonomous");
  Brain.Screen.setCursor(10, 30);
  if (auton == 5) {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::red);}
  Brain.Screen.print("Small Autonomous");
  Brain.Screen.setPenColor(color::white);
}

int swap() {
  if((Brain.Screen.yPosition() < 73) && (Brain.Screen.xPosition() < 250)) {
    auton = 0;
  }
  else if ((Brain.Screen.yPosition() < 73) && (Brain.Screen.xPosition() > 250)) {
    auton = 1;
  }
  else if ((Brain.Screen.yPosition() > 73) && (Brain.Screen.yPosition() < 146) && (Brain.Screen.xPosition() < 250)) {
    auton = 2;
  }
  else if ((Brain.Screen.yPosition() > 73) && (Brain.Screen.yPosition() < 146) && (Brain.Screen.xPosition() > 250)) {
    auton = 3;
  }
  else if ((Brain.Screen.yPosition() > 73) && (Brain.Screen.xPosition() < 250)) {
    auton = 4;
  }
  else if ((Brain.Screen.yPosition() > 73) && (Brain.Screen.xPosition() > 250)) {
    auton = 5;
  }
  else {
    auton = 6;
  }
  return auton;
}