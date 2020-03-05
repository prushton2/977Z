#include "vex.h"
using namespace vex;
  vex::controller Controller1 = vex::controller();

  vex::motor LeftFront         = vex::motor(  PORT9,  true  );
  vex::motor LeftBack          = vex::motor(  PORT8,  true  );

  vex::motor RightFront        = vex::motor(  PORT1,  false );
  vex::motor RightBack         = vex::motor(  PORT2,  false );

  vex::motor LiftMotor         = vex::motor(  PORT10,  true  );
  vex::motor Tilter            = vex::motor(  PORT7,   false );

  vex::motor LeftIntakeMotor   = vex::motor(  PORT20,   false );
  vex::motor RightIntakeMotor  = vex::motor(  PORT11,   true  );

  vex::competition Competition;

//DEAD PORTS: 1, 2, 4, 5, 7, 8, 9, 10 [Irrelevant]
//            

//Limits : 81% down, 33% up
//         510       -2 (degrees)

/* 
lift is in port 10, 
front left drive is in port 9, 
back left is in port 8. 
Right front drive is in port 1, 
back right drive is in port 2. 
Tilter is in port 7, and 
left intake will be in port 20 and 
right intake will be in port 11
*/
