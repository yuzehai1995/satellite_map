//
// Created by fish on 19-12-18.
//

#include "sMapEditor.h"
using namespace std;
using namespace cv;

double SMapEditor::lat_ = 0; //定义并初始化静态成员变量
double SMapEditor::lng_ = 0;
double SMapEditor::dim_ = 0;
int    SMapEditor::map_row_ = 0;


cv::Mat src_map;
//cv::Mat lane_map(src_map.rows,src_map.cols,CV_8UC3);
int point_num = 1;
cv::Point2i firs_point;
cv::Point2i second_point;
//string txtFile= "/home/fish/perception_code/0/satellite_map/satellite_ui/map.txt";

int roadNum = 0 ;
bool is_first = true;


//opencv鼠标回调函数
void MouseHandle(int event, int x, int y, int flags, void *param);//鼠标回调函数

SMapEditor::SMapEditor(){

}
void SMapEditor::loadImg(string& s_img){

    if(s_img.empty()){
        src_map = cv::imread( Config::get<string>("src_map_dir") );
        cout <<"read  /home/fish/perception_code/0/satellite_map/satellite_ui/src.png "<<endl;
    }else{
        src_map = cv::imread(s_img);
    }



}

void SMapEditor::init(string& s_img){
    if(s_img.empty()){
        src_map = cv::imread( Config::get<string>("src_map_dir") );
        cout <<"read  /home/fish/perception_code/0/satellite_map/satellite_ui/src.png "<<endl;
    }else{
        src_map = cv::imread(s_img);
    }
    Value::MAP_ROW = src_map.rows;
    Value::MAP_COL = src_map.cols;


    satelliteMap_ = src_map.clone();
    Mark_point p1,p2;
    Calculate calc;

    p1.lat = Config::get<double >("p1_lat");
    p1.lng = Config::get<double >("p1_lng");
    p2.lat = Config::get<double >("p2_lat");
    p2.lng = Config::get<double >("p2_lng");
    p1.u = Config::get<int >("p1_u");
    p1.v = Config::get<int >("p1_v");
    p2.u = Config::get<int >("p2_u");
    p2.v = Config::get<int >("p2_v");

//    string lane_map_dir = Config::get<string>("lane_map_dir");
//    string src_map_dir = Config::get<string>("src_map_dir");
//    cv::Mat lane_map = cv::imread(lane_map_dir,0);

    int map_row = src_map.rows;

    //计算地图的尺度、原点坐标
    calc.calc_origin(p1,p2,map_row);

}

void SMapEditor::editMap(){

    Mark_point p1,p2;
    Calculate Mcalc;

    p1.lat = Config::get<double >("p1_lat");
    p1.lng = Config::get<double >("p1_lng");
    p2.lat = Config::get<double >("p2_lat");
    p2.lng = Config::get<double >("p2_lng");
    p1.u = Config::get<int >("p1_u");
    p1.v = Config::get<int >("p1_v");
    p2.u = Config::get<int >("p2_u");
    p2.v = Config::get<int >("p2_v");

//    string lane_map_dir = Config::get<string>("lane_map_dir");
//    string src_map_dir = Config::get<string>("src_map_dir");
//    cv::Mat lane_map = cv::imread(lane_map_dir,0);

    int map_row = src_map.rows;



    //计算地图的尺度、原点坐标
    Mcalc.calc_origin(p1,p2,map_row);


    cv::namedWindow("src_map",CV_WINDOW_NORMAL);
    //run_callback(calc);


    //将calc对象传入回调函数
    cv::setMouseCallback("src_map", MouseHandle, (void*)&Mcalc);//鼠标操作回调函数
    int key;

    while(key != 27){
        key=cv::waitKey(10);

        cv::imshow("src_map",src_map);

        //cv::waitKey(10);

    }
    //cv::waitKey(0);
    cv::destroyWindow("src_map");


}




void MouseHandle(int event, int u, int v, int flags, void *param)
{

    //Mat& image = *(cv::Mat*) param;

    Calculate &calc = *(Calculate*) param;  //建立对象的引用
    switch (event)
    {
        case EVENT_MOUSEMOVE://鼠标移动
        {

        }
            break;
        case EVENT_LBUTTONDOWN://点击鼠标左键
        {
            string txtFile= Config::get<string >("txtFile");
            ofstream outfile_(txtFile,ios::app);

            if(is_first){
                outfile_ <<roadNum <<" " << u << " " << v <<" ";
            }else{
                outfile_ << u << " " << v <<endl;
                roadNum++;
            }

            is_first = !is_first;



            double lat;
            double lng;
            calc.pix2gps(u,v,lat,lng);



            std::cout << setprecision(5)<< "(x,y):("<<calc.dim_ * u <<","<<calc.dim_ * (calc.map_row_ - v)<<")"<<endl;
            std::cout << setprecision(12)<< "(lat_,lng_):("<<lat <<","<<lng<<")"<<endl;

            if(point_num == 1)
            {
                firs_point.x = u;
                firs_point.y = v;
                cout<<"first point :" << u<<","<<v<<endl;
                string s = to_string(lng) + "," + to_string(lat);
                cv::putText(src_map,s,firs_point,2,0.5,cv::Scalar(0,0,255),1);
                point_num = 2;
            }
            else if(point_num == 2)
            {
                second_point.x = u;
                second_point.y = v;
                cout<<"second point :" << u<<","<<v<<endl;

                cv::line(src_map,firs_point,second_point,cv::Scalar(255,255,0),1);
                string s = to_string(lng) + "," + to_string(lat);
                cv::putText(src_map,s,second_point,2,0.5,cv::Scalar(0,0,255),1);

                point_num = 1;

            }

        }
            break;
        case EVENT_LBUTTONUP://鼠标左键抬起
        {

        }
            break;
    }
}
