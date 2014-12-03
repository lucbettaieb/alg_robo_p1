/*
*	Noisey Library
*	A library for adding noise to signals such as a laser scan.
*
*
*/
#ifndef NOISEY_H
#define NOISEY_H
class noisey {
	
public:	
	sensor_msgs::LaserScan addNoiseLaserScan(sensor_msgs::LaserScan oldScan);
};


#endif