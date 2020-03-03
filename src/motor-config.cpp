#include "vex.h"
using namespace vex;
  vex::controller Controller1 = vex::controller();

  vex::motor LeftFront         = vex::motor(  PORT11,  true  );
  vex::motor LeftBack          = vex::motor(  PORT12,  true  );

  vex::motor RightFront        = vex::motor(  PORT13,  false );
  vex::motor RightBack         = vex::motor(  PORT14,  false );

  vex::motor LiftMotor         = vex::motor(  PORT21,  true  );
  vex::motor Tilter            = vex::motor(  PORT5,   false );

  vex::motor LeftIntakeMotor   = vex::motor(  PORT6,   false );
  vex::motor RightIntakeMotor  = vex::motor(  PORT7,   true  );

  vex::competition Competition;

//DEAD PORTS: 1, 2, 4, 5, 7, 8, 9, 10
//            

//Limits : 81% down, 33% up
//         510       -2 (degrees)