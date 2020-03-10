#include "vex.h"

Mech::Mech(int upperLimitP, int lowerLimitP) {
  upperLimit = upperLimitP;
  lowerLimit = lowerLimitP;
}

void Mech::dLift(int speed) {
  if(speed < 0 && LiftPot.angle(percent) > lowerLimit) {
    LiftMotor.spin(directionType::fwd, speed, velocityUnits::pct);
  }
  else if(speed > 0 && LiftPot.angle(percent) < upperLimit) {
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
  while(Tilter.rotation(degrees) > -1400) {
        dTilter(-60);
      }
      dTilter(0);
      task::sleep(500);
      while(Tilter.rotation(degrees) < -10) {
        dTilter(60);
      }
      dTilter(0);
      task::sleep(800);
      dIntake(35);
      int speed = -15;
      LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
      LeftBack.spin(directionType::fwd, speed, velocityUnits::pct);

      RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
      RightBack.spin(directionType::fwd, speed, velocityUnits::pct); 

      task::sleep(750);

      dIntake(0);
      speed = 0;
      LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
      LeftBack.spin(directionType::fwd, speed, velocityUnits::pct);

      RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
      RightBack.spin(directionType::fwd, speed, velocityUnits::pct); 

      while(Controller1.ButtonY.pressing()) {} //Wait until button upressed
}