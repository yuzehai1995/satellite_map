//
// Created by fish on 19-12-24.
//

#ifndef MAP_ED_QT_GPS_NODE_H
#define MAP_ED_QT_GPS_NODE_H
#include <ros/ros.h>
#include <time.h>
#include <vector>
#include <ivsensorgps.h>
#include <QApplication>
#include <qtextcodec.h>
#include "config.h"
#include "global_value.h"
#include "mainwindow.hpp"
#include <geometry_msgs/Twist.h>

#include <iostream>
class GPS
{
public:
    double x; //纬度 latitude
    double y; //经度 longitude
    double gpstime;
    double gpsspeed;
    double gpsdirect;
    double pitch;
    double roll;
    double yaw;
};

/**************************************************
 * @name: class GpsNode
 * @brief:  用于接收GPS信息的ros节点类
***************************************************/
class GpsNode{
public:
    GpsNode( ros::NodeHandle& node  );
    ~GpsNode();

private:
    ros::Subscriber gps_sub_;
    ros::Subscriber cmd_;

    void processCmd(const geometry_msgs::Twist &cmd_msg);

    void processGPS(GpsImu7661::ivsensorgps gps_imu);
    std::vector<GPS> gps_vector;


};

#endif //MAP_ED_QT_GPS_NODE_H
