#include "application.h"
#include "Adafruit-MotorShield-V2/Adafruit-MotorShield-V2.h"
#include "Adafruit-MotorShield-V2/Adafruit_PWMServoDriver.h"

/*
 Visit the following url for help on connecting the motor shield
 to the spark core:
 https://community.spark.io/t/adafruit-motor-shield-v2-progress/5218
*/

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
// Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

// You can also make a stepper motor on M1/M2
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 1);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(10);
}

void loop() {
  myMotor->step(100, FORWARD, SINGLE);
  
  Serial.print("Spin");
  
  delay(1000);
}

