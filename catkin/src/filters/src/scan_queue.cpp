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
	algp1_msgs::PoseScan poseScan;
	std::vector<std::string> list;
	std::string line;

	std::ifstream fin;
	fin.open("rangemap_simple.txt");
	if(!fin.good()){
		ROS_INFO("rangemap not found");
		ros::shutdown();
	}
	
	list.clear();
	
	line.resize(6000);
	ROS_INFO("Copying file to vector");

	for(int i = 0; i < 1960; i++){
		if(std::getline(fin, line)){ 	//If there is a line to get
			list.push_back(line);		//Push it to the vector
		}
	}

	ROS_INFO("Done copying file to vector.");

	for(int i = 0; i < 1960; i+= 10){ 	//For every 10th element ([x,y])
		int com = list.at(i).find(",");	//Find the comma
		std::vector<std::string> rangeVector;	//DEFINE VECTOR TO HOLD RANGES that will be assigned to pose2d things

		std::string ex = list.at(i).substr(1,com-1); 	//Create a string that will represent X
		std::string ey = list.at(i).substr(com+1);	 	//Create a strong that will represent Y] (for some reason the bracket stays)
		ey.resize(ey.size()-1);						 	//Remove the bracket

		float x = (float)std::atoi(ex.c_str());	//Make a float from the string for X
		float y = (float)std::atoi(ey.c_str());	//And Y

		for(int a = 0; a < 1960; a++){ 	//Loop through the entire vector again
			if((a % 10)!= 0){			//And if its not one of the lines where there is a []


				std::string ranges;
				//ranges.resize(6000);
				ranges = list.at(a);
				//std::cout << ranges.size() << std::endl;

				if(ranges.size() > 2){ //If the line is not blank
				
					ranges = list.at(a).substr(1);
					ranges.resize(ranges.size()-1);
			
					std::string tmp = ranges.substr(0);					//copy over ranges
					int delim = tmp.find(",");
							
					ranges = ranges.substr(delim+1); //ranges is now one element less

					if(delim > 1){
						tmp.resize(delim);
						rangeVector.push_back(tmp);
						//std::cout << a << " - "<< tmp << std::endl;

					}
				}
			}
		}
		poseScan.pose2d.x = x;	//Assign X to X in pose2d
		poseScan.pose2d.y = y;	//Assign Y to Y in pose2d
		for(int hi = 0; hi < rangeVector.size(); hi++)
			poseScan.ranges.push_back(std::atof(rangeVector.at(hi).c_str()));

		//A poseScan should be now fully defined for a designated X and Y position.
		//Theta can be accounted for with iterations
		//std::cout << poseScan.ranges.at(5) << std::endl;
		pub_PoseScan_.publish(poseScan);
	}
}

int main(int argc, char** argv){
	ros::init(argc, argv, "scan_queue");
	ros::NodeHandle nh;

	pub_PoseScan_ = nh.advertise<algp1_msgs::PoseScan>("/scan_queue", 1);
	//sub_newBool_ = nh.subscribe("/newData", 10, updateBool);

	parseFile();

	ros::spin();
	return 0;
}