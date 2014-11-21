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
#include <nav_msgs/Odometry.h>

#include <std_msgs/Bool.h>

#include <algp1_msgs/Pose2DWithCovariance.h>
#include <algp1_msgs/PoseScan.h>
#include <algp1_msgs/PoseScanVector.h>


ros::Publisher pub_model_;	//To publish the odom with variance derived from vel
ros::Publisher pub_newDataBool_;

ros::Subscriber sub_Laser_;	//To subscribe to noiseyscan
ros::Subscriber sub_Map_;
ros::Subscriber sub_Odom_; //subscribing to /robot0/odom to see if there will be a change

sensor_msgs::LaserScan current_scan_; //access ranges
algp1_msgs::PoseScanVector pose_scan_vector_; 	//access ranges
std::vector<geometry_msgs::Pose2D> potentialPoses_;

algp1_msgs::Pose2DWithCovariance dat_pose_doe_;

// float current_avg_ = 0;

const float tolerance_ = 0.25;

void updateLaser(const sensor_msgs::LaserScan &laser){
	//ROS_INFO("Got new scan data, current_scan_ updated.");
	current_scan_ = laser;
	// int numInf = 0;
	// for(int i = 0; i < current_scan_.ranges.size(); i++){
	// 	if(current_scan_.ranges.at(i) < 10000){ //if !inf
	// 		current_avg_ += current_scan_.ranges.at(i);
	// 	} else numInf++;
	// }
	// current_avg_ /= (current_scan_.ranges.size()-numInf);
}

void updateMap(const algp1_msgs::PoseScanVector &scan){
	//ROS_INFO("Got new pose scan vector!");
	pose_scan_vector_ = scan;
}

float averageDifferenceScans(sensor_msgs::LaserScan &scan1, algp1_msgs::PoseScan &scan2){ //pass by reference because we will only be accessing the vector elements
	//ROS_INFO("hi");
	float avg = 0;
	int numInf=0;
	for(int i = 0; i < scan1.ranges.size(); i++){
		if(scan1.ranges.at(i) < 10000000000 && scan2.ranges.at(i) < 10000000000){
			avg += std::abs(scan1.ranges.at(i) - scan2.ranges.at(i));
		} else numInf++;
	}

	return avg / (scan1.ranges.size()-numInf);
}

void updateModel(const nav_msgs::Odometry &odom){
	//ROS_INFO("Updating");
	for(int i = 0; i < pose_scan_vector_.scans.size(); i++){
		
		//for(int j = 0; j < pose_scan_vector_.scans.at(i).ranges.size(); j++){
		//std::cout << averageDifferenceScans(current_scan_, pose_scan_vector_.scans.at(i)) <<std::endl;
			if(averageDifferenceScans(current_scan_, pose_scan_vector_.scans.at(i)) < tolerance_){
				//ROS_INFO("did we do it we did it");
				dat_pose_doe_.pose2d.y = pose_scan_vector_.scans.at(i).pose2d.x; //WEIRD NOTE, swapping X and Y here because idk, it got messed up somewhere so im fixing it here
				dat_pose_doe_.pose2d.x = pose_scan_vector_.scans.at(i).pose2d.y;
				dat_pose_doe_.pose2d.theta = pose_scan_vector_.scans.at(i).pose2d.theta;
				

				pub_model_.publish(dat_pose_doe_);
			}

			
	}

	for(int i = 0; i < potentialPoses_.size(); i++){	
		std::cout << potentialPoses_.at(i).x << " | " << potentialPoses_.at(i).y << " | "<< potentialPoses_.at(i).theta << std::endl;
	}

	//ros::spinOnce();
}

int main(int argc, char** argv){
	ros::init(argc, argv, "sense_model");
	ros::NodeHandle nh;

	pub_newDataBool_ = nh.advertise<std_msgs::Bool>("/update_queue", 1);  //publish a TRUE to get new data.  Upon recieving new data, publish FALSE
	pub_model_ = nh.advertise<algp1_msgs::Pose2DWithCovariance>("/sense_model", 1); //publisher for sensor model

	sub_Laser_ = nh.subscribe("/noiseyScan", 10, updateLaser);
	sub_Map_ = nh.subscribe("/scan_map", 10, updateMap);
	sub_Odom_ = nh.subscribe("/robot0/odom", 10, updateModel);

	ros::spin();
}