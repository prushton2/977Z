#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class Drivetrain {
  public:
    Drivetrain();
    void Drive(int speed, int side);
    void MoveEn(double distance, int speed, bool autocorrect);
};

#endif