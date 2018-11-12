#ifndef MOTORS_H
#define MOTORS_H

///A0 and A7 Are SHORTED (BAD SOLDERING JOB)
#define PHOTO_1 PC5
#define PHOTO_2 PC4
#define PHOTO_3 PC3
#define PHOTO_4 PC2
#define PHOTO_5 PC1
#define PHOTO_6 PC0
#define BUTTON  PD1
#define MOTOR_1 PD7
#define MOTOR_2 8 //for some reason PB0 PB1 and PB2 didnt work
#define MOTOR_3 9
#define MOTOR_4 10
#define ENABLE_A  PD6
#define ENABLE_B  PD5
#define LED_LIGHT PD0

#include <L298N.h>

const int motorInput[]  = {0, 10, 20, 30, 40, 50, 60, 70};
const int motorOutput[] = {0, 20, 27, 35, 46, 61, 123, 255};

class Motors
{
  private:
    int leftSpeed = 0;
    int rightSpeed = 0;
    bool isStopped = 0;
    
    L298N rightMotor;
    L298N leftMotor;
    int multiMap(int val, int* _in, int* _out, uint8_t size);
    void move(int left, int right);   //-70 +70
    
  public:
    Motors();
    void drive(int _speed, int _wheel);///0-255, 0-50
    void brake();
};

#endif  //MOTORS_H
