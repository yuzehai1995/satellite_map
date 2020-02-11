//
// Created by fish on 19-12-18.
//

#ifndef MAP_ED_QT_SMAPEDITOR_H
#define MAP_ED_QT_SMAPEDITOR_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include <config.h>
#include <calculate.h>
using namespace std;
using namespace cv;



class SMapEditor {
public:
    SMapEditor();
    void init(string& s_img);
    void editMap();

    cv::Mat satelliteMap_;
    static double lat_ , lng_  , dim_;
    static int map_row_;
//
//    cv::Mat src_map = cv::imread("/home/fish/perception_code/0/satellite_map/satellite/src.bmp");
//    //cv::Mat lane_map(src_map.rows,src_map.cols,CV_8UC3);
//    int point_num = 1;
//    cv::Point2i firs_point;
//    cv::Point2i second_point;
private:
    void loadImg(string& );

};


#endif //MAP_ED_QT_SMAPEDITOR_H
