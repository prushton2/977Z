class Movement {
  public:

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
};