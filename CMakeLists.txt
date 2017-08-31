cmake_minimum_required(VERSION 3.8)
project(Robot)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Robot.cpp Robot.h Landmark.cpp Landmark.h random.cpp parameter.h ParticleFilter.cpp ParticleFilter.h)
add_executable(Robot ${SOURCE_FILES})