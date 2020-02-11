//
// Created by fish on 19-12-24.
//

#include <gps_node.h>
#include "my_thread.h"
#include <QDebug>
#include "global_value.h"
myThread::myThread()
{

}

myThread::myThread(ros::NodeHandle& n) : node_(n)
{

    //GpsNode gpsNode_(n);

    cmd_ = node_.subscribe("turtle1/cmd_vel", 10,
                           &myThread::processCmd, this);
}




void myThread::run()
{

    /**************************************************
     * @brief:  if(Value::REAL_TIME)
     *          执行一种线程程序 thread2 车辆位置更新
    ***************************************************/
    if(Value::REAL_TIME){
        trajectory_.clear();
        cout << "thread 2 ok" <<endl;

        ros::Rate    r(5);  //===========设定车辆位置刷新频率============//
        cv::Mat      map ;

        cv::namedWindow("1");
        while(Value::REAL_TIME ){

            //cout << Value::CUR_LAT<<","<< Value::CUR_LNG<<endl;
            Value::MAP.copyTo(map);

            double x = 0 , y =0 ;
            gps2plane(x, y ,Value::LAT , Value::LNG , Value::CUR_LAT ,Value::CUR_LNG);

            x   =   x / Value::DIM ;
            y   =   Value::MAP_ROW - y/Value::DIM;
            //cout << x<<","<< y<<endl;


            if( x > 0 && y > 0){
                cv::Point2i p( x , y );
                cv::circle( map,p,5,cv::Scalar(255,255,255),2 );

                if(trajectory_.size() > 199){
                    trajectory_.erase(trajectory_.begin());
                }
                trajectory_.emplace_back( cv::Point2i(x,y) );
             }

            for(auto it = trajectory_.cbegin() ; it != trajectory_.cend() ; it++){
                cv::Point2i p( it->x , it->y );
                cv::circle(map,p,1,cv::Scalar(0,0,255),1);

            }

            //cout << "trajectory_.size()"<<trajectory_.size()<<endl;
            cv::imshow("1",map);

            r.sleep();
        }
        cv::destroyWindow("1");


    }else{
        /**************************************************
         * @brief:  else
         *          执行另外一种线程程序 thread1 接受GPS信息
        ***************************************************/
        cout << "thread 1 ok" <<endl;
        ros::Rate r(1);
        int i = 0;

        GpsNode gpsNode(node_);

        ros::spin();

    }


}

void myThread::processCmd(const geometry_msgs::Twist &cmd_msg)
{

    cout <<"1"<<endl;
}


/**************************************************
 * @brief:  GPS点转化为平面坐标
***************************************************/
void myThread::gps2plane( double &x, double &y, double lat0 , double lng0 ,double lat , double lng )
{
    double R_ = Config::get<double>("R");
    double PI_= Config::get<double>("PI");
    x = R_*cos(0.5*(lat+lat0)*PI_/180)*PI_/180*(lng - lng0);
    y = R_*(lat - lat0)*PI_/180;

}

