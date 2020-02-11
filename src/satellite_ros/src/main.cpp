#include <ros/ros.h>


#include <iostream>
#include "mainwindow.hpp"
#include "ui_mainwindow.hpp"
#include <QApplication>
#include <qtextcodec.h>
#include "config.h"
#include "global_value.h"
#include "gps_node.h"
#include "my_thread.h"   //包涵头文件
#include <iostream>
#include <QDebug>
#include <QFile>
using namespace std;
using namespace cv;

int main(  int argc, char *argv[] )
{

    QApplication  a(argc, argv);

    Config::setParameterFile ( "/home/fish/0my_catkin/ws_satellite/src/satellite_ros/para.yaml");
    Value::initialize();


    cout << "Hello World!" << endl;


    ros::init(argc, argv, "map_ed_qt");
    ros::NodeHandle nh;

    /**************************************************
     * @brief:  thread1 用于建立一个GpsNode对象，便于接收GPS信息
    ***************************************************/
    myThread* thread1 = new myThread(nh);
    thread1->start();

    /**************************************************
     * @brief:  建立自定义的主窗口
    ***************************************************/
    MainWindow    w;
    w.show();


    cout << " sure" <<endl;


    return a.exec();
}
