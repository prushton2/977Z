#include "vex.h"
bool developer = true;
void runAutonomous(int autonID) {
  if(developer) {
    Blue1();
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
  task::sleep(500);
  Drive(0, 2);
  task::sleep(100);
  MoveEn(2.6 * 360, 30, true);
  task::sleep(100);
  GyroTurn(-90, 15);
  task::sleep(100);
  LiftMotor.spin(directionType::fwd, 10, velocityUnits::pct);
  MoveEn(.26 * 360, 10, true);
  LiftMotor.stop(brakeType::hold);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  // LiftMotor.stop();
  LiftMotor.spin(directionType::fwd, -20, velocityUnits::pct);
  task::sleep(600);
  LiftMotor.stop(brakeType::hold);
  IntakeMotor.stop(brakeType::hold);
  GyroTurn(-120, 15);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(100);
  IntakeMotor.stop(brakeType::hold);
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
  // MoveEn(-.3*360, 10, true);
  Turn(1, 91, 20);
  task::sleep(100);
  Drive(-30, 2);
  task::sleep(500);
  Drive(0, 2);
  task::sleep(100);
  MoveEn(2.7 * 360, 30, true);
  task::sleep(100);
  GyroTurn(90, 15);
  task::sleep(100);
  LiftMotor.spin(directionType::fwd, 10, velocityUnits::pct);
  MoveEn(.33 * 360, 10, true);
  LiftMotor.stop(brakeType::hold);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  // LiftMotor.stop();
  LiftMotor.spin(directionType::fwd, -20, velocityUnits::pct);
  task::sleep(600);
  LiftMotor.stop(brakeType::hold);
  IntakeMotor.stop(brakeType::hold);
  GyroTurn(120, 15);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(100);
  IntakeMotor.stop(brakeType::hold);
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
  // Depositing tower and large goal
  MoveEn(.5* 360, 20, true);
  task::sleep(100);
  Turn(1, 90, 30);
  Drive(-10, 0);
  Drive(-25, 1);
  task::sleep(1000);
  Drive(0, 2);
  MoveEn(2 * 360, 20, true);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  task::sleep(500);
  IntakeMotor.stop(brakeType::hold);
  Turn(1, 19, 20);
  MoveEn(.5 * 360, 20, true); 
  liftArmTo(72, 45, false);
  task::sleep(100);
  MoveEn(.7 * 360, 20, true);
  IntakeMotor.spin(directionType::fwd, 100, velocityUnits::pct);
  task::sleep(500);
  IntakeMotor.stop();
  //PHASE 2
  //Depositing Tower
  MoveEn(-.3 * 360, 20, true);
  setClaw(false);
  liftArmTo(50, 45, false);
  setClaw(true);
  Turn(1, 45, 20);
  MoveEn(.35*360, 20, true);
  setClaw(false);
  Turn(1, 155, 12);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(100);
  IntakeMotor.stop(brakeType::hold);
  MoveEn(2.7 * 360, 25, true);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  Drive(-50, 2);
  task::sleep(1000);
  Drive(0, 2);
  IntakeMotor.stop();
}
