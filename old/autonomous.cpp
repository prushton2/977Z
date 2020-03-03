#include "vex.h"
bool developer = false;
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
  MoveEn(.5 * 360, 10, true);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  task::sleep(1000);
  IntakeMotor.stop(brakeType::hold);
  GyroTurn(-120, 15);
  // IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(100);
  // IntakeMotor.stop(brakeType::hold);
  MoveEn(3 * 360, 25, true);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(500);
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
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  task::sleep(1000);
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
  MoveEn(2.6 * 360, 15, true);
  task::sleep(100);
  GyroTurn(89, 15);
  task::sleep(100);
  LiftMotor.spin(directionType::fwd, 15, velocityUnits::pct);
  MoveEn(.4 * 360, 5, true);
  LiftMotor.stop(brakeType::hold);
  task::sleep(100);

  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  task::sleep(600);
  IntakeMotor.stop(brakeType::hold);

  GyroTurn(120, 15);
  task::sleep(100);
  LiftMotor.stop();
  MoveEn(2.7 * 360, 25, true);
  
  Drive(20, 2);
  task::sleep(1000);
  Drive(0, 2);

  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(500);
  MoveEn(-.52 * 360, 20, true);

  Drive(-10, 0);
  Drive(10, 1);
  while(Gyro.heading(degrees) > 193) {}

  Drive(0, 2);
  MoveEn(1.0 * 360, 15, true);

  IntakeMotor.spin(directionType::fwd, -75, velocityUnits::pct);
  task::sleep(900);
  IntakeMotor.stop(brakeType::hold);
  
  MoveEn(.3 * 360, 15, true);
  liftArmTo(80, 20, false);
  // MoveEn(1*360, 15, true);
  Drive(15, 2);
  task::sleep(2000);
  Drive(0, 2);

  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(500);
  IntakeMotor.stop();
  MoveEn(-.5 * 360, 15, true);
  liftArmTo(60, 25, false);
  MoveEn(-0.25 * 360, 15, true);
  GyroTurn(-90, 20);
  Drive(-30, 2);
  
  LiftMotor.spin(directionType::fwd, 20, velocityUnits::pct);
  task::sleep(2000);
  LiftMotor.stop();
  MoveEn(2 * 360, 15, true);
  GyroTurn(3, 2);
  MoveEn(2 * 360, 15, true);

  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(750);
  IntakeMotor.stop(brakeType::hold);
  
  GyroTurn(-25, 15);
  MoveEn(5 * 360, 15, true);

}
