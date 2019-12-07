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
// ArmPot               pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "Vision1.h"
#include "vex_units.h"
using namespace vex;

//A global instance of vex::brain used for printing to the V5 brain screen
//vex::brain       Brain;

brain  Brain;

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

pot ArmPot = pot(Brain.ThreeWirePort.A);
// A global instance of vex::competition
vex::competition Competition;


int auton = 0;
bool running = false;
int ticks = 0;
bool developer = false;
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

void Turn(int dir, int angle, int speed) {
  if(dir == 0) {
    while(RightBack.rotation(rotationUnits::deg) <= angle*2.49) {
      Drive(-1*speed, 0);
      Drive(speed, 1); 
    }
    Drive(0, 2);
  } else if(dir == 1) {
    while(LeftBack.rotation(rotationUnits::deg) <= angle*2.49) {
      Drive(speed, 0);
      Drive(-1*speed, 1);
    }
    Drive(0, 2);
  }
}

bool MoveEn(double distance, int speed, bool autocorrect) {
  LeftBack.resetRotation();
  RightBack.resetRotation();
  while(LeftBack.rotation(rotationUnits::deg) <= distance) {
    if (LeftBack.rotation(rotationUnits::deg) > RightBack.rotation(rotationUnits::deg) && autocorrect) {
      Drive(speed, 0);
      Drive(speed + (speed/3), 1);
    }
    else if (LeftBack.rotation(rotationUnits::deg) < RightBack.rotation(rotationUnits::deg) && autocorrect) {
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


void render() {
    if(developer) {
      Brain.Screen.newLine();
      Brain.Screen.print("Developer Mode is Enabled");
      Brain.Screen.newLine();
    }
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

void trackColor() {
  int posX = 0;
  int posY = 0;
  int visionSpeedLeft = 0;
  int visionSpeedRight = 0;
  //while(Controller1.ButtonA.pressing()) { //Custom Charge with color sensing
    visionSpeedLeft = Controller1.Axis3.value();
    visionSpeedRight = Controller1.Axis3.value();
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
      Drive(-7+Controller1.Axis3.value(), 0);
      Drive(7+Controller1.Axis3.value(), 1);
      Vision.setLedColor(255, 255, 0);
    }
    else if (posX > 160) {
      Drive(7+Controller1.Axis3.value(), 0);
      Drive(-7+Controller1.Axis3.value(), 1);
      Vision.setLedColor(0, 255, 255);
    }
    else if ((posX  > 140) && (posX < 160)) {
      Drive(Controller1.Axis3.value(), 2);
      Vision.setLedColor(0, 255, 0);
    }
  //}
}


void pre_auton( void ) {
  while(!competition().isEnabled() || true) {
    if(developer) {
      Brain.Screen.clearScreen();
      Brain.Screen.print("Autonomous selection is disabled in dev mode");
      Brain.Screen.newLine();
      auton = 1;
    } else {
      swap();
      render();
    }  
  }
}

void autonomous( void ) {
  running = true;
  task::sleep(500);     
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  switch (auton) {
    case 0:
      Brain.Screen.print("No Auton");
      break;
    case 1:
      Brain.Screen.print("Testing Autonomous");
      IntakeMotor.stop(brakeType::hold);
      MoveEn(.4* 360, 20, true);
      task::sleep(100);
      Turn(1, 91, 20);
      task::sleep(100);
      Drive(-20, 2);
      task::sleep(900);
      Drive(0, 2);
      task::sleep(100);
      MoveEn(2.3 * 360, 30, true);
      task::sleep(100);
      Turn(1, 97, 20);
      task::sleep(100);
      MoveEn(.4 * 360, 10, true);
      task::sleep(100);
      IntakeMotor.spin(directionType::fwd, -75, velocityUnits::pct);
      task::sleep(500);
      IntakeMotor.stop(brakeType::hold);
      task::sleep(100);
      Turn(1, 150, 12);
      IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
      task::sleep(100);
      IntakeMotor.stop(brakeType::hold);
      MoveEn(2.7 * 360, 25, true);
      task::sleep(100);
      IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
      Drive(-50, 2);
      task::sleep(1500);
      Drive(0, 2);
      IntakeMotor.stop();
      break;
    case 2:
      Brain.Screen.print("Near Blue");

      IntakeMotor.stop(brakeType::hold);
      MoveEn(.4* 360, 20, true);
      task::sleep(100);
      Turn(0, 91, 20);
      task::sleep(100);
      Drive(-20, 2);
      task::sleep(900);
      Drive(0, 2);
      task::sleep(100);
      MoveEn(2.3 * 360, 30, true);
      task::sleep(100);
      Turn(0, 97, 20);
      task::sleep(100);
      MoveEn(.4 * 360, 10, true);
      task::sleep(100);
      IntakeMotor.spin(directionType::fwd, -75, velocityUnits::pct);
      task::sleep(500);
      IntakeMotor.stop(brakeType::hold);
      task::sleep(100);
      Turn(0, 150, 12);
      IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
      task::sleep(100);
      IntakeMotor.stop(brakeType::hold);
      MoveEn(2.7 * 360, 25, true);
      task::sleep(100);
      IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
      Drive(-50, 2);
      task::sleep(1500);
      Drive(0, 2);
      IntakeMotor.stop();

      break;
    case 3:
      Brain.Screen.print("Near Red");
      IntakeMotor.stop(brakeType::hold);
      MoveEn(.4* 360, 20, true);
      task::sleep(100);
      Turn(1, 91, 20);
      task::sleep(100);
      Drive(-20, 2);
      task::sleep(900);
      Drive(0, 2);
      task::sleep(100);
      MoveEn(2.3 * 360, 30, true);
      task::sleep(100);
      Turn(1, 97, 20);
      task::sleep(100);
      MoveEn(.4 * 360, 10, true);
      task::sleep(100);
      IntakeMotor.spin(directionType::fwd, -50, velocityUnits::pct);
      task::sleep(500);
      IntakeMotor.stop(brakeType::hold);
      task::sleep(100);
      Turn(1, 150, 12);
      IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
      task::sleep(100);
      IntakeMotor.stop(brakeType::hold);
      MoveEn(2.7 * 360, 25, true);
      task::sleep(100);
      IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
      Drive(-50, 2);
      task::sleep(1500);
      Drive(0, 2);
      IntakeMotor.stop();

      break;
    case 4:
      Brain.Screen.print("Far Blue");

      Drive(-20, 2);
      LiftMotor.spin(directionType::fwd, -100, velocityUnits::pct);
      task::sleep(1000);
      LiftMotor.stop();
      Drive(0, 2);

      break;
    case 5:
      Brain.Screen.print("Far Red");

      Drive(-20, 2);
      LiftMotor.spin(directionType::fwd, -100, velocityUnits::pct);
      task::sleep(1000);
      LiftMotor.stop();
      Drive(0, 2);

      break;
  }
}


void usercontrol( void ) {

  //User control code here, inside the loop
  while (1) {
    Vision.setLedColor(0, 0, 255);

    Drive(Controller1.Axis3.value()*.65, 0);
    Drive(Controller1.Axis2.value()*.65, 1);

    if(Controller1.ButtonR1.pressing()) {
      LiftMotor.spin(directionType::fwd, -100, velocityUnits::pct);
    } else if(Controller1.ButtonR2.pressing()) {
      LiftMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    } else {
      LiftMotor.stop(brakeType::brake);
    }
    if(Controller1.ButtonL1.pressing()) {
      IntakeMotor.spin(directionType::fwd, -50, velocityUnits::pct);
    } else if(Controller1.ButtonL2.pressing()) {
      IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
    } else {
      IntakeMotor.stop();//brakeType::hold);
    }

    if (Controller1.ButtonRight.pressing() && developer) {
      autonomous();
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}


int main() {
  //Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  ticks++;
    //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );
  //render();
  pre_auton();
  //Prevent main from exiting with an infinite loop.                        

  vex::task::sleep(10);//Sleep the task for a short amount of time to prevent wasted resources.
  
}