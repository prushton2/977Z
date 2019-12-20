#include "vex.h"
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

void driveBot() {
  Drive(Controller1.Axis3.value()*.65, 0); Drive(Controller1.Axis2.value()*.65, 1);

  if(Controller1.ButtonR1.pressing()) {
    LiftMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  } else if(Controller1.ButtonR2.pressing()) {
    LiftMotor.spin(directionType::fwd, 100, velocityUnits::pct);
  } else {
    LiftMotor.stop(brakeType::brake);
  }
  if(Controller1.ButtonL1.pressing()) {
    IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  } else if(Controller1.ButtonL2.pressing()) {
    IntakeMotor.spin(directionType::fwd, 100, velocityUnits::pct);
  } else {
    IntakeMotor.stop(brakeType::hold);
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