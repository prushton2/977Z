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
#include "Movement.h"
// A global instance of vex::competition

 

int auton = 0;
bool running = false;
int ticks = 0;

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
  runAutonomous(auton);
}



void usercontrol( void ) {
  // Red1();
  while (1) {
    Controller1.Screen.print(IntakeMotor.temperature(temperatureUnits::celsius));    
    driveBot();
    driveClaw();
    driveArm();
    if(Controller1.ButtonA.pressing()) {
      
    }
    if(Controller1.ButtonX.pressing()) {
      liftArmTo(78, 15, true);
    }
    if(Controller1.ButtonB.pressing()) {
      liftArmTo(72, 15, true);
    }
    if(Controller1.ButtonUp.pressing()) {
      liftArmTo(75, 15, true);
    }
    if(Controller1.ButtonDown.pressing()) {
      liftArmTo(68, 15, true);
    }
    task::sleep(10);
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