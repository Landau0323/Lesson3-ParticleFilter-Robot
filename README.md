# Lesson3-ParticleFilter-Robot
Codes for the exercises in udacity program "Artificial Intelligence for Robotics" (3: particle filter). 

This is a program for localization of robot moving on a plane following the inputted order. 
When the robot moves, it first rotates, and then go straight.
The order for movement is given in terms of (theta, R), which are the rotation angle and the length of going straight.
The measurement gives the distances between the robot and the four landmarks.
By running the code and plotting the result, one can see visually that the uncertainty decreases after measurements.
