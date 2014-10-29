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
#include <random>

ros::Publisher pub_;
ros::Subscriber sub_;

//Random number generator and normal distribution (by default N(0,1))
float mu = 0;
float sigma = 1;

//std::default_random_engine generator;
std::normal_distribution<float> distribution(mu, sigma);

//Signal to noise ratio
//Will act as a constant to define how much noise is delivered to the signal
float SNR = 0.5;			

int main(int argc, char** argv){
	//Standard ROS Initialization Stuff
	ros::init(argc, argc, "noisey")

}
 
//Callback function for when node recieves a signal value (should be forever)
float addNoise(const std_msgs::Float64 &signal){
	return distribution(signal.data); //simply trying to use the input to the dist. as the sigval
}

