#!/bin/bash

sudo chmod 666 /dev/ttyUSB0

cd ~/catkin_ws

source devel/setup.bash

roslaunch rplidar_ros rplidar.launch &

sleep 3

gnome-terminal --

cd ~/catkin_ws

roslaunch hector_slam_launch tutorial.launch
