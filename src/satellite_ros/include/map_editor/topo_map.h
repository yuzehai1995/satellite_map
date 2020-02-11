//
// Created by fish on 19-12-22.
//

#ifndef MAP_ED_QT_TOPO_MAP_H
#define MAP_ED_QT_TOPO_MAP_H

#include <iostream>
#include <config.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "calculate.h"

class Line{
public:
    int line_num;
    int uB , vB , uE , vE;
    double xB , yB , xE , yE;
    double lngB , latB , lngE , latE;

};

class TopoMap{
public:
    //TopoMap(){}
    TopoMap(const string& txt, const cv::Mat & ,
            const double& origin_lat , const double& origin_lng ,
            const double& dim , const int& row) ;
    void loadLine();
    void getMap(cv::Mat& returnMap);
    void getMap();

    void addRoad();
    void deleteRoad();
    void splitRoad();

    void saveMap();


    cv::Mat topoImg_;

    std::vector<Line> lines;

    static Line new_line_;
    static cv::Point2i delete_point_;
    static cv::Point2i split_point_;
    static bool add_line_;
    static bool delete_line_;
    static bool split_line_;

private:

    void find_nearest_line( const cv::Point2i pt, int& sub_num );
    void find_nearest_point(const cv::Point2i pt, cv::Point2i& new_point ,const Line line);

    void calc_line_para(Line& line);

    string text_string_;
    cv::Mat origin_img_;
    void showDeleteLine(const int num);


    double origin_lat_ ;
    double origin_lng_ ;
    double dim_;
    int row_;

};

#endif //MAP_ED_QT_TOPO_MAP_H
