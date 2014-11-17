/*
* kf
* A ROS node to implement a kalman filter using a probabalistic velocity model
* and a probabalistic sensor model.  Will return a gaussian to tell you what's good.
*
* Luc A. Bettaieb
* bettaieb@case.edu
* 
* 11.8.14 (Began work)
*/

#include <ros/ros.h>
#include <stdio.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <algp1_msgs/Pose2DWithCovariance.h>

typedef float array_3x3_type[3][3];
typedef float array_3x1_type[3];

ros::Publisher pub_state_;

ros::Subscriber sub_sense_model_;
ros::Subscriber sub_vel_model_;

algp1_msgs::Pose2DWithCovariance vel_model_;
algp1_msgs::Pose2DWithCovariance sense_model_;

int kalmanIteration = 0;


//Callback function to update the velocity model var
void updateVelocityModel(const algp1_msgs::Pose2DWithCovariance &vel){
	vel_model_ = vel;
}

//Callback function to update the sensor model var
void updateSensorModel(const algp1_msgs::Pose2DWithCovariance &sen){
	sense_model_ = sen;
}

void multiply3x3(array_3x3_type& arr, float a[3][3], float b[3][3]){

	arr[0][0] = (a[0][0]* b[0][0]) + (a[0][1]* b[1][0]) + (a[0][2]* b[2][0]);
	arr[0][1] = (a[1][0]* b[0][0]) + (a[1][1]* b[1][0]) + (a[1][2]* b[2][0]);
	arr[0][2] = (a[2][0]* b[0][0]) + (a[2][1]* b[1][0]) + (a[2][2]* b[2][0]);

	arr[1][0] = (a[0][0]* b[0][1]) + (a[0][1]* b[1][1]) + (a[0][2]* b[2][1]);
	arr[1][1] = (a[1][0]* b[0][1]) + (a[1][1]* b[1][1]) + (a[1][2]* b[2][1]);
	arr[1][2] = (a[2][0]* b[0][1]) + (a[2][1]* b[1][1]) + (a[2][2]* b[2][1]);
	
	arr[2][0] = (a[0][0]* b[0][2]) + (a[0][1]* b[1][2]) + (a[0][2]* b[2][2]);
	arr[2][1] = (a[1][0]* b[0][2]) + (a[1][1]* b[1][2]) + (a[1][2]* b[2][2]);
	arr[2][2] = (a[2][0]* b[0][2]) + (a[2][1]* b[1][2]) + (a[2][2]* b[2][2]);

}

void add3x3(array_3x3_type& arr, float a[3][3], float b[3][3]){

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			arr[i][j] = a[i][j] + b[i][j];
		}
	}

}

void sub3x3(array_3x3_type& arr, float a[3][3], float b[3][3]){

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			arr[i][j] = a[i][j] - b[i][j];
		}
	}

}

void sub3x1(array_3x1_type& arr, float a[3], float b[3]){

	for(int j = 0; j < 3; j++){
		arr[j] = a[j] - b[j];
	}

}


void kf(float prevMean, float prevCov[3][3], algp1_msgs::Pose2DWithCovariance action, algp1_msgs::Pose2DWithCovariance measure){
	if(true == false){ //Base case death
		ros::shutdown();
	}

	//All matricies are represented in row-major notation
	// {1, 2, 3 / 4, 5, 6 / 7, 8, 9} ya dig?

	//The initial state prediction goes here
	float X_o [3]={		1,
					 	1,
					 	0
					};
	//

	float A [3][3] = {{	1,		0,		0},
					 {	0,		1,		0},
					 {	0,		0,		1}};
	float A_t [3][3] =	{{	1,		0,		0},
					 {	0,		1,		0},
					 {	0,		0,		1}};
					 				
	float H [3][3] = {{	1,		0,		0},
					 {	0,		1,		0},
					 {	0,		0,		1}};

	float P [3][3] = {{	1,		0,		0},
					 {	0,		1,		0},
					 {	0,		0,		1}};

	float Q [3][3] = {{	0.01,	0,		0},
					 {	0,		0.01,	0},
					 {	0,		0,		0.01}};

	float R [3][3] = {{	1,		0,		0},
					 {	0,		1,		0},
					 {	0,		0,		1}};

	float meanBar;

	float X_p[2];	//State prediction (from velocity model)
	X_p[0] = action.pose2d.x;
	X_p[1] = action.pose2d.y;
	X_p[2] = action.pose2d.theta;

	//float Z_n[2]

	//float P_p[3][3] = add3x3(multiply3x3(multiply3x3(A,P), A_t), Q);
	
	//float Y_tilde[3] = sub3x1();
}


int main(int argc, char** argv){
	ros::init(argc, argv, "kf");
	ros::NodeHandle nh;

	//needs to accept a P(x| sensor) and a P(x| velocity)
	sub_vel_model_ = nh.subscribe("/vel_model", 10, updateVelocityModel);
	sub_sense_model_ = nh.subscribe("/sense_model", 10, updateSensorModel);

	//then publish a P(x| the fusion of the two n stuff)
	pub_state_ = nh.advertise<algp1_msgs::Pose2DWithCovariance>("/robot0/kf/state", 1);

	float initCov[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

	//now go forth and do work, son.

	kf(0, initCov, vel_model_, sense_model_);

	ros::spin();
	return 0;
}