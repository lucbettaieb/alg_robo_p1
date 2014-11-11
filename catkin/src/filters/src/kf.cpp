/*
* kf
* A ROS node to implement a kalman filter using a probabalistic velocity model
* and a probabalistic sensor model.  Will return a gaussian to tell you what's good.
*
* Luc A. Bettaieb
* bettaieb@case.edu
* 
* 11.8.14 (Began work)
*/

#include <ros/ros.h>
#include <stdio.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

ros::Publisher pub_state_;
ros::Subscriber sub_sense_model_;
ros::Subscriber sub_vel_model_;

int main(int argc, char** argv){
	ros::init(argc, argv, "kf");
	ros::NodeHandle nh;

	//needs to accept a P(x| sensor) and a P(x| velocity)
	sub_vel_model_ = nh.subscribe("/vel_model",10,updateVelocityModel);
	sub_sense_model_ = nh.subscribe("/sense_model",10,updateSensorModel);

	//then publish a P(x| the fusion of the two n stuff)
	pub_state_ - nh.advertise<

	ros::spin();
	return 0;
}