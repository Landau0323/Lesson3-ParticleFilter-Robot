//
// Created by 研究用 on 2017/08/22.
//

#include "Robot.h"
#include "parameter.h"

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

double Gaussian_random(double sigma=1);

void Robot::set_state(double input_x, double input_y, double input_theta) {
    x=input_x;
    y=input_y;
    theta=input_theta;
}

void Robot::show_state() {
    cout<<"[x="<<x<<" y="<<y<<" heading="<<theta<<"]"<<endl;
}

//move according to the order
void Robot::move(double input_theta,double input_r) {
//cout<<"input:["<<input_theta<<" "<<input_r<<"]"<<endl;
    //add noise to the movement order
    input_theta+=Gaussian_random(turn_noise);
    input_r+=Gaussian_random(forward_noise);

    //calculate rotation and movement (the order is important: rotate, then move)
    theta+=input_theta;
    x+=input_r*cos(theta);
    y+=input_r*sin(theta);

    //cyclic boundary condition
    if(x<0) x+= world_size;
    if(x>100) x+= -world_size;
    if(y<0) y+= world_size;
    if(y>world_size)    y+= -world_size;

    //theta is defined with mod 2*PI
    if(theta<0) theta+= 2.0*PI;
    if(theta>2.0*PI) theta+= -2.0*PI;

    //for debug (sometimes result becomes nan)
    if(!(x<INT_MAX)){
        cout<<"Bug!";
        show_state();
        cout<<"input is ["<<input_theta<<" "<<input_r<<"]"<<endl;
    }
}

//update the expected result for the measurement (theta does not play role here)
void Robot::sense(vector<Landmark> landmarks) {
    expected_measurement.resize(num_landmark);
    expected_measurement.clear();

//cout<<"[";
    for(int i=0;i<num_landmark;i++){
        double r=sqrt((x-landmarks[i].getX())*(x-landmarks[i].getX())
                      +(y-landmarks[i].getY())*(y-landmarks[i].getY()));
//if(i!=num_landmark-1) cout<<r<<", ";
//else cout<<r;
        expected_measurement[i]=r;
    }
//    cout<<"]"<<endl;
}

void Robot::show_expected_measurement() {
    cout<<"expected measurement: [";
    for(int i=0;i<num_landmark;i++){
    if(i!=num_landmark-1) cout<<expected_measurement[i]<<", ";
    else cout<<expected_measurement[i];
    }
    cout<<"]"<<endl;
}

void Robot::setWeight(double weight) {
    Robot::weight = weight;
}
double Robot::getX() const {
    return x;
}
double Robot::getY() const {
    return y;
}
double Robot::getTheta() const {
    return theta;
}
const vector<double> &Robot::getExpected_measurement() const {
    return expected_measurement;
}
double Robot::getWeight() const {
    return weight;
}

