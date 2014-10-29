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
#include <cstdlib>
//#include <iostream>
#include <random> 

ros::Publisher pub_;
ros::Subscriber sub_;

//Random number generator and normal distribution (by default N(0,1))
float mu = 0;
float sigma = 1;

//std::default_random_engine generator;
std::normal_distribution<std_msgs::Float32> distribution(mu, sigma);

//Signal to noise ratio
//Will act as a constant to define how much noise is delivered to the signal
float SNR = 0.5;			

int main(int argc, char** argv){
	//Standard ROS Initialization Stuff
	ros::init(argc, argc, "noisey");
	ros::NodeHandle nh;
	//Init random number generator with time seed

	sub_ = nh.subscribe("/robot0/LaserScan", 1, addNoiseLaser); //make sure its robot0...  This may need to be fixed

}
 
//Callback function for when node recieves a signal value (should be forever)
void addNoiseLaser(const sensor_msgs::LaserScan &scan){ //need to get sensor_msgs/LaserScan, iterate through ranges[] and add noise then publish new laserscan
	sensor_msgs::LaserScan noiseyScan;
	
	std::srand(time(0));
	int randomNumber = std::rand() % 1;

	for(int i = 0; i < scan.intensities.length(); i++){ //TODO: Check if length function of float32[] is real\
		if(randomNumber >= (1-SNR)){ //should converge on SNR over time for all the signal noise n stuff.  I could test this.  See if LaserScan.intensity[i] / NoiseyScan.intensity[i] == 1 or not, then divide the nots by the 1's and that should equal SNR after a while 
			noiseyScan.intensities[i] = distribution(scan.intensities[i]);
		}
		else{
			noiseyScan.intensities[i] = scan.intensities[i];
		}
	}

	pub_.publish(noiseyScan);
}