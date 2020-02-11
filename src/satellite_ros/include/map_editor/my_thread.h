//
// Created by fish on 19-12-24.
//

#ifndef MAP_ED_QT_MY_THREAD_H
#define MAP_ED_QT_MY_THREAD_H



#include <QThread>
#include "gps_node.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include "mainwindow.hpp"
class myThread: public QThread
{
public:

    myThread(ros::NodeHandle& n);
    myThread();

    void run(); //声明继承于QThread虚函数 run()

private:

    ros::Subscriber cmd_;
    void processCmd(const geometry_msgs::Twist &cmd_msg);
    ros::NodeHandle node_;
    void gps2plane( double &x, double &y, double lat0 , double lng0 ,double lat , double lng );
    vector<cv::Point2i> trajectory_;

};

#endif //MAP_ED_QT_MY_THREAD_H
