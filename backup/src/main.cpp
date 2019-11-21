/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Robotics                                         */
/*    Created:      Thu May 16 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//#include "Config.cpp"
#include "vex.h"
#include "Vision1.h"
#include "vex_units.h"
//#include "Custom_Controls.cpp"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::controller Controller = vex::controller();
vex::vision Vision       = vex::vision( PORT8   );

vex::motor LeftFront     = vex::motor(  PORT11  );
vex::motor LeftMiddle    = vex::motor(  PORT12,  true );
vex::motor LeftBack      = vex::motor(  PORT13   );

vex::motor RightFront    = vex::motor(  PORT18,  true );
vex::motor RightMiddle   = vex::motor(  PORT19   );
vex::motor RightBack     = vex::motor(  PORT20,  true );

vex::motor LiftMotor     = vex::motor(  PORT10,  true );
vex::motor IntakeMotor   = vex::motor(  PORT9    );

// A global instance of vex::competition
vex::competition Competition;


int auton = 0;
bool running = false;
int ticks = 0;
/*
01 - armup
02 - armdown
11 - buttonR1
12 - buttonR2
21 - false
22 - true

*/
void Drive(int speed, int side) {
  if(side==0) {
    LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
    LeftMiddle.spin(directionType::fwd, speed, velocityUnits::pct);
    LeftBack.spin(directionType::fwd, speed, velocityUnits::pct);
  } else if(side==1) {
    RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
    RightMiddle.spin(directionType::fwd, speed, velocityUnits::pct);
    RightBack.spin(directionType::fwd, speed, velocityUnits::pct); 
  } else {
    LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
    LeftMiddle.spin(directionType::fwd, speed, velocityUnits::pct);
    LeftBack.spin(directionType::fwd, speed, velocityUnits::pct);

    RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
    RightMiddle.spin(directionType::fwd, speed, velocityUnits::pct);
    RightBack.spin(directionType::fwd, speed, velocityUnits::pct); 
  }
}
bool MoveEn(double distance, int speed, bool autocorrect) {
  LeftBack.resetRotation();
  RightBack.resetRotation();
  while(LeftBack.rotation(rotationUnits::deg) <= distance) {
    if (LeftBack.rotation(rotationUnits::deg) < RightBack.rotation(rotationUnits::deg) && autocorrect) {
      Drive(speed, 0);
      Drive(speed + (speed/3), 1);
    }
    else if (LeftBack.rotation(rotationUnits::deg) > RightBack.rotation(rotationUnits::deg) && autocorrect) {
      Drive(speed + (speed/3), 0);
      Drive(speed, 1);
    }
    else {
      Drive(speed, 0);
      Drive(speed, 1);
    }
  }
  LeftBack.resetRotation();
  RightBack.resetRotation();
  Drive(0, 2);
  return true;
}

void moveLiftTo(int encoderVal, int speed) {
  while(true) {
    if(LiftMotor.rotation(rotationUnits::deg) > encoderVal - 2) {
      LiftMotor.spin(directionType::fwd, -1*speed, velocityUnits::pct);
    }
    else if(LiftMotor.rotation(rotationUnits::deg) < encoderVal + 2) {
      LiftMotor.spin(directionType::fwd, speed, velocityUnits::pct);
    }
    else {
      return;
    }
  }
}


void render() {
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
    Brain.Screen.print("Near Autonomous");
    Brain.Screen.setCursor(10, 5);
    if (auton == 4) {Brain.Screen.setPenColor(color::purple);}
    else {Brain.Screen.setPenColor(color::blue);}
    Brain.Screen.print("Far Autonomous");
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
    Brain.Screen.print("Near Autonomous");
    Brain.Screen.setCursor(10, 30);
    if (auton == 5) {Brain.Screen.setPenColor(color::purple);}
    else {Brain.Screen.setPenColor(color::red);}
    Brain.Screen.print("Far Autonomous");
    Brain.Screen.setPenColor(color::white);
}

void swap() {
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
}



void pre_auton( void ) {
  while(!competition().isEnabled() || true) {
    swap();
    render();
  }
}

void autonomous( void ) {
  running = true;
  task::sleep(1000);
  switch (auton) {
    case 0:
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("No Auton");
      break;
    case 1:
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Testing Autonomous");
      MoveEn(4.5 * 360, -50, true);
      break;
    case 2:
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Near Blue");
      break;
    case 3:
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Near Red");
      break;
    case 4:
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Far Blue");
      break;
    case 5:
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Far Red");
      break;
  }
}
void trackColor() {
  int posX = 0;
  int posY = 0;
  int visionSpeedLeft = 0;
  int visionSpeedRight = 0;
  //while(Controller.ButtonA.pressing()) { //Custom Charge with color sensing
    visionSpeedLeft = Controller.Axis3.value();
    visionSpeedRight = Controller.Axis3.value();
    if (competition().isDriverControl()) {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 0);
      Brain.Screen.print("Objects: ");
      Brain.Screen.print(Vision.takeSnapshot(SIG_2));
      Brain.Screen.print("  X: ");
      Brain.Screen.print(Vision.largestObject.centerX);
      Brain.Screen.print("  Y: ");
      Brain.Screen.print(Vision.largestObject.centerY);
      Brain.Screen.newLine();
      Brain.Screen.print("Stored Pos: ");
      Brain.Screen.print("  X: ");
      Brain.Screen.print(posX);
      Brain.Screen.print("  Y: ");
      Brain.Screen.print(posY);
    }
    if ((Vision.largestObject.centerX != 0) && (Vision.largestObject.centerY != 0)) {
      posX = Vision.largestObject.centerX;
      posY = Vision.largestObject.centerY;
    }
    if (posX < 140) {
      Drive(-7+Controller.Axis3.value(), 0);
      Drive(7+Controller.Axis3.value(), 1);
      Vision.setLedColor(255, 255, 0);
    }
    else if (posX > 160) {
      Drive(7+Controller.Axis3.value(), 0);
      Drive(-7+Controller.Axis3.value(), 1);
      Vision.setLedColor(0, 255, 255);
    }
    else if ((posX  > 140) && (posX < 160)) {
      Drive(Controller.Axis3.value(), 2);
      Vision.setLedColor(0, 255, 0);
    }
  //}
}


void usercontrol( void ) {

  // User control code here, inside the loop
  while (1) {
    Vision.setLedColor(0, 0, 255);

    Drive(Controller.Axis3.value()*.7, 0);
    Drive(Controller.Axis2.value()*.7, 1);

    if(Controller.ButtonR1.pressing()) {
      LiftMotor.spin(directionType::fwd, -100, velocityUnits::pct);
    } else if(Controller.ButtonR2.pressing()) {
      LiftMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    } else {
      LiftMotor.stop();
    }

    if (Controller.ButtonRight.pressing()) {
      MoveEn(100, 50, true);
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    ticks++;
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    //render();
    pre_auton();
    //Prevent main from exiting with an infinite loop.                        
    if(Controller.ButtonDown.pressing()) {
      autonomous();
    }
    vex::task::sleep(10);//Sleep the task for a short amount of time to prevent wasted resources.
      
}