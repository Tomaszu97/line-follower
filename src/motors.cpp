#include "motors.h"

Motors::Motors():
  rightMotor(ENABLE_A, MOTOR_1, MOTOR_2),
  leftMotor(ENABLE_B, MOTOR_3, MOTOR_4)
{
  pinMode(PHOTO_1, INPUT);
  pinMode(PHOTO_2, INPUT);
  pinMode(PHOTO_3, INPUT);
  pinMode(PHOTO_4, INPUT);
  pinMode(PHOTO_5, INPUT);
  pinMode(PHOTO_6, INPUT);
  pinMode(BUTTON, INPUT);

  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_3, OUTPUT);
  pinMode(MOTOR_4, OUTPUT);
  pinMode(ENABLE_A, OUTPUT);
  pinMode(ENABLE_B, OUTPUT);
  pinMode(LED_LIGHT, OUTPUT);
}

int Motors::multiMap(int val, int* _in, int* _out, uint8_t size)
{
  // note: the _in array should have increasing values

  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size - 1]) return _out[size - 1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while (val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos - 1]) * (_out[pos] - _out[pos - 1]) / (_in[pos] - _in[pos - 1]) + _out[pos - 1];
}

void Motors::move(int left, int right)  //-70 +70
{
  isStopped = 0;
  
  bool leftDir = 0;
  bool rightDir = 0;
  if (left >= 0) leftDir = 1;
  if (right >= 0) rightDir = 1;
  left = abs(left);
  right = abs(right);
  left = multiMap(left, motorInput, motorOutput, 8);
  right = multiMap(right, motorInput, motorOutput, 8);

  rightMotor.setSpeed(right);
  leftMotor.setSpeed(left);
  leftSpeed = left;
  rightSpeed = right;
  if (leftDir)  leftMotor.forward();
  if (!leftDir) leftMotor.backward();
  if (rightDir) rightMotor.backward();
  if (!rightDir)rightMotor.forward();
}

void Motors::drive(int _speed, int _wheel)
{
  _wheel = constrain(_wheel, 0, 50);
  _wheel -= 25;
  _speed = constrain(_speed, -70, 70);
  move(_speed + _wheel, _speed - _wheel);
}

void Motors::brake()
{
  if (isStopped == 0)
  {
    move(-leftSpeed*1.2, -rightSpeed*1.2);
    delay(50);
    move(0, 0);
    delay(600);
  }
  isStopped = 1;
}

