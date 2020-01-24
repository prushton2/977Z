#include "vex.h"
bool developer = true;
void runAutonomous(int autonID) {
  if(developer) {
    Skills1();
  } else {
    switch(autonID) {
    case 0:

    break;
    case 1:
      Skills1();
    break;
    case 2:
      Blue1();
    break;
    case 3:
      Red1();
    break;
    case 4:
      Blue2();
    break;
    case 5:
      Red2();
    break;
    }
  }
}

void Blue1() {
  IntakeMotor.stop(brakeType::hold);
  LiftMotor.stop(brakeType::hold);
  MoveEn(.48* 360, 20, true);
  task::sleep(100);
  // MoveEn(-.3*360, 10, true);
  Turn(0, 91, 20);
  task::sleep(100);
  Drive(-30, 2);
  task::sleep(700);
  Drive(0, 2);
  task::sleep(100);
  MoveEn(2.6 * 360, 30, true);
  task::sleep(100);
  GyroTurn(-90, 15);
  task::sleep(100);
  LiftMotor.spin(directionType::fwd, 15, velocityUnits::pct);
  MoveEn(.3 * 360, 10, true);
  LiftMotor.stop(brakeType::hold);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  LiftMotor.spin(directionType::fwd, -20, velocityUnits::pct);
  task::sleep(600);
  LiftMotor.stop(brakeType::hold);
  IntakeMotor.stop(brakeType::hold);
  GyroTurn(-120, 15);
  // IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(100);
  // IntakeMotor.stop(brakeType::hold);
  MoveEn(3 * 360, 25, true);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(300);
  Drive(-50, 2);
  task::sleep(1000);
  Drive(0, 2);
  IntakeMotor.stop();
}
void Blue2() {
  MoveEn(.4* 360, 20, true);
  task::sleep(100);
  Drive(-50, 2);
  task::sleep(300);
  Drive(0, 2);
}
void Red1() {
  IntakeMotor.stop(brakeType::hold);
  LiftMotor.stop(brakeType::hold);
  MoveEn(.48* 360, 20, true);
  task::sleep(100);
  Turn(1, 91, 20);
  task::sleep(100);
  Drive(-30, 2);
  task::sleep(700);
  Drive(0, 2);
  task::sleep(100);
  MoveEn(2.5 * 360, 30, true);
  task::sleep(100);
  GyroTurn(90, 15);
  task::sleep(100);
  LiftMotor.spin(directionType::fwd, 15, velocityUnits::pct);
  MoveEn(.35 * 360, 10, true);
  LiftMotor.stop(brakeType::hold);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  // LiftMotor.spin(directionType::fwd, -20, velocityUnits::pct);
  task::sleep(600);
  // LiftMotor.stop(brakeType::hold);
  IntakeMotor.stop(brakeType::hold);
  GyroTurn(120, 15);
  // IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(100);
  // IntakeMotor.stop(brakeType::hold);
  MoveEn(3 * 360, 25, true);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(200);
  Drive(-50, 2);
  task::sleep(1000);
  Drive(0, 2);
  IntakeMotor.stop();
}
void Red2() {
  MoveEn(.4* 360, 20, true);
  task::sleep(100);
  Drive(-50, 2);
  task::sleep(300);
  Drive(0, 2);
}

void Skills1() {
  // PHASE 1 
  // Running match auton
  IntakeMotor.stop(brakeType::hold);
  LiftMotor.stop(brakeType::hold);
  MoveEn(.48* 360, 20, true);
  task::sleep(100);
  Turn(1, 91, 20);
  task::sleep(100);
  Drive(-30, 2);
  task::sleep(700);
  Drive(0, 2);
  task::sleep(100);
  MoveEn(2.8 * 360, 15, true);
  task::sleep(100);
  GyroTurn(90, 15);
  task::sleep(100);
  LiftMotor.spin(directionType::fwd, 15, velocityUnits::pct);
  MoveEn(.35 * 360, 5, true);
  LiftMotor.stop(brakeType::hold);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  // LiftMotor.spin(directionType::fwd, -20, velocityUnits::pct);
  task::sleep(600);
  // LiftMotor.stop(brakeType::hold);
  IntakeMotor.stop(brakeType::hold);
  GyroTurn(125, 15);
  // IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(100);
  // IntakeMotor.stop(brakeType::hold);
  MoveEn(3.2 * 360, 25, true);
  task::sleep(200);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  MoveEn(-1.2 * 360, 20, true);
  while(Gyro.heading(degrees) < 180) {
    Drive(-15, 0);
    Drive(15, 1);
  }
  Drive(0, 2);
}
