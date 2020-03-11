#ifndef MECH_H
#define MECH_H

class Mech {
  public:
    int upperLimit;
    int lowerLimit;
    Mech(int upperLimitP, int lowerLimitP);
    void dLift(int speed);
    void dIntake(int speed);
    void dTilter(int speed);
    void Deploy();
    void RaiseToHigh();
    void RaiseToLow();
};

#endif