//
// Created by fish on 19-12-24.
//

#include "gps_node.h"
using namespace std;
//using namespace cv;

GpsNode::GpsNode( ros::NodeHandle& node ){

    gps_sub_ = node.subscribe("gpsimu", 10, &GpsNode::processGPS, this);
    cmd_ = node.subscribe("turtle1/cmd_vel", 10,
                          &GpsNode::processCmd, this);

}
GpsNode::~GpsNode(){


}

/**************************************************
 * @name: processGPS
 * @brief:  gps 回调函数
***************************************************/
void GpsNode::processGPS(GpsImu7661::ivsensorgps gps_imu){
    {
        GPS gpstem;
        gpstem.x=gps_imu.lat;
        gpstem.y=gps_imu.lon;

        //cout << gpstem.y <<endl;

        gpstem.gpstime=gps_imu.header.stamp.sec + 1e-9*gps_imu.header.stamp.nsec;
        //ROS_INFO("000000:%f", gpstem.gpstime);
        gpstem.gpsspeed=gps_imu.velocity;
        gpstem.gpsdirect=gps_imu.heading;
        gpstem.pitch=gps_imu.pitch;
        gpstem.roll=gps_imu.roll;
        gpstem.yaw=gps_imu.yaw;
        gps_vector.push_back(gpstem);
        if(gps_vector.size()>100)  //已改
        {
            vector<GPS>::iterator k = gps_vector.begin();
            gps_vector.erase(k);
        }
        ///////////////////////
        Value::CUR_LAT = gps_imu.lat;
        Value::CUR_LNG = gps_imu.lon;
        //////////////////////
    }
}

void GpsNode::processCmd(const geometry_msgs::Twist &cmd_msg)
{

    cout <<"666"<<endl;
}