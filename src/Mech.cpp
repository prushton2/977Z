#include "vex.h"

Mech::Mech() {}

void Mech::dLift(int speed) {
  LiftMotor.spin(directionType::fwd, speed, velocityUnits::pct);
}

void Mech::dIntake(int speed) {
  LeftIntakeMotor.spin(directionType::fwd, speed, velocityUnits::pct);
  RightIntakeMotor.spin(directionType::fwd, -1*speed, velocityUnits::pct);

}