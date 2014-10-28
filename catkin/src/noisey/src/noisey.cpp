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
#include <std_msgs>
#include <sensor_msgs>
//#include <random> not sure if this is real

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

	sub_ = nh.subscribe("/robot0/LaserScan", 1, addNoiseLaser); //make sure its robot0

}
 
//Callback function for when node recieves a signal value (should be forever)
void addNoiseLaser(const sensor_msgs::LaserScan &scan){ //need to get sensor_msgs/LaserScan, iterate through ranges[] and add noise then publish new laserscan
	sensor_msgs::LaserScan noiseyScan;
	for(int i = 0; i < scan.intensities.length(); i++){ //TODO: Check if length function of float32[] is real
		noiseyScan.intensities[i] = distribution(scan.intensities[i]);
	}

	pub_.publish(noiseyScan);
}