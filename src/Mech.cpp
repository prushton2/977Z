#include "vex.h"

Mech::Mech() {}

void Mech::dLift(int speed) {
  if(speed == 0) {
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