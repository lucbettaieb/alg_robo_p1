/*
* sense_model
* A ROS node that will take in noisey sensor data, fit some lines to
* different sets of data, and try to extrapolate a probability distrubution
* of where the robot may be.
*
* Luc A. Bettaieb
* bettaieb@case.edu
*
* 11.6.14 (Began work)
*/

#include <ros/ros.h>
#include <Eigen/Eigen>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

ros::Publisher pub_;	//To publish the odom with variance derived from vel
ros::Subscriber sub_;	//To subscribe to cmd_vel

void updateOdom(const sensor_msgs::LaserScan &laser){
	ROS_INFO("Got new scan data, updating sense_model.");

	nav_msgs::Odometry sensor_model;
	//Do dat stuff and update the sense_model


	return sensor_model;
}

int main(int argc, char** argv){
	ros::init(argc, argv, "sense_model");
	ros::NodeHandle nh;

	pub_ = nh.advertise<nav_msgs::Odometry>("sense_model", 1);
	sub_ = nh.subscribe("/noiseyScan", 10, updateOdom);

	ros::spin();
	return 0;
}