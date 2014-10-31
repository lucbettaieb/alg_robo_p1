/*
* Noisey
* A ROS Node to subscribe to a stream of simulated sensor data, add Gaussian noise to it,
* and republish it for probabilisitc-based filtering.
*
* Luc A. Bettaieb
* bettaieb@case.edu
*
* 22.10.14
*/

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/LaserScan.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TWO_PI 6.2831853071795864769252866
ros::Publisher pub_;
ros::Subscriber sub_;
 
//Box Muller transform for adding normally distributed noise to the signal (thanks wikipedia)
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

//Callback function for when node recieves a signal value (should be forever)
void addNoiseLaser(const sensor_msgs::LaserScan &scan){ //need to get sensor_msgs/LaserScan, iterate through ranges[] and add noise then publish new laserscan
	ROS_INFO("Adding noise...");

	sensor_msgs::LaserScan noiseyScan;

	std::srand(time(0));
	int randomNumber = std::rand() % 1;

	noiseyScan.ranges.resize(scan.ranges.size());
	for(int i = 0; i < 667; i++){ 
		noiseyScan.ranges[i] = scan.ranges[i] + addGaussianNoise(.03);
	}

	pub_.publish(noiseyScan);
}

int main(int argc, char** argv){

	//Standard ROS Initialization Stuff
	
	ros::init(argc, argv, "noisey");
	ros::NodeHandle nh;
	//Init random number generator with time seed

	pub_ = nh.advertise<sensor_msgs::LaserScan>("noiseyScan", 1);
	sub_ = nh.subscribe("/robot0/laser_0", 10, addNoiseLaser); //make sure its robot0...  This may need to be fixed
	ros::spinOnce();
	
 	ros::spin();
 	return 0;
}
