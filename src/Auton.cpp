#include "vex.h"
#include "Drivetrain.h"
#include "Mech.h"

Drivetrain drivers;
Mech mechs(60, 20);

Auton::Auton() {};

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
  mechs.dLift(100);
  mechs.dIntake(60);
  task::sleep(1300);
  mechs.dLift(-60);
  mechs.dIntake(0);
  task::sleep(400);
  LiftMotor.resetRotation();
  mechs.dTilter(-60);
  drivers.Drive(5, 2);
  while(-Tilter.rotation(degrees) < 400) {
    task::sleep(10);
  }
  Brain.Screen.print("Done");
  mechs.dTilter(0);
  drivers.Drive(0, 2);
};