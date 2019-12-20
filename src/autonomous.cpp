#include "vex.h"

void runAutonomous(int autonID) {
  switch(autonID) {
    case 0:

    break;
    case 1:

    break;
    case 2:
      Blue1();
    break;
    case 3:
      Red1();
    break;
    case 4:

    break;
    case 5:

    break;
  }
}

void Blue1() {
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
  MoveEn(.6 * 360, 10, true);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  task::sleep(500);
  IntakeMotor.stop(brakeType::hold);
  task::sleep(100);
  Turn(0, 150, 12);
  // liftArmTo(4096, 10);
  IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
  task::sleep(100);
  IntakeMotor.stop(brakeType::hold);
  MoveEn(2.7 * 360, 25, true);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, 75, velocityUnits::pct);
  Drive(-50, 2);
  task::sleep(1500);
  Drive(0, 2);
  IntakeMotor.stop();
}

void Red1() {
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
  MoveEn(.6 * 360, 10, true);
  task::sleep(100);
  IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
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
}