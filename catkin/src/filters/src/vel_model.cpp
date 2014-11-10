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
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
#include <stdio.h>
#include <algp1_msgs/Pose2DWithCovariance.h>

ros::Publisher pub_vel_model_odom_;	//To publish the odom with variance derived from vel
ros::Publisher pub_vel_model_pose_; //To publish the pose of the robot x,y,theta and (co)variance

ros::Subscriber sub_cmd_vel_;	//To subscribe to cmd_vel
ros::Subscriber sub_realOdom_;

nav_msgs::Odometry realOdom_;
nav_msgs::Odometry velocity_model_;
algp1_msgs::Pose2DWithCovariance velocity_model_pose_;

const float moveTime = 1; //Derived from motion classes.  Needs to be changed if changed elsewhere.

bool timeToUpdateOdom = true;

void updateVel_model(const geometry_msgs::Twist &cmdvel){
	ROS_INFO("Got new cmd_vel, updating vel_model.");
	timeToUpdateOdom = true; //Allow for a new true odom measurement to be gathered

	//if(!(cmdvel.linear.x == 0 && cmdvel.angular.z == 0)){

		//This is a bit hacky considering the fact that realOdom shouldn't technically be real...  I guess it will just be perfect.

		//Updating model's X with previous
		velocity_model_.pose.pose.position.x = realOdom_.pose.pose.position.x + cos(cmdvel.angular.z) * moveTime * cmdvel.linear.x;
		velocity_model_.pose.pose.position.y = realOdom_.pose.pose.position.y + sin(cmdvel.angular.z) * moveTime * cmdvel.linear.y;

		//Something is wrong with this line of code.
		//I need to update the quaternion correctly and I have no idea.
		
		//velocity_model_.pose.pose.orientation.w = (1/3.14159)*atan(abs(realOdom_.pose.pose.orientation.z/realOdom_.pose.pose.orientation.w)) + (moveTime * cmdvel.angular.z)/3.14159;

		//std::cout << realOdom_.pose.pose.orientation.z << "prevZ" << std::endl;
		//std::cout << realOdom_.pose.pose.orientation.w << "prevW" << std::endl;
		//std::cout << cmdvel.angular.z << "cmdVel z" << std::endl;
		//velocity_model_.pose.pose.orientation.w = (1/3.14159)*atan2(realOdom_.pose.pose.orientation.z,realOdom_.pose.pose.orientation.w) + (moveTime * cmdvel.angular.z)/3.14159;
		
		velocity_model_.pose.pose.orientation.w = (1/M_PI)*(2*acos(realOdom_.pose.pose.orientation.w) + (moveTime * cmdvel.angular.z));
		
		//if(velocity_model_.pose.pose.orientation.)
		// if(velocity_model_.pose.pose.orientation.w > 1.99){ //If at 2pi, go back to 0 (full rotation)  (kind of hacky because of the 1.99)
		// 	velocity_model_.pose.pose.orientation.w = 0;
		// }

		velocity_model_pose_.pose2d.x = velocity_model_.pose.pose.position.x;
		velocity_model_pose_.pose2d.y = velocity_model_.pose.pose.position.y;
		velocity_model_pose_.pose2d.theta = velocity_model_.pose.pose.orientation.w;

		//(!!!) TODO: Add in the covariance matrix
		//(!!!) TODO: Add in Algorithmic_model_velocity
		pub_vel_model_odom_.publish(velocity_model_);
		pub_vel_model_pose_.publish(velocity_model_pose_);

	//}
}

void updateRealOdom(const nav_msgs::Odometry &odom){
	//if(timeToUpdateOdom){
		realOdom_ = odom;  //make this update only after the velocity_model_ has been updated so it can keep track of the odom before a perturbation has been applied
		timeToUpdateOdom = false;
	//}
}

int main(int argc, char** argv){
	ros::init(argc, argv, "vel_model");
	ros::NodeHandle nh;

	//These two publishers will publish to /robot0/vel_model/"___" If things mess up with /robot0/ being involved, check here.
	pub_vel_model_odom_ = nh.advertise<nav_msgs::Odometry>("robot0/vel_model/odom", 1);
	pub_vel_model_pose_ = nh.advertise<algp1_msgs::Pose2DWithCovariance>("robot0/vel_model/pose", 1);
	
	sub_realOdom_ = nh.subscribe("/robot0/odom", 10, updateRealOdom);
	sub_cmd_vel_ = nh.subscribe("/robot0/cmd_vel", 10, updateVel_model);

	ros::spin();
	return 0;
}