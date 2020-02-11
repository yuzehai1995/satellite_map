//
// Created by fish on 19-12-22.
//

#ifndef MAP_ED_QT_GLOBAL_VALUE_H
#define MAP_ED_QT_GLOBAL_VALUE_H

#include <iostream>
#include <memory>
#include <vector>
#include <opencv2/core/core.hpp>

/**************************************************
 * @name :  单例模式的类Value
 * @brief:  用于存储随时调用的静态变量
***************************************************/
class Value{

private:
    static std::shared_ptr<Value> value_;

    Value () {} // private constructor makes a singleton
public:
    ~Value();  // close the file when deconstructing

    // set a new config file
    static void initialize(  );

    static bool REAL_TIME;           //是否实时显示车辆位置
    static cv::Mat MAP;              //拓扑地图图像

    static double LAT , LNG , DIM ;  //地图原点坐标与尺度(m/pix)
    static int    MAP_ROW,MAP_COL;   //卫星图像的尺寸

    static int    EDIT_STATUS;       //地图编辑模式标志位
                                     // 1 for add road ;
                                     // 2 for delete road;
                                     // 3 for spilt road;
    static double CUR_LAT ;          //车辆当前的GPS坐标
    static double CUR_LNG ;

};






#endif //MAP_ED_QT_GLOBAL_VALUE_H
