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
#include <iostream>

void InvMatrix(float src[][3], float dst[][3]);

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

float determinant(float matrix[][3])
{
    float det = 0;
    for (int i = 0; i < 3; ++i)
        det += matrix[0][i]*matrix[1][(i+1)%3]*matrix[2][(i+2)%3]
               - matrix[2][i]*matrix[1][(i+1)%3]*matrix[0][(i+2)%3];
    return det;
}

float min0r(float matrix[][3], int row, int col)
{
    int ir = row == 1 ? -1 : 1;
    int ic = col == 1 ? -1 : 1;
    float a = matrix[(row+ir+3)%3][(col+ic+3)%3];
    float b = matrix[(row+ir+3)%3][(col-ic+3)%3];
    float c = matrix[(row-ir+3)%3][(col+ic+3)%3];
    float d = matrix[(row-ir+3)%3][(col-ic+3)%3];
    return a*d - b*c;
}

void getCofactorMatrix(float src[][3], float dst[][3])
{
    bool neg = false;
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
        {
            dst[r][c] = min0r(src, r, c) * (neg ? -1 : 1);
            neg = !neg;
        }
}

void swapValue(float& a, float& b)
{
    float temp = a;
    a = b;
    b = temp;
}

void transpose(float matrix[][3])
{
    for (int r = 0; r < 3; ++r)
        for (int c = r+1; c < 3; ++c)
            if (r != c)
                swapValue(matrix[r][c], matrix[c][r]);
}

void InvMatrix(float src[][3], float dst[][3])
{
    float det = determinant(src);
    if (!det) throw "Singular matrix, cannot inverse.";
    getCofactorMatrix(src, dst);
    transpose(dst);
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            dst[r][c] /= det;
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
	float Z_n [3];
	Z_n[0] = sense_model_.pose2d.x;
	Z_n[1] = sense_model_.pose2d.y;
	Z_n[2] = sense_model_.pose2d.theta;


	float A [3][3] = {{	1,		0,		0},
					 {	0,		1,		0},
					 {	0,		0,		1}};
	float A_t [3][3] =	{{	1,		0,		0},
					 {	0,		1,		0},
					 {	0,		0,		1}};
					 				
	float H [3][3] = {{	1,		0,		0},	//plz make this stay I so everything below works
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



	//------ State prediction (from velocity model)
	float X_p[2];	
	X_p[0] = action.pose2d.x;
	X_p[1] = action.pose2d.y;
	X_p[2] = action.pose2d.theta;

	
	//------ Covariance Prediction
	float APnm1[3][3];
	multiply3x3(APnm1, A, P);
	
	float APnm1At[3][3];
	multiply3x3(APnm1At, APnm1, A_t);
	
	float P_p[3][3];
	add3x3(P_p, APnm1At, Q);

	//------Innovation
	float Y_tilde[3];

	sub3x1(Y_tilde, Z_n, X_p); //NOTE: In a fully implemented kalman filter where H is not [I], this step is incorrect.

	//------Innovation Covariance
	float HP_p[3][3];
	multiply3x3(HP_p, H, P_p);

	float HP_pHt[3][3];
	multiply3x3(HP_pHt, HP_p, H); //NOTE: In this case I assume H = H^T

	float S[3][3];
	add3x3(S, HP_pHt, R);

	//------Kalman Gain
	


	
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