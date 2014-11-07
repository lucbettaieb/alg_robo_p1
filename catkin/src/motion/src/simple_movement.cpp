/*
* simple_movement
* A ROS node to command simple movements to a /robot0/ 
* in STDR simulator.
*
* Luc A. Bettaieb
* bettaieb@case.edu
* 
* 11.6.4 (Began work)
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <stdio.h>

ros::Publisher pub_vel_;
ros::Subscriber sub_realOdom_;

nav_msgs::Odometry realOdom_;

const float moveTime = 0.5;

geometry_msgs::Twist stuffTwistWithVel(int select, float vel){
	geometry_msgs::Twist cmd;
	//cmd.linear.x
	//cmd.angular.z

}

int main(int argc, char** argv){
	ros::init(argc, argv, "simple_movement");
	ros::NodeHandle nh;


	int tranRotSel = -1;
	float velocity = 0.0;

	pub_vel_ = nh.advertise<"/robot/cmd_vel", 1>;  //Set up the publisher to publish to the robots cmd_vel

	std::cout << "(!!!) Be aware!  All commands excecute for "<< moveTime << " seconds!" << std::endl;
	ROS_INFO("Starting interactive loop...");

	while(ros::ok()){
		
		std::cout << "Please enter 0 for a translational or 1 for a rotational command: ";
		std::cin >> tranRotSel;

		if(tranRotSel == 0){ 		//Translational Command
			std::cout << "Enter the value in meters/second for your translational command: ";
			std::cin >> velocity;

			ROS_INFO("Sending velocity command..")


		} else if (tranRotSel == 1){	//Rotational Command
			std::cout << "Enter the value in rads/second for your rotational command: ";
			std::cin >> velocity;
		}

		ros::spinOnce();
	}

}