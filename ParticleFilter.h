//
// Created by 研究用 on 2017/08/22.
//

#ifndef ROBOT_PARTICLEFILTER_H
#define ROBOT_PARTICLEFILTER_H

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
#include "Robot.h"

using namespace std;

class ParticleFilter {
private:
    vector<Robot> robots;
    Robot true_position;

public:
    ParticleFilter();

    void show_state_all();
    void write_particles();
    void show_average();

    void move(double,double);

    void measure(vector<double>,vector<Landmark>);
    void expect_measurement(vector<Landmark>);
    void evaluate_weight(vector<double>);
    void resample();

};


#endif //ROBOT_PARTICLEFILTER_H
