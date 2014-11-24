/*
* scan_queue_2
* a ros node to correctly parse and enqueue elements from the rangemap for position tolerance checking
*
* Luc A Bettaieb
* bettaieb@case.edu
*
* 11.20.14
*/

#include <ros/ros.h>

#include <algp1_msgs/PoseScan.h>
#include <algp1_msgs/PoseScanVector.h>

#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <queue>

ros::Publisher pub_PoseScan_;	//Publisher to publish a new poseScan
algp1_msgs::PoseScanVector psv;

int angleCount_ = 2;

void parseFile(){
	algp1_msgs::PoseScan poseScan;

	std::vector<std::string> list;
	std::string line;
	std::ifstream fin;

	fin.open("rangemap_simple.txt");

	if(!fin.good()){
		ROS_INFO("Rangemap not found");
		ros::shutdown();
	}

	list.clear();

	ROS_INFO("Copying file to vector.");

	while(std::getline(fin, line)){
		list.push_back(line);
	}

	ROS_INFO("Done copying file to vector.  Each element of the vector is a line of the file.");
	for(int xy = 0; xy < list.size(); xy += 10){ //Every 10th element is a X or Y
		//algp1_msgs::PoseScan *poseScan = new algp1_msgs::PoseScan;

		//For every 10th element, starting at 10,
		int comma = list.at(xy).find(",");

		std::vector<std::string> range_vector; //should contain 8 ranges per iteration

		std::string ex = list.at(xy).substr(1,comma-1);
		std::string wy = list.at(xy).substr(comma+1);
		wy.resize(wy.size()-1);

		float x = std::atof(ex.c_str());
		float y = std::atof(wy.c_str());

		poseScan.pose2d.x = x;
		poseScan.pose2d.y = y;

		for(int a = xy+1; a < xy+9; a++){

			
			std::string ranges;
			ranges = list.at(a); //get the string correspoinding to xy+1(+a)

			std::istringstream ss(ranges);
			while(ss){
				std::string ranges;
				if(!getline(ss, ranges, ',')) break;
				range_vector.push_back(ranges);
			}

			//rangeVector is now populated with ranges corresponding to a certain angle for a certain xy
			poseScan.pose2d.theta = a % 10;

			

			for(int ran = 0; ran < range_vector.size(); ran++){
				poseScan.ranges.push_back(std::atof(range_vector.at(ran).c_str()));
			}

			//Add to queue
			//scanQueue_.push(poseScan);
			psv.scans.push_back(poseScan);
			//pub_PoseScan_.publish(poseScan); //for publishing

			range_vector.clear();
			poseScan.ranges.clear();

			//ros::Duration(1).sleep(); //for publishing
			//ros::spinOnce(); //for publishing
		}
	}
}

int main(int argc, char** argv){
	ros::init(argc, argv, "scan_queue");
	ros::NodeHandle nh;

	pub_PoseScan_ = nh.advertise<algp1_msgs::PoseScanVector>("/scan_map", 1);
		
	ROS_INFO("Parsing file and adding to queue.");
	parseFile();
	ROS_INFO("Done adding to queue");
	int it = 0;

	ROS_INFO("Continually publishing PoseScanVector");
	while(ros::ok()){

		pub_PoseScan_.publish(psv);
		ROS_INFO("Pub'd.");
		ros::Duration(1).sleep(); //for publishing
		
		ros::spinOnce();
	}

	//ros::spin();
	return 0;
}