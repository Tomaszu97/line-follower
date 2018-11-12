/*
  //  LINE FOLLOWER ROBOT BY TOMASZ JAKUBOWSKI  [2017-2018]
  //  FUSEBIT SETTINGS FOR AVRDUDE (8MHZ INTERNAL CLOCK): -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m
  //  SET BOARD AS PURE AVR ATMEGA CHIP WITH 8MHZ CLOCK
  //  BE AWARE THAT SERIAL IS OCCUPIED BY BUTTON(TX) AND LED(RX)
  //  PROGRAMMING DONE BY USBASP THROUGH ISP INTERFACE
*/

#include <PID_v1.h>
#include "motors.h"

int lineSide = 0;
int lastCentroid = 25;

int getCentroid(int minimalMass, int criticalMass)   //calculate the line position using mass/torque relation analogy //returns values 0-50, and -1 if it sees only black
{
  int sensorReadings[6];
  int mass = 0;
  int torque = 0;

  sensorReadings[0] = analogRead(PHOTO_1);
  sensorReadings[1] = analogRead(PHOTO_2);
  sensorReadings[2] = analogRead(PHOTO_3);
  sensorReadings[3] = analogRead(PHOTO_4);
  sensorReadings[4] = analogRead(PHOTO_5);
  sensorReadings[5] = analogRead(PHOTO_6);

  for (int i = 0; i < 6; i++)
  {
    int reading = sensorReadings[i] / 32;
    mass += reading;
    torque += reading * (i + 1);
  }

  if (lastCentroid < 15)       lineSide = -1;
  else if (lastCentroid > 35) lineSide = 1;
  else lineSide = 0;

  if (mass < minimalMass)
  {
    if (lineSide == -1) return 0;
    else if(lineSide == 0) return 25;
    else return 50;
  }

  else if (mass > criticalMass)  return -1;

  else
  {
    lastCentroid = torque * 10 / mass - 10;
    return lastCentroid;
  }

}

double centroid = 25;
double setpoint = 25;
double wheel = 25;
Motors motors;
PID drivingPID(&centroid, &wheel, &setpoint, 3.0 , 0.0, 0.05 , REVERSE);

void setup()
{
  //UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0)); //DISABLE UART
  Serial.begin(38400);
  motors.drive(0, 25);

  drivingPID.SetSampleTime(1);
  drivingPID.SetMode(AUTOMATIC);

  delay(1000);
}

void loop()
{
  centroid = (double)getCentroid(10, 150);

  if (centroid != -1)
  {
    drivingPID.Compute();
    motors.drive(16, wheel);
  }
  else
  {
    motors.brake();
  }
}
