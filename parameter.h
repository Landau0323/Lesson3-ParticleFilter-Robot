//
// Created by 研究用 on 2017/08/22.
//

#ifndef ROBOT_PARAMETER_H
#define ROBOT_PARAMETER_H

//なぜかconstつけないとビルドエラーになる

const double PI=3.14159265359;

const double world_size=100.0;
const int num_landmark=4;
const int num_robot=1000;

//const double forward_noise=5.0;
//const double turn_noise=0.1;
const double forward_noise=0.05;
const double turn_noise=0.05;
const double sense_noise=5.0;

#endif //ROBOT_PARAMETER_H
