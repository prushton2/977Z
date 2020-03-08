#include "vex.h"

UI::UI() {}

void UI::renderDisplay() {
  // if(developer) {}
  Brain.Screen.setPenColor(color::blue);
  Brain.Screen.drawLine(0, 73, 250, 73);
  Brain.Screen.drawLine(0, 146, 250, 146);

  Brain.Screen.setCursor(2, 5);//blue

  if (auton == "No") {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::white);}
  Brain.Screen.print("No Autonomous");

  Brain.Screen.setPenColor(color::blue);
  Brain.Screen.setCursor(6, 5);

  if (auton == "Blue Large") {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::blue);}
  Brain.Screen.print("Large Autonomous");

  Brain.Screen.setCursor(10, 5);

  if (auton == "Blue Small") {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::blue);}
  Brain.Screen.print("Small Autonomous");

  Brain.Screen.setPenColor(color::white);

  Brain.Screen.setPenColor(color::white);
  Brain.Screen.drawLine(250, 0, 250, 250);
  
  Brain.Screen.setPenColor(color::red);//red
  Brain.Screen.drawLine(250, 73, 500, 73);
  Brain.Screen.drawLine(250, 146, 500, 146);
  Brain.Screen.setCursor(2, 30);

  if (auton == "Skills") {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::white);}
  Brain.Screen.print("Skills Autonomous");

  Brain.Screen.setCursor(6, 30);

  if (auton == "Red Large") {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::red);}
  Brain.Screen.print("Large Autonomous");

  Brain.Screen.setCursor(10, 30);

  if (auton == "Red Small") {Brain.Screen.setPenColor(color::purple);}
  else {Brain.Screen.setPenColor(color::red);}
  Brain.Screen.print("Small Autonomous");

  Brain.Screen.setPenColor(color::white);
}

std::string UI::swap() {
  if((Brain.Screen.yPosition() < 73) && (Brain.Screen.xPosition() < 250)) {
    auton = "No";
  }
  else if ((Brain.Screen.yPosition() < 73) && (Brain.Screen.xPosition() > 250)) {
    auton = "Skills";
  }
  else if ((Brain.Screen.yPosition() > 73) && (Brain.Screen.yPosition() < 146) && (Brain.Screen.xPosition() < 250)) {
    auton = "Blue Large";
  }
  else if ((Brain.Screen.yPosition() > 73) && (Brain.Screen.yPosition() < 146) && (Brain.Screen.xPosition() > 250)) {
    auton = "Red Large";
  }
  else if ((Brain.Screen.yPosition() > 73) && (Brain.Screen.xPosition() < 250)) {
    auton = "Blue Small";
  }
  else if ((Brain.Screen.yPosition() > 73) && (Brain.Screen.xPosition() > 250)) {
    auton = "Red Small";
  }
  else {
    auton = "No";
  }
  return auton;
}