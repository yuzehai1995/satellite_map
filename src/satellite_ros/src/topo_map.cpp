//
// Created by fish on 19-12-22.
//
#include <topo_map.h>

using namespace std;
using namespace cv;

Line TopoMap::new_line_; //静态变量定义
cv::Point2i TopoMap::delete_point_;
cv::Point2i TopoMap::split_point_;


bool TopoMap::add_line_ = false;
bool TopoMap::delete_line_ = false;
bool TopoMap::split_line_ = false;

TopoMap::TopoMap(const string& txt, const cv::Mat & img,
        const double& origin_lat , const double& origin_lng ,
        const double& dim , const int& row)
                :text_string_(txt),origin_lat_(origin_lat)  ,
                 origin_lng_(origin_lng) , dim_(dim) , row_(row){

    img.copyTo(topoImg_);
    img.copyTo(origin_img_);




}

void TopoMap::loadLine() {

    ifstream   infile(text_string_);
    if(! infile.is_open()){
        cout <<"file open failed"<<endl;
    }

    string            buffer;
    stringstream      ss;  //string stream
    Line              temp_line;
    Calculate         calc;


    while(getline(infile,buffer))
    {
        ss.clear();
        ss.str(buffer);
        ss >>temp_line.line_num>> temp_line.uB >> temp_line.vB >> temp_line.uE >> temp_line.vE;

        temp_line.xB = temp_line.uB * dim_;
        temp_line.yB = (row_ - temp_line.vB) * dim_;
        temp_line.xE = temp_line.uE * dim_;
        temp_line.yE = (row_ - temp_line.vE) * dim_;

        calc.pix2gps(temp_line.uB,temp_line.vB,origin_lat_,origin_lng_,
                     temp_line.latB,temp_line.lngB  , row_ , dim_);
        calc.pix2gps(temp_line.uE,temp_line.vE,origin_lat_,origin_lng_,
                     temp_line.latE,temp_line.lngE  , row_ , dim_);
        lines.push_back(temp_line);

        cout << temp_line.uB<<" "<< temp_line.vB <<" "<< temp_line.xB<<" "<<" "<< temp_line.yB<<" "<<
             temp_line.latB<< " "<< temp_line.lngB<<endl;

    }
    cout<<lines.size()<< " lines loaded"<<endl;


}

void TopoMap::getMap(cv::Mat& returnMap) {
    cv::Point2i p1 , p2;
    origin_img_.copyTo(topoImg_);

    for(auto it = lines.cbegin() ; it != lines.cend() ; it++){

        p1.x = it -> uB ; p1.y = it->vB;
        p2.x = it -> uE ; p2.y = it->vE;
        cv::circle(topoImg_,p1,2,cv::Scalar(0,255,0),2);
        cv::circle(topoImg_,p2,3,cv::Scalar(255,0,0),2);

        cv::line(topoImg_, p1, p2, cv::Scalar(255,255,0) ,2);
    }

    topoImg_.copyTo(Value::MAP);
    topoImg_.copyTo(returnMap);


}

void TopoMap::showDeleteLine(const int num){
    cv::Point2i pt1( lines[num].uB, lines[num].vB );
    cv::Point2i pt2( lines[num].uE, lines[num].vE );
    cv::line(topoImg_,pt1,pt2,cv::Scalar(255,0,0),2);

}

void TopoMap::getMap() {


}


void TopoMap::addRoad(){

    if(add_line_){
        Line              temp_line;

        temp_line.line_num = rand()%100;
        temp_line.uB = new_line_.uB;  temp_line.vB = new_line_.vB;
        temp_line.uE = new_line_.uE;  temp_line.vE = new_line_.vE;

        calc_line_para(temp_line);

        lines.push_back(temp_line);

        cout << "new line added :"<<endl;
        cout << temp_line.uB<<" "<< temp_line.vB <<" "<< temp_line.xB<<" "<<" "<< temp_line.yB<<" "<<
             temp_line.latB<< " "<< temp_line.lngB<<endl;
        add_line_ = false;
    }


}

void TopoMap::deleteRoad(){
    if(delete_line_) {

        int subNum = 0;

        find_nearest_line(delete_point_, subNum);
        cout << "subNun"<<subNum<<endl;
        lines.erase(lines.begin() + subNum);

        delete_line_ = false;
    }
}

void TopoMap::splitRoad(){
    if(split_line_) {


        int subNum = 0;

        find_nearest_line(split_point_, subNum);

        Line line1;
        Line line2;

        line1.line_num = rand()%100;
        line1.uB = lines[subNum].uB;    line1.vB = lines[subNum].vB;
        line1.uE = split_point_.x;         line1.vE = split_point_.y;
        calc_line_para(line1);

        line2.line_num = rand()%100;
        line2.uB = split_point_.x;         line2.vB = split_point_.y;
        line2.uE = lines[subNum].uE;    line2.vE = lines[subNum].vE;
        calc_line_para(line2);

        lines.erase(lines.begin() + subNum);
        lines.push_back(line1);
        lines.push_back(line2);

        split_line_ = false;
    }


}



void TopoMap::saveMap(){
    string txtFile= Config::get<string >("newTxtFile");
    ofstream outfile_(txtFile);
    for(auto it = lines.cbegin() ; it != lines.cend() ; it++){

        outfile_<< it->line_num <<" "<<it->uB << " " << it->vB << " " << it->uE << " " << it->vE <<endl;
    }


}

void TopoMap::find_nearest_point(const cv::Point2i pt, cv::Point2i& new_point ,const Line line){
    float dx = line.uE - line.uB;
    float dy = line.vE - line.vB;
    float ds = sqrtf( dx*dx + dy*dy );

    float x = 0 , y = 0;
    float p2p = 0 ;
    float min_dis = 100000;

    int i_num;

    for(int i = 0 ; i < ds ; i++){
        x = i*dx/ds;
        y = i*dy/ds;
        p2p = sqrtf( (x-pt.x)*(x-pt.x) +(y-pt.y)*(y-pt.y)   );
        if(min_dis > p2p){
            min_dis = p2p;
            i_num = i;

        }
    }

    new_point.x = i_num*dx/ds;
    new_point.y = i_num*dy/ds;


}


void TopoMap::find_nearest_line( const cv::Point2i pt,  int& sub_num ){

    float point[2] = {   static_cast<float>(pt.x ),  static_cast<float>(pt.y) };
    float min_dis = 10000;
    sub_num = 0;
    for(auto it = lines.cbegin() ; it != lines.cend() ; it++){

        float p1[2] = { static_cast<float>(it->uB) , static_cast<float>(it->vB) };
        float p2[2] = {static_cast<float>(it->uE) , static_cast<float>(it->vE) };
        float dis = 0.001;

        float dx = p2[0] - p1[0];
        float dy = p2[1] - p1[1];

        // 两直线垂直，向量表示法，转换后公示
        float k = -((p1[0] - point[0])*dx + (p1[1] - point[1])*dy) / ( dx*dx + dy*dy);
        float footX = k*dx + p1[0];
        float footY = k*dy + p1[1];

        //if垂足是否落在线段上
        if( footY >= min(p1[1], p2[1]) && footY <=max(p1[1], p2[1])
            && footX >= min(p1[0], p2[0]) && footX <=max(p1[0], p2[0] ) )
        {
            dis = sqrtf((footX-point[0])*(footX-point[0]) + (footY-point[1])*(footY-point[1]));
        }
        else
        {
            float dis1 = sqrtf((p1[0]-point[0])*(p1[0]-point[0]) + (p1[1]-point[1])*(p1[1]-point[1]));
            float dis2 = sqrtf((p2[0]-point[0])*(p2[0]-point[0]) + (p2[1]-point[1])*(p2[1]-point[1]));

            dis = ( dis1 < dis2 ? dis1 : dis2 );
        }

        if(dis < min_dis){
            min_dis = dis;
            sub_num = it - lines.begin();

        }
    }


}

void TopoMap::calc_line_para(Line& temp_line){

    temp_line.xB = temp_line.uB * dim_;
    temp_line.yB = (row_ - temp_line.vB) * dim_;
    temp_line.xE = temp_line.uE * dim_;
    temp_line.yE = (row_ - temp_line.vE) * dim_;

    Calculate         calc;

    calc.pix2gps(temp_line.uB,temp_line.vB,origin_lat_,origin_lng_,
                 temp_line.latB,temp_line.lngB  , row_ , dim_);
    calc.pix2gps(temp_line.uE,temp_line.vE,origin_lat_,origin_lng_,
                 temp_line.latE,temp_line.lngE  , row_ , dim_);
}


