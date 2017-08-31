//
// Created by 研究用 on 2017/08/22.
//

#include "ParticleFilter.h"
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
#include <random>

using namespace std;

double uniform_random(double upper=1, double lower=0);

//constructor
ParticleFilter::ParticleFilter() {
    cout<<"particle filter start!"<<endl;
    robots.resize(num_robot);
    for(int i=0;i<num_robot;i++){
        //initial state of particles are uniform and random
        double x=uniform_random(world_size,0);
        double y=uniform_random(world_size,0);
        double theta=uniform_random(2.0*PI,0);
        robots[i].set_state(x,y,theta);
    }

    //also set the real position and orientation
    true_position.set_state(45, 50, 0); //test case 1:[45,50,0]
}

///////////////movement phase/////////////////
void ParticleFilter::move(double input_theta,double input_r) {
    cout<<"Move with the order ("<<input_theta<<", "<<input_r<<")"<<endl;
    for(int i=0;i<num_robot;i++) robots[i].move(input_theta,input_r);
    true_position.move(input_theta,input_r);
}

///////////////measurement phase/////////////////
void ParticleFilter::measure(vector<double> input_measurement, vector<Landmark> landmarks) {
    cout<<"Measure. Result of measurement is [";
    for(int i=0;i<num_landmark;i++) cout<<input_measurement[i]<<" ";
    cout<<"]"<<endl;

    expect_measurement(landmarks);  //expect result of measurement from positions of each particle
    evaluate_weight(input_measurement); //evaluate weight from difference of expected result and actual result
    resample(); //resampling

}

//update the expected result of measurement for each particle
void ParticleFilter::expect_measurement(vector<Landmark> landmarks) {
    cout<<"expect measurement"<<endl;
    for(int i=0;i<num_robot;i++){
        robots[i].sense(landmarks);
    }

    true_position.sense(landmarks);
    cout<<"measurement result from true position should be [";
    for(int i=0;i<num_landmark;i++) cout<<true_position.getExpected_measurement()[i]<<" ";
    cout<<endl;
}

//evaluate weight for each particle based on measurement result and expected value of measurement
void ParticleFilter::evaluate_weight(vector<double> input_measurement) {
    cout<<"evaluate weight"<<endl;
    for(int n=0;n<num_robot;n++) {
        double dist=0;
        for (int i = 0; i < num_landmark; i++) {
            vector<double> expected(num_landmark);
            expected[i]=robots[n].getExpected_measurement()[i];
//cout<<i<<" "<<input_measurement[i]<<" "<<expected[i]<<endl;
            dist += (input_measurement[i]-expected[i])
                    * (input_measurement[i]-expected[i])
                    / (2.0 * sense_noise * sense_noise);
        }
        robots[n].setWeight(exp(-dist));

        //for debug
        if(exp(-dist)>0.8){
            cout<<"weight:"<<exp(-dist)<<" position:";//<<" "<<robots[n].getWeight()<<endl;
            robots[n].show_state();
        }

    }

    double temp=0;
    for (int i = 0; i < num_landmark; i++) {
        vector<double> expected(num_landmark);
        expected[i]=true_position.getExpected_measurement()[i];
//cout<<i<<" "<<input_measurement[i]<<" "<<expected[i]<<endl;
        temp += (input_measurement[i]-expected[i])
                * (input_measurement[i]-expected[i])
                / (2.0 * sense_noise * sense_noise);
    }
    true_position.setWeight(exp(-temp));
    cout<<"weight for true position particle (it should be 1):"<<true_position.getWeight()<<endl;
}

//resampling from the set of the particles
void ParticleFilter::resample() {
    cout<<"resampling"<<endl;
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    //weightsにrobot N個それぞれの重みを格納
    vector<double> weights(num_robot);
    for(int i=0;i<num_robot;i++) weights[i]=robots[i].getWeight();

    //discrete_distributionを使って重みを反映した乱数生成（乱数は整数、範囲は0からnum_robotまで）
    discrete_distribution<> distri (weights.begin(), weights.end());

    //resample後のparticle
    vector<Robot> resampled_particles(num_robot);
    for(int i=0;i<num_robot;i++) {
        int id=distri(engine);
        resampled_particles[i]=robots[id];
        if(resampled_particles[i].getWeight()>0.8){
            cout<<"weight:"<<resampled_particles[i].getWeight()<<" position:";//<<" "<<robots[n].getWeight()<<endl;
            resampled_particles[i].show_state();
        }
    }

    robots.clear();
    robots=resampled_particles;
    resampled_particles.clear();

}

///////////////////interface//////////////////
//show the average position and the angle
void ParticleFilter::show_average() {
    double x,y,theta;
    x=y=theta=0;

    for(int i=0;i<num_robot;i++){
        x+=robots[i].getX()/num_robot;
        y+=robots[i].getY()/num_robot;
        theta+=robots[i].getTheta()/num_robot;
    }
    cout<<"average position is ["<<x<<", "<<y<<", "<<theta<<"]"<<endl;
    cout<<"true position is [" <<true_position.getX()<< ", " <<true_position.getY()
        << ", "<<true_position.getTheta()<< "]" <<endl;
}

void ParticleFilter::show_state_all() {
    for(int i=0;i<num_robot;i++) robots[i].show_state();
}

void ParticleFilter::write_particles() {
    cout<<"writing data"<<endl;

    string filename_data="particles.dat";
    ofstream fout;
    fout.open(filename_data,ios::app);

    for(int i=0;i<robots.size();i++){
        fout<< robots[i].getX()<<" "<<robots[i].getY()<<" "
            <<robots[i].getTheta() <<endl;
    }
    fout<<endl<<endl;

    fout.close();

}
