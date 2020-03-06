#ifndef AUTON_H
#define AUTON_H

class Auton {
    public:
        std::string autonSide;
        std::string autonType;
        Auton();
        void BluePrep();
        void BlueSmall();
        void BlueLarge();
        void RedPrep();
        void RedSmall();
        void RedLarge();
};

#endif