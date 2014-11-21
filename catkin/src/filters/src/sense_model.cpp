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

#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Bool.h>
#include <algp1_msgs/Pose2DWithCovariance.h>
#include <algp1_msgs/PoseScan.h>

ros::Publisher pub_model_;	//To publish the odom with variance derived from vel
ros::Publisher pub_newDataBool_;

ros::Subscriber sub_Laser_;	//To subscribe to noiseyscan
ros::Subscriber sub_Map_;

sensor_msgs::LaserScan current_scan_; //access ranges
algp1_msgs::PoseScan pose_scan_; 	//access ranges
std::vector<geometry_msgs::Pose2D> potentialPoses_;

const float tolerance_ = 1;

void updateLaser(const sensor_msgs::LaserScan &laser){
	ROS_INFO("Got new scan data, current_scan_ updated.");
	current_scan_ = laser;
}

void updateMap(const algp1_msgs::PoseScan &scan){
	ROS_INFO("got new pose scan");
	pose_scan_ = scan;
}

void getNewPoseScan(){
	std_msgs::Bool troo;
	troo.data = true;

	std_msgs::Bool flas;
	flas.data = false;


	pub_newDataBool_.publish(troo);
	//ros::Duration(1).sleep();

	//pub_newDataBool_.publish(flas);
}

int main(int argc, char** argv){
	ros::init(argc, argv, "sense_model");
	ros::NodeHandle nh;

	pub_newDataBool_ = nh.advertise<std_msgs::Bool>("/update_queue", 1);  //publish a TRUE to get new data.  Upon recieving new data, publish FALSE
	pub_model_ = nh.advertise<algp1_msgs::Pose2DWithCovariance>("sense_model", 1); //publisher for sensor model

	
	for(int a = 0; a < 1568; a++){
		getNewPoseScan();
		ros::Duration(.1).sleep();

		// for(int i = 0; i < pose_scan_.ranges.size(); i++){
		// 	if((current_scan_.ranges.at(i) < pose_scan_.ranges.at(i) + tolerance_) && current_scan_.ranges.at(i) > pose_scan_.ranges.at(i) - tolerance_){ //if within range
		// 		potentialPoses_.push_back(pose_scan_.pose2d); //add to potential choices
		// 	}
		// }


		//Check 10 times against first set of data
		//Loop through all values of PoseScan ranges to see if they are within a tolerance of current noiseyscan
		ros::spinOnce();
	}

	ros::spin();
}