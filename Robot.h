//
// Created by 研究用 on 2017/08/22.
//

#ifndef ROBOT_ROBOT_H
#define ROBOT_ROBOT_H

#include <cmath>
#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Landmark.h"

using namespace std;


class Robot {
private:
    double x,y,theta;
    double weight;
    vector<double> expected_measurement;

public:
    void move(double,double);
    void sense(vector<Landmark>);

    void show_state();
    void show_expected_measurement();

    void set_state(double,double,double);
    void setWeight(double weight);
    double getX() const;
    double getY() const;
    double getTheta() const;
    double getWeight() const;
    const vector<double> &getExpected_measurement() const;
};

#endif //ROBOT_ROBOT_H
