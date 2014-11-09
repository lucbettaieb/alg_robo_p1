/*
* simple_movement_with_error
* A ROS node to command simple movements to a /robot0/ 
* in STDR simulator.  Adds error to simulate reality.
*
* Luc A. Bettaieb
* bettaieb@case.edu
* 
* 11.8.14 (Began work)
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <stdio.h>

ros::Publisher pub_vel_;
ros::Subscriber sub_realOdom_;

nav_msgs::Odometry realOdom_;

const float moveTime = 1;  //NOTE!!!  If this is changed, please change in vel_model, too!

geometry_msgs::Twist stuffTwistWithVel(int select, float vel){
	geometry_msgs::Twist cmd;
	
	cmd.linear.x = 0;
	cmd.linear.y = 0;
	cmd.linear.z = 0;
	
	cmd.angular.x = 0;
	cmd.angular.y = 0;
	cmd.angular.z = 0;
	if(select == 0){ 		//Translational
		cmd.linear.x = vel;

	} else if(select == 1){	//Rotational
		cmd.angular.z = vel;

	} else{					//Zero
		return cmd;

	}

}

float addGaussianNoise(const float &variance){
	static bool haveSpare = false;
	static float rand1, rand2;

	if(haveSpare){
		haveSpare = false;
		return sqrt(variance * rand1) * sin(rand2);
	}

	haveSpare = true;

	rand1 = std::rand() / ((float) RAND_MAX);
	if(rand1 < 1e-100) rand1 = 1e-100;
	rand1 = -2*log(rand1);
	rand2 = ((rand() / ((float) RAND_MAX)) * TWO_PI);

	return sqrt(variance * rand1) * cos(rand2);
}

geometry_msgs::Twist addTwistError(geometry_msgs::Twist cmd){

}

int main(int argc, char** argv){
	ros::init(argc, argv, "simple_movement");
	ros::NodeHandle nh;


	int tranRotSel = -1;
	float velocity = 0.0;

	pub_vel_ = nh.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1);  //Set up the publisher to publish to the robots cmd_vel

	std::cout << "(!!!) Be aware!  All commands excecute for "<< moveTime << " seconds!" << std::endl;
	ROS_INFO("Starting interactive loop...");

	while(ros::ok()){
		
		std::cout << "Please enter 0 for a translational or 1 for a rotational command: ";
		std::cin >> tranRotSel;

		if(tranRotSel == 0){ 		//Translational Command
			std::cout << "Enter the value in meters/second for your translational command: ";
			std::cin >> velocity;


			ROS_INFO("Sending translational velocity command..");
			pub_vel_.publish(stuffTwistWithVel(0,velocity));
			ros::Duration(moveTime).sleep();
			pub_vel_.publish(stuffTwistWithVel(2,velocity));

		} else if (tranRotSel == 1){	//Rotational Command
			std::cout << "Enter the value in rads/second for your rotational command: ";
			std::cin >> velocity;


			ROS_INFO("Sending rotational velocity command..");
			pub_vel_.publish(stuffTwistWithVel(1,velocity));
			ros::Duration(moveTime).sleep();
			pub_vel_.publish(stuffTwistWithVel(2,velocity));

		} else{
			ros::shutdown();
		}

		ros::spinOnce();
	}

}