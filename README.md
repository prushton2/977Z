# 977Z
Code for the 977Z robot


# File Structure

## Drivetrain
Controls wheels and gyro. Contains move and turn code.

## Mech
Drives the mechanisms. Contains code to automatically apply </br>a stop when the given power is 0 for any mechanisms

## UI
Contains a function to draw the display, and to detect screen presses. Stores the </br> pressed button in the auton attribute

## Auton
Contains a method for each auton, a method to deploy the tray, and a method to control the autons
