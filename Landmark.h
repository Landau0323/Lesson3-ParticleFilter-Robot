//
// Created by 研究用 on 2017/08/22.
//

#ifndef ROBOT_LANDMARK_H
#define ROBOT_LANDMARK_H

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


class Landmark {
private:
    double x,y;

public:
    void set_position(double,double);

    double getX() const;
    double getY() const;

};


#endif //ROBOT_LANDMARK_H
