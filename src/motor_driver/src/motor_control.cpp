#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <iostream>

#include "motor_driver.h"
#include <wiringPi.h>
#include <softPwm.h>

#define vel2pwm_rate 1200


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
           

void callback(const geometry_msgs::Twist& cmd_vel)
{
	ROS_INFO("Received a /cmd_vel message!");
	
	ROS_INFO("Linear Components:[%f, %f, %f]", cmd_vel.linear.x, cmd_vel.linear.y, cmd_vel.linear.z);
	ROS_INFO("Angular Components:[%f, %f, %f]", cmd_vel.angular.x, cmd_vel.angular.y, cmd_vel.angular.z);
	// Do velocity processing here:  
    // Use the kinematics of your robot to map linear and angular velocities into motor commands  
//    v_l = ...  
//    v_r = ...  
  
    // Then set your wheel speeds (using wheel_left and wheel_right as examples)  
//    wheel_left.set_speed(v_l)  
//    wheel_right.set_speed(v_r) 
	if(cmd_vel.linear.x > 0){
		motorForward(cmd_vel.linear.x * vel2pwm_rate);
	}
	else if(cmd_vel.linear.x < 0){
		motorBackward(cmd_vel.linear.x * vel2pwm_rate);
	}
	else{
		motorStop();
	}
	
	if(cmd_vel.angular.z > 0){
		motorTurnLeft();
	}
	
	if(cmd_vel.angular.z < 0){
		motorTurnRight();
	}
}

int main(int argc, char** argv)
{
	if(motorInit() == -1){
		ROS_INFO("setup wiringPi failed !");
		return -1;
	}

	ros::init(argc, argv, "motor_controller");
	
	ros::NodeHandle n;
	
	ros::Subscriber sub = n.subscribe("cmd_vel", 1000, callback);
	
	ros::spin();

/*
//http://answers.ros.org/question/129506/subscriber-not-seeing-cmd_vel-messages/
	ros::Rate loop_rate(10);
	while( n.ok() ) 
	{
   		 ros::spin();
	}
*/
	return 1;
}
