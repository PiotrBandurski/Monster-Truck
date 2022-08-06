#include <Motor.h>


//Motor shiled I2C Address: 0x30
//PWM frequency: 1000Hz(1kHz)
Motor M1(0x30,_MOTOR_A, 1000);//Motor A kiera
Motor M2(0x30,_MOTOR_B, 1000);//Motor B motur


void setSpeed(int speed){
  if(speed > 0){
        M2.setmotor( _CW, speed);
    } else{
        M2.setmotor( _CCW, -speed);
    }
}

void setWheelRotation(int rotation){
    if(rotation > 0){
        M1.setmotor( _CW, rotation);
    } else{
        M1.setmotor( _CCW, -rotation);
    }
}