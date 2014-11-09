/*
* vel_model
* A ROS node to simulate the kinematics of a robot being simulated in
* STDR simulator and return a probability distribution of where the robot
* probably is.
*
* Luc A. Bettaieb
* bettaieb@case.edu
*
* 11.6.14 (Began work)
*/

#include <ros/ros.h>
//#include <Eigen/Eigen>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <math.h>

ros::Publisher pub_;	//To publish the odom with variance derived from vel
ros::Subscriber sub_cmd_vel_;	//To subscribe to cmd_vel
ros::Subscriber sub_realOdom_;

nav_msgs::Odometry realOdom_;

void updateVel_model(const geometry_msgs::Twist &cmdvel){
	ROS_INFO("Got new cmd_vel, updating vel_model.");

	nav_msgs::Odometry velocity_model;
	//Do dat state space stuff and update the vel_model
	velocity_model.pose.pose.position.x = realOdom_.pose.pose.position.x + 

	pub_.publish(velocity_model);
}

void updateRealOdom(const nav_msgs::Odometry &odom){
	realOdom_ = odom;
}

int main(int argc, char** argv){
	ros::init(argc, argv, "vel_model");
	ros::NodeHandle nh;

	pub_ = nh.advertise<nav_msgs::Odometry>("vel_model", 1);

	sub_cmd_vel_ = nh.subscribe("/robot0/cmd_vel", 10, updateVel_model);
	sub_realOdom_ = nh.subscribe("/robot0/odom", 10, updateRealOdom);

	ros::spin();
	return 0;
}