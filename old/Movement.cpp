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
  Drive(Controller1.Axis3.value()*.65, 0); 
  Drive(Controller1.Axis2.value()*.65, 1);
}
void driveClaw() {
  if(Controller1.ButtonL1.pressing()) {
    IntakeMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  } else if(Controller1.ButtonL2.pressing()) {
    IntakeMotor.spin(directionType::fwd, 100, velocityUnits::pct);
  } else {
    IntakeMotor.stop(brakeType::hold);
  }
}
void driveArm() {
  if(Controller1.ButtonR1.pressing()) {
    LiftMotor.spin(directionType::fwd, -100, velocityUnits::pct);
  } else if(Controller1.ButtonR2.pressing()) {
    LiftMotor.spin(directionType::fwd, 100, velocityUnits::pct);
  } else {
    LiftMotor.stop(brakeType::brake);
  }
}



bool MoveEn(double distance, int speed, bool autocorrect) {
  LeftBack.resetRotation();
  RightBack.resetRotation();
  if(distance > 0) {
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
  } else {
    while(LeftBack.rotation(rotationUnits::deg) >= distance) {
      if (LeftBack.rotation(rotationUnits::deg) < RightBack.rotation(rotationUnits::deg) && autocorrect) {
        Drive(-1*speed, 0);
        Drive(-1*(speed + (speed/3)), 1);
      }
      else if (LeftBack.rotation(rotationUnits::deg) > RightBack.rotation(rotationUnits::deg) && autocorrect) {
        Drive(-1*(speed + (speed/3)), 0);
        Drive(-1*speed, 1);
      }
      else {
        Drive(-1*speed, 0);
        Drive(-1*speed, 1);
      }
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

bool isBetween(int val, int lim1, int lim2) {
  if((val >= lim1 && val <= lim2) || (val <= lim1 && val >= lim2)) {
    return true;
  } else {
    return false;
  }
}

void GyroTurn(int angle, int speed) {
  inertial::quaternion  Inertial_quaternion;
  Gyro.setRotation(0, degrees);
  // bool hasrun = false;
  if(angle > 0) {
    while(Gyro.rotation(degrees) < angle) {
      Drive(speed, 0);
      Drive(-1*speed, 1);
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(Gyro.heading(degrees));
      Brain.Screen.print(", ");
      Brain.Screen.print(angle);
      // hasrun = true;
    }
    Drive(0, 2);
  } else {
    while(Gyro.rotation(degrees) > angle) {
      Drive(-1*speed, 0);
      Drive(speed, 1);
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(Gyro.heading(degrees));
      Brain.Screen.print(", ");
      Brain.Screen.print(angle);
    }
  }
  Drive(0, 2);

  // Gyro.setRotation(0, degrees);
  Brain.Screen.clearLine(1);
  Brain.Screen.print(Gyro.heading(degrees));

}

void liftArmTo(int height, int speed, bool CanDrive) {
  // if(CanDrive) {
    LiftMotor.stop();
  // }
  if(height > ArmPot.angle()) {
    while(height > ArmPot.angle()) {
      LiftMotor.spin(directionType::fwd, -1*speed, velocityUnits::pct);
      if(CanDrive) {
        driveBot();
        driveClaw();
      }
    }
    LiftMotor.stop(brakeType::hold);
    return;
  }
  if(height < ArmPot.angle()) {
    while(height < ArmPot.angle()) {
      LiftMotor.spin(directionType::fwd, 1*speed, velocityUnits::pct);
      if(CanDrive) {
        driveBot();
        driveClaw();
      }
    }
    LiftMotor.stop(brakeType::hold);
    return;
  }
  LiftMotor.stop(brakeType::hold);
}

void setClaw(bool openClaw) {
  if(openClaw) {
    IntakeMotor.spin(directionType::fwd, 50, velocityUnits::pct);
    task::sleep(1000);
    IntakeMotor.stop();
  }
  if(!openClaw) {
    IntakeMotor.spin(directionType::fwd, -50, velocityUnits::pct);
    task::sleep(1000);
    IntakeMotor.stop();
  }
}