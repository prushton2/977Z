#include "vex.h"
#include "Drivetrain.h"
#include "Mech.h"

Auton::Auton() {
  Drivetrain driver;
  Mech mech(75, 33);
};

void Auton::AutonStart() {
  //Raise lift to full height
  //Outtake
};

void Auton::BluePrep() {
  Init();
};
void Auton::BlueSmall() {}; //No
void Auton::BlueLarge() {
  Init();
};

void Auton::RedPrep() {
  Init();
};
void Auton::RedSmall() {}; //No
void Auton::RedLarge() {
  Init();
};


void Auton::Init() {

};