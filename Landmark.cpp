//
// Created by 研究用 on 2017/08/22.
//

#include "Landmark.h"

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

void Landmark::set_position(double input_x, double input_y) {
    x=input_x;
    y=input_y;
}

double Landmark::getX() const {
    return x;
}
double Landmark::getY() const {
    return y;
}
