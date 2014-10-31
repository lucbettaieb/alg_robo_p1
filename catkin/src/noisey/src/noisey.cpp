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
#define countof( array ) ( sizeof( array )/sizeof( array[0] ) )
#define TWO_PI 6.2831853071795864769252866
ros::Publisher pub_;
ros::Subscriber sub_;
 
//Box Nuller transform for adding normally distributed noise to the signal (thanks wikipedia)
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
	//std_msgs::Float32 ranges [countof(scan.ranges)];
	sensor_msgs::LaserScan noiseyScan;

	ROS_INFO("Created noiseyScan object");
	std::srand(time(0));
	int randomNumber = std::rand() % 1;
	ROS_INFO("Initialized random number using current time.");

	// for(int i = 0; i < countof(scan.intensities); i++){ //TODO: Check if length function of float32[] is real
	// 	ROS_INFO("maybe the error is out of bounds??");
	// 	if( randomNumber >= (1-SNR) ){ //should converge on SNR over time for all the signal noise n stuff.  I could test this.  See if LaserScan.intensity[i] / NoiseyScan.intensity[i] == 1 or not, then divide the nots by the 1's and that should equal SNR after a while 
	// 		ROS_INFO("maybe the error is here");
	// 		if((randomNumber*10)%2 == 0){ //Using the same number to see if its even or odd (50/50 chance, right?)
	// 			noiseyScan.intensities[i] += (float)addGaussianNoise(.01);
	// 		} else{
	// 			noiseyScan.intensities[i] -= (float)addGaussianNoise(.01);
	// 		}
			
	// 	} else{
	// 		noiseyScan.intensities[i] = scan.intensities[i];
	// 	}
	// }
	
	
	//noiseyScan.ranges = scan.ranges;
	std::cout << (float)addGaussianNoise(.1) << std::endl;
	for(int i = 0; i < countof(scan.ranges); i++){ 
		noiseyScan.ranges[i] = noiseyScan.ranges[i] + addGaussianNoise(.5);
	}
	//noiseyScan.ranges = ranges;
	pub_.publish(noiseyScan);
}

int main(int argc, char** argv){
	ROS_INFO("Hey");
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
