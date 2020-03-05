#include "vex.h"

Mech::Mech(int upperLimitP, int lowerLimitP) {
  upperLimit = upperLimitP;
  lowerLimit = lowerLimitP;
}

void Mech::dLift(int speed) {
  if(speed > 0 && LiftPot.angle(degrees) < upperLimit) {
    LiftMotor.spin(directionType::fwd, speed, velocityUnits::pct);
  }
  else if(speed < 0 && LiftPot.angle(degrees) > lowerLimit) {
    LiftMotor.spin(directionType::fwd, speed, velocityUnits::pct);
  } else {
    LiftMotor.stop(brakeType::hold);
  }
}

void Mech::dIntake(int speed) {
  if(speed == 0) {
    LeftIntakeMotor.spin(directionType::fwd, speed, velocityUnits::pct);
    RightIntakeMotor.spin(directionType::fwd, -1*speed, velocityUnits::pct);
  } else {
    LeftIntakeMotor.stop(brakeType::hold);
    RightIntakeMotor.stop(brakeType::hold);
  }
}