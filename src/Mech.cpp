#include "vex.h"

Mech::Mech(int upperLimitP, int lowerLimitP) {
  upperLimit = upperLimitP;
  lowerLimit = lowerLimitP;
}

void Mech::dLift(int speed) {
  if(speed < 0 && 100 - LiftPot.angle(percent) > lowerLimit) {
    LiftMotor.spin(directionType::fwd, speed, velocityUnits::pct);
  }
  else if(speed > 0 && 100 - LiftPot.angle(percent) < upperLimit) {
    LiftMotor.spin(directionType::fwd, speed, velocityUnits::pct);
  } else {
    LiftMotor.stop(brakeType::brake);
  }
}

void Mech::dIntake(int speed) {
  if(speed != 0) {
    LeftIntakeMotor.spin(directionType::fwd, speed, velocityUnits::pct);
    RightIntakeMotor.spin(directionType::fwd, -1*speed, velocityUnits::pct);
  } else {
    LeftIntakeMotor.stop(brakeType::hold);
    RightIntakeMotor.stop(brakeType::hold);
  }
}

void Mech::dTilter(int speed) {
  if(speed != 0) {
    Tilter.spin(directionType::fwd, speed, velocityUnits::pct);
  } else {
    Tilter.stop(brakeType::coast);
  }
}

void Mech::Deploy() {
  int iterations = 0;
  dTilter(-45);
  
  while(Tilter.rotation(degrees) > -1500 || iterations > 150) {
    if(!Controller1.ButtonY.pressing()) {
      return;
    }
  }
  task::sleep(300);
  dTilter(0);
  task::sleep(500);
  while(Tilter.rotation(degrees) < -10) {
    dTilter(50);
    if(!Controller1.ButtonY.pressing()) {
      return;
    }
  }
  dTilter(0);
  task::sleep(800);
  dIntake(15);
  task::sleep(300);
  int speed = -15;
  LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
  LeftBack.spin(directionType::fwd, speed, velocityUnits::pct);

  RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
  RightBack.spin(directionType::fwd, speed, velocityUnits::pct); 

  task::sleep(1000);

  dIntake(0);
  speed = 0;
  LeftFront.stop(brakeType::coast);
  LeftBack.stop(brakeType::coast);

  RightFront.stop(brakeType::coast);
  RightBack.stop(brakeType::coast); 

  while(Controller1.ButtonY.pressing()) {} //Wait until button upressed
}

void Mech::RaiseToHigh() {

  int ticks = 370;
  dLift(50);
  while(LiftMotor.rotation(degrees) < ticks) {
    task::sleep(20);
    Brain.Screen.clearScreen();
    Brain.Screen.newLine();
    Brain.Screen.print("Raising |", LiftMotor.rotation(degrees));
  }
  dLift(-20);
  while(LiftMotor.rotation(degrees) > ticks + 10) {
    task::sleep(20);
    Brain.Screen.clearScreen();
    Brain.Screen.newLine();
    Brain.Screen.print("Lowering |", LiftMotor.rotation(degrees));
  }
  dLift(0);
  return;
}

void Mech::RaiseToLow() {
  int ticks = 280;
  dLift(50);
  while(LiftMotor.rotation(degrees) < ticks) {
    task::sleep(20);
    Brain.Screen.clearScreen();
    Brain.Screen.newLine();
    Brain.Screen.print("Raising |", LiftMotor.rotation(degrees));
  }
  dLift(-20);
  while(LiftMotor.rotation(degrees) > ticks + 10) {
    task::sleep(20);
    Brain.Screen.clearScreen();
    Brain.Screen.newLine();
    Brain.Screen.print("Lowering |", LiftMotor.rotation(degrees));
  }
  dLift(0);
  return;
}
//-390 ticks hi
//-280 ticks lo