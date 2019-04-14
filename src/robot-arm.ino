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
  WiFi.selectAntenna(ANT_AUTO);
  Serial.begin(115200);
}
STARTUP(startupTasks());

// Cloud Variables

char ssid[100];
int rssi;
int strength;
int quality;

void listAPs()
{
  WiFiAccessPoint aps[20];
  int found = WiFi.scan(aps, 20);
  for (int i = 0; i < found; i++)
  {
    WiFiAccessPoint &ap = aps[i];
    Serial.printlnf("SSID: %s, Security: %d, Channel: %d, RSSI: %d", ap.ssid, ap.security, ap.channel, ap.rssi);
  }

  Serial.println();
}

void updateConnectionStats()
{
  WiFiSignal sig = WiFi.RSSI();

  snprintf(ssid, sizeof(ssid), "%s", WiFi.SSID());
  rssi = sig.rssi;
  strength = sig.getStrength();
  quality = sig.getQuality();

  Serial.printlnf("[%s]: rssi: %d, strength: %d, quality: %d", ssid, rssi, strength, quality);
}

int toggleLed(const char *args)
{
  pinMode(D7, OUTPUT);
  int command = atoi(args);
  if (command == 1)
  {
    digitalWrite(D7, HIGH);
  }
  else
  {
    digitalWrite(D7, LOW);
  }
  return command;
}

bool hasIP = false;
char myIp[200];

void ipHandler(const char *topic, const char *data)
{
  Serial.println("received " + String(topic) + ": " + String(data));
  snprintf(myIp, sizeof(myIp), "%s", data);
  hasIP = true;
}

String serialInput;

void setup() // Put setup code here to run once
{
  // Cloud Variable Definitions
  Particle.variable("ssid", ssid);
  Particle.variable("rssi", rssi);
  Particle.variable("strength", strength);
  Particle.variable("quality", quality);

  Particle.variable("lastCommand", serialInput);

  // Cloud Function Definitions
  Particle.function("toggle", toggleLed);

  Particle.function("setMotors", setMotors);

  // Subscriptions
  Particle.subscribe("particle/device/ip", ipHandler, MY_DEVICES);

  // Put initialization like pinMode and begin functions here.

  motors.begin();

#ifdef USE_WIFI
  Particle.connect();
#endif
}

int setMotors(const char *message)
{

  // 4 motors each with direction and speed

  int numMotors = 4;
  int directions[numMotors];
  int speeds[numMotors];

  Adafruit_DCMotor *dcMotors[numMotors];

  int ret = sscanf(message, "%d,%d,%d,%d,%d,%d,%d,%d", &directions[0], &speeds[0], &directions[1], &speeds[1], &directions[2], &speeds[2], &directions[3], &speeds[3]);

  Serial.println();
  Serial.printlnf("Got %d arguments back.", ret);

  if (ret != 8)
  {
    Serial.println("Invalid arguments");
    return -1;
  }

  for (int i = 0; i < numMotors; i++)
  {
    dcMotors[i] = motors.getMotor(i + 1);
    Serial.printlnf("Motor %d:\nDirection %d:\nSpeed: %d", i + 1, directions[i], speeds[i]);
  }

  for (int i = 0; i < numMotors; i++)
  {
    dcMotors[i]->setSpeed(speeds[i]);
    dcMotors[i]->run(directions[i]);
  }

  return 0;
}

void loop() // Put code here to loop forever
{
  static char serialCommand[50];

  if (Serial.available())
  {
    serialInput = Serial.readStringUntil('\n');
    serialInput.toCharArray(serialCommand, sizeof(serialCommand));
    setMotors(serialCommand);
  }
}