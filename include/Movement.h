#ifndef MOVEMENT_H
#define MOVEMENT_H

void Drive(int speed, int side);
void driveBot();
void driveClaw();
void driveArm();
bool MoveEn(double distance, int speed, bool autocorrect);
void Turn(int dir, int angle, int speed);
void GyroTurn(int angle, int speed);
bool isBetween(int val, int lim1, int lim2);
void liftArmTo(int height, int speed, bool CanDrive);
void setClaw(bool openClaw);

#endif