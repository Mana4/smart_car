#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#define uint8 unsigned char
//channel one
#define motor_left_pin1    	0
#define motor_left_pin2    	1
//channel two
#define motor_right_pin1    2
#define motor_right_pin2    3
//pwm
#define pwm_motor_left 4
#define pwm_motor_right 5

uint8 motorInit(void);

void motorForward(uint8 speed);
void motorBackward(uint8 speed);

void motorTurnLeft(void);
void motorTurnRight(void);

void motorStop(void);

#endif

