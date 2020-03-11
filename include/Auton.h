#ifndef AUTON_H
#define AUTON_H

class Auton {
  public:
    std::string autonId;
    
    Auton();

    void Init();

    void AutonStart();

    void BluePrep();
    void BlueSmall();
    void BlueLarge();
    void RedPrep();
    void RedSmall();
    void RedLarge();
};

#endif