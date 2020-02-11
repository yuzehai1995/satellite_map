//
// Created by fish on 19-12-7.
//

#ifndef SATELLITE_MAP_CALCULATE_H
#define SATELLITE_MAP_CALCULATE_H
#include <iostream>
#include <config.h>
#include "global_value.h"
#include <iomanip>

using namespace std;

class Mark_point{
public:
    double lat;
    double lng;
    int u;
    int v;
};

/**************************************************
 * @name: class Calculate
 * @brief:  用于初始化时计算地图原点、尺度等的类
***************************************************/
class Calculate{
public:
    Calculate();
    void calc_origin(const Mark_point &p1 , const Mark_point &p2 , const int &map_row);
    void plane2gps( double x, double y, double &lat , double &lng);
    void gps2plane( double &x, double &y, double lat0 , double lng0 ,double lat , double lng );
    double dim_; //像素坐标与真实坐标尺度关系
    int map_row_;
    void pix2gps( double u, double v, double origin_lat,double origin_lng,
                             double &lat , double &lng ,int map_row,double dim);
    void pix2gps( double x, double y, double &lat , double &lng);

private:
    void get_dim( const Mark_point &p1 , const Mark_point &p2 );

    double R_ ; //地球半径
    double  PI_;
    double origin_lat_ , origin_lng_;
};


#endif //SATELLITE_MAP_CALCULATE_H
