#include <iostream>
#include <vector>

#include "Robot.h"
#include "Landmark.h"
#include "parameter.h"
#include "ParticleFilter.h"

using namespace std;

int main() {

    vector<Landmark> landmark(num_landmark);
    //landmark positions: [20,20] [80,80] [20,80] [80 20]
    landmark[0].set_position(20,20);
    landmark[1].set_position(80,80);
    landmark[2].set_position(20,80);
    landmark[3].set_position(80,20);

/*
    //code for test of class Robot
    cout<<"Test for Robot class"<<endl;
    Robot r;

    cout<<"test case 1"<<endl;
    //1: go straight to x-direction
    r.set_state(10,10,0);
    r.show_state();
    r.move(0,10);
    r.show_state();
    cout<<endl;

    cout<<"test case 2"<<endl;
    //2:turn left (positive angle means left turn) by 90 degree, and go straight (y-direction)
    r.set_state(10,10,0);
    r.show_state();
    r.move(PI/2,10);
    r.show_state();
    r.sense(landmark);
    r.show_expected_measurement();
    cout<<endl;

    cout<<"test case 3"<<endl;
    //3:turn right by 90 degree and go straight (x-direction), then turn right by 90 degree and go straight (-y direction)
    r.set_state(30,50,PI/2);
    r.show_state();
    r.move(-PI/2,15);
    r.show_state();
    r.sense(landmark);
    r.show_expected_measurement();
    r.move(-PI/2,10);
    r.show_state();
    r.sense(landmark);
    r.show_expected_measurement();
    cout<<endl;

    r.move(0,10);
    r.show_state();
    r.sense(landmark);
    r.show_expected_measurement();
    r.move(PI/2,20);
    r.show_state();
    r.sense(landmark);
    r.show_expected_measurement();
*/


    //Particle filter starts
    ParticleFilter* p_set=new ParticleFilter();
    p_set->write_particles();

    //Movement phase
//    p_set->move(-PI/2,15);
//    p_set->write_particles();
//    p_set->show_average();

    //Measurement phase
    vector<double> input_measure(num_landmark);
    input_measure[0]=39; input_measure[1]=46; input_measure[2]=39; input_measure[3]=46;
    cout<<"true position is [45, 50, 0]"<<endl;
    p_set->measure(input_measure,landmark);
    p_set->write_particles();
    p_set->show_average();
    cout<<endl;

    //Movement phase
    p_set->move(-PI/2, 10);
    p_set->write_particles();
    p_set->show_average();
    cout<<endl;

    //Measurement phase
    input_measure[0]=32; input_measure[1]=53.1; input_measure[2]=47.1; input_measure[3]=40.3;
    cout<<"true position is [45, 40, 4.71]"<<endl;
    p_set->measure(input_measure,landmark);
    p_set->write_particles();
    p_set->show_average();
    cout<<endl;

    //Movement phase
    p_set->move(0, 10);
    p_set->write_particles();
    p_set->show_average();
    cout<<endl;

    //Measurement phase
    input_measure[0]=27.7; input_measure[1]=60.2; input_measure[2]=55.6; input_measure[3]=36.0;
    cout<<"true position is [45, 30, 4.71]"<<endl;
    p_set->measure(input_measure,landmark);
    p_set->write_particles();
    p_set->show_average();
    cout<<endl;

    //Movement phase
    p_set->move(PI/2, 20);
    p_set->write_particles();
    p_set->show_average();
    cout<<endl;

    //Measurement phase
    input_measure[0]=47; input_measure[1]=50.6; input_measure[2]=66.5; input_measure[3]=18.5;
    cout<<"true position is [65, 30, 0]"<<endl;
    p_set->measure(input_measure,landmark);
    p_set->write_particles();
    p_set->show_average();
    cout<<endl;

    delete p_set;

    //true position of robot
    string filename="true_robot.dat";
    ofstream fout_true;
    fout_true.open(filename,ios::out);
    fout_true<< 45<<" "<<50<<" " <<0 <<endl<<endl<<endl;
    fout_true<< 45<<" "<<40<<" " <<3*PI/2 <<endl<<endl<<endl;
    fout_true<< 45<<" "<<30<<" " <<3*PI/2 <<endl<<endl<<endl;
    fout_true<< 65<<" "<<30<<" " <<0 <<endl<<endl<<endl;
    fout_true.close();

    return 0;
}

//////////////test case 1//////////////
//(initial position: 30,50,PI/2)
//movement [-PI/2, 15]
//measurement [39.0, 46.0, 39.0, 46.0] -> position [45,50,0]
//movement [-PI/2,10]
//measurement [32.0, 53.1, 47.1, 40.3] ->position [45,40,-PI/2=3*PI/2=4.71]
///////////////////////////////////////

//input_measure[0]=10; input_measure[1]=92.1954; input_measure[2]=60.8276; input_measure[3]=70;
//measurement result [10.0, 92.195444572928878, 60.87625302982199, 70.0] implies the robot position [10,20,1.57]
//measurement result [39.0, 46.0, 39.0, 46.0] implies the robot position [45,50]
//measurement result [32.0, 53.1, 47.1, 40.3] implies the robot position [45,40]

//////////////test case 2//////////////
//after test case 1, we add the following:
//movement [0,10]
//measurement [27.7, 60.2, 55.6, 36.0] -> position [45,30,-PI/2=4.71]
//movement [PI/2,20]
//measurement [47.0, 50.6, 66.5, 18.5] -> position [65,30,0]
///////////////////////////////////////

