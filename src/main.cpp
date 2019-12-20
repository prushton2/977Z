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
bool developer = true;
void renderDisplay(int auton);
int swap();

void pre_auton( void ) {
  while(true) {
    auton = swap();
    renderDisplay(auton);
  }
}

void autonomous( void ) {
  runAutonomous(auton);
}



void usercontrol( void ) {
  while (1) {
    driveBot();
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
  Brain.Screen.print("Testing Autonomous");
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