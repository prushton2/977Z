#include "vex.h"
using namespace vex;
  vex::controller Controller1 = vex::controller();
  vex::vision Vision       = vex::vision( PORT8   );

  vex::motor LeftFront     = vex::motor(  PORT11,  true  );
  vex::motor LeftMiddle    = vex::motor(  PORT12,  false );
  vex::motor LeftBack      = vex::motor(  PORT13,  true  );

  vex::motor RightFront    = vex::motor(  PORT18,  false );
  vex::motor RightMiddle   = vex::motor(  PORT19,  true  );
  vex::motor RightBack     = vex::motor(  PORT20,  false );

  vex::motor LiftMotor     = vex::motor(  PORT3,   true  );
  vex::motor IntakeMotor   = vex::motor(  PORT4,   false );
  vex::competition Competition;
