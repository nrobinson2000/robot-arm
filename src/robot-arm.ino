/*
 * Project: robot-arm
 * Description: Our project for the Rocket.Build Community Hackathon
 * Authors: Nathan Robinson, J Tarness
 * Date: 2019-04-13
 */

// Project Settings
#define USE_WIFI 1 // Comment out to disable WIFI

// Library Includes
#include "Adafruit-MotorShield-V2.h"

// Particle System Configuration
SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

// Library Instances
Adafruit_MotorShield motors;

// Startup Processes
void startupTasks()
{
  Serial.begin(115200);
}
STARTUP(startupTasks());

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.

  motors.begin();

#ifdef USE_WIFI
  Particle.connect();
#endif
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // The core of your code will likely live here.
}