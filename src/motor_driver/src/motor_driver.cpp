#include "motor_driver.h"
#include <wiringPi.h>
#include <softPwm.h>

uint8 motorInit(void){
  
 
  softPwmCreate(pwm_motor_left, 0, 255);
  softPwmCreate(pwm_motor_right, 0, 255);
  

  return 0;
}

void motorForward(uint8 speed){
	if(speed < 60)
		speed = 60;

        digitalWrite (motor_left_pin1, HIGH) ;
	digitalWrite (motor_left_pin2, LOW) ;

	digitalWrite (motor_right_pin1, HIGH) ;
	digitalWrite (motor_right_pin2, LOW) ;

	softPwmWrite(pwm_motor_right, speed);
	softPwmWrite(pwm_motor_left, speed);
}

void motorBackward(uint8 speed){
	if(speed < 60)
		speed = 60;
	
	digitalWrite (motor_left_pin1, LOW) ;
	digitalWrite (motor_left_pin2, HIGH) ;

	digitalWrite (motor_right_pin1, LOW) ;
	digitalWrite (motor_right_pin2, HIGH) ;

	softPwmWrite(pwm_motor_right, speed);
	softPwmWrite(pwm_motor_left, speed);
}

void motorStop(void){
	softPwmWrite(pwm_motor_right, 0);
	softPwmWrite(pwm_motor_left, 0);

	digitalWrite (motor_left_pin1, LOW) ;
	digitalWrite (motor_left_pin2, LOW) ;

	digitalWrite (motor_right_pin1, LOW) ;
	digitalWrite (motor_right_pin2, LOW) ;
}

void motorTurnLeft(void){
	uint8 speed = 225;

	digitalWrite (motor_left_pin1, LOW) ;
	digitalWrite (motor_left_pin2, HIGH) ;

	digitalWrite (motor_right_pin1, LOW) ;
	digitalWrite (motor_right_pin2, LOW) ;

	softPwmWrite(pwm_motor_right, 0);
	softPwmWrite(pwm_motor_left, speed);

	delay(100);
}

void motorTurnRight(void){
	uint8 speed = 225;

	digitalWrite (motor_left_pin1, LOW) ;
	digitalWrite (motor_left_pin2, LOW) ;

	digitalWrite (motor_right_pin1, LOW) ;
	digitalWrite (motor_right_pin2, HIGH) ;

	softPwmWrite(pwm_motor_right, speed);
	softPwmWrite(pwm_motor_left, 0);

	delay(100);
}
           
