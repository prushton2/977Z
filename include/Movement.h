#ifndef MOVEMENT_H
#define MOVEMENT_H

void Drive(int speed, int side);
void driveBot();
bool MoveEn(double distance, int speed, bool autocorrect);
void Turn(int dir, int angle, int speed);
#endif