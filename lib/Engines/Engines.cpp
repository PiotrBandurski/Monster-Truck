#include <Motor.h>


//Motor shiled I2C Address: 0x30
//PWM frequency: 1000Hz(1kHz)
Motor M1(0x30,_MOTOR_A, 1000);//Motor A kiera
Motor M2(0x30,_MOTOR_B, 1000);//Motor B motur


void setSpeed(int speed){
  M2.setmotor(_CW, speed);
}

void setWheelRotation(int rotation){
  M1.setmotor( _CW, rotation);
}