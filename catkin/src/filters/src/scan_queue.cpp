/*
* scan_queue
* A ROS node to parse and enqueue elements from the rangemap for position checking for the sensor model.
*
* Luc A. Bettaieb
* bettaieb@case.edu
*
* 11.11.14 (Began work)
*/

#include <ros/ros.h>

#include <algp1_msgs/PoseScan.h>
#include <std_msgs/Bool.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

ros::Publisher pub_PoseScan_;	//Publisher to provide a new PoseScan message to sense_model
ros::Subscriber sub_newBool_;	//Subscriber to check whether or not to get a new set of data from the rangemap.

bool newData_ = true;			//Global boolean to determine whether or not to get a new set of data from the rangemap.

void parseFile(){
	std::ifstream fin;
	fin.open("rangemap_simple.txt");
	if(!fin.good()){
		ROS_INFO("rangemap not found");
		ros::shutdown();
	}
	std::vector<std::string> list;
	list.clear();
	std::string line;
	line.resize(6000);
	ROS_INFO("Copying file to vector");

	for(int i = 0; i < 1960; i++){
		if(std::getline(fin, line)){
			list.push_back(line);
		}
	}
	ROS_INFO("Done copying file to vector.");
	for(int i = 0; i < 1960; i+= 10){
		std::cout<< list.at(i) << std::endl;
	}
}

int main(int argc, char** argv){
	ros::init(argc, argv, "scan_queue");
	ros::NodeHandle nh;

	pub_PoseScan_ = nh.advertise<algp1_msgs::PoseScan>("scan_queue", 1);
	//sub_newBool_ = nh.subscribe("/newData", 10, updateBool);
	parseFile();

	ros::spin();
	return 0;
}