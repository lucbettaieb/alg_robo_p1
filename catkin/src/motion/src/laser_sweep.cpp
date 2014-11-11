/*
* laser_sweep
* A ROS utility to send a command to a robot in STDR sim to perform a full rotation
* so that laser data can be gathered to generate a sensor model
*
* Luc A. Bettaieb
* bettaieb@gmail.command
*
* 11.11.14 (Began work)
*/

#include <ros/ros.h>
#include <math.h>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

#include <stdio.h>
#include <iostream>
#include <fstream> //Write the data to a file

ros::Publisher pub_rot_;
ros::Subscriber sub_laser_;
ros::Subscriber sub_odom_;

sensor_msgs::LaserScan scan_;
bool gotInitialLaser = true;

void updateLaser(const sensor_msgs::LaserScan &laser){
	// if(gotInitialLaser){
	// ROS_INFO("Got initial sensor data, updating global variable.");
	// 	gotInitialLaser = false;
	// }
	scan_ = laser;
}

void performSweep(){
	//might want to wait for initial data to appear for odom and laser TODO
	geometry_msgs::Twist sweep;
	
	sweep.linear.x = 0;
	sweep.linear.y = 0;
	sweep.linear.z = 0;

	sweep.angular.x = 0;
	sweep.angular.y = 0;
	sweep.angular.z = 0;

	geometry_msgs::Twist stop;

	stop.linear.x = 0;
	stop.linear.y = 0;
	stop.linear.z = 0;

	stop.angular.x = 0;
	stop.angular.y = 0;
	stop.angular.z = 0;

	int intCont = 0;

	std::ofstream file;
	file.open ("rangemap.txt");

	for(int i = 0; i < 15; i++){ 		//For all of the grid ROWS
		for(int j = 0; j < 15; j++){	//For all of the column CELLS in the ROW
			std::cout << "Please move robot to: " << i << ", " << j << "." << std::endl;
			std::cout << "Enter an int once robot is in position: ";
			std::cin >> intCont;

			//WRITE which cell this is going to be for in the file.

			file << "[" << i << "," << j << "] \n";
			std::cout << "[" << i << "," << j << "] \n";
			for(int a = 0; a < 8; a++){
				sweep.angular.z = M_PI/4;	//Set an omega of pi/4 rads/s
				pub_rot_.publish(sweep);	//Publish omega
				ros::Duration(1).sleep();	//For one second
				pub_rot_.publish(stop);		//Stop

				ros::spinOnce();

				//WRITE the angle at which the robot is at.
				file << "Angle: " << a+1 << "*pi/4" << "\n";
				
					for(int b = 0; b < scan_.ranges.size(); b++){
						//Acquire range array and write the values to the file.
						if(b == 0){ //first range
							file << "Ranges: {" << scan_.ranges[b] <<",";
						}
						else if(b == scan_.ranges.size()-1) { //last range
							file << scan_.ranges[b] << "}";
						}
						else {//in-betweeners
							file << scan_.ranges[b] << ",";
						}
					}
				file << "\n \n";
				file.flush();
		
			}

		}
	}
	
	file.close();
	ros::shutdown();
}

int main(int argc, char** argv){
	ros::init(argc, argv, "laser_sweep");
	ros::NodeHandle nh;

	pub_rot_ = nh.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1);
	sub_laser_ = nh.subscribe("/noiseyScan", 10, updateLaser);
	//sub_odom_ = nh.subscribe("/robot0/odom", 10, updateOdom);


	performSweep();
	ros::spin();
	return 0;
}