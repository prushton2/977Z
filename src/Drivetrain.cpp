#include "vex.h"

Drivetrain::Drivetrain() {}

void Drivetrain::Drive(int speed, int side) {
  switch(side) {
    case 0:
      LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
      LeftBack.spin(directionType::fwd, speed, velocityUnits::pct);
    break;
    case 1:
      RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
      RightBack.spin(directionType::fwd, speed, velocityUnits::pct); 
    break;
    default:
      LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
      LeftBack.spin(directionType::fwd, speed, velocityUnits::pct);

      RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
      RightBack.spin(directionType::fwd, speed, velocityUnits::pct); 
  }
}


void Drivetrain::MoveEn(double distance, int speed, bool autocorrect) {
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
}

void Drivetrain::GyroTurn(int angle, int speed) {
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