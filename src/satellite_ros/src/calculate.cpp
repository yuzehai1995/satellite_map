//
// Created by fish on 19-12-7.
//
#include "calculate.h"
#include "sMapEditor.h"
Calculate::Calculate()
{
    R_ = Config::get<double>("R");
    PI_= Config::get<double>("PI");
}

void Calculate::get_dim( const Mark_point &p1 , const Mark_point &p2 ){

    double delta_y = ( p1.lat - p2.lat ) * R_ * PI_ / 180;
    delta_y = abs(delta_y);
    double delta_v = p2.v - p1.v ;
    delta_v = abs(delta_v);
    double dim1 = delta_y / delta_v ;

    double delta_x = R_ * cos( 0.5*(p1.lat + p2.lat)*PI_/180 ) * (p1.lng - p2.lng) * PI_ /180;
    delta_x = abs(delta_x);
    double delta_u = p1.u - p2.u;
    delta_u = abs(delta_u);
    double dim2 = delta_x / delta_u ;


    dim_ = dim1 * delta_y/(delta_y+delta_x) + dim2 * delta_x/(delta_y+delta_x);
    SMapEditor::dim_ = dim_;
    Value::DIM = dim_;
    cout<<setprecision(10) << "dim1:"<<dim1 <<",dim2:"<<dim2<<",dim:"<<dim_<<endl;

}

void Calculate::calc_origin(const Mark_point &p1 , const Mark_point &p2 ,const int &map_row){
    map_row_ = map_row;
    SMapEditor::map_row_ = map_row_;
    get_dim(p1 , p2 );

    //y1 - y0 = R * (lat1 - lat0) * PI /180
    //x1 - x0 = R*cos(0.5*(lat1+lat0)*PI/180)*(lng1-lng0)*PI/180
    origin_lat_ = p1.lat - (map_row - p1.v )*180/PI_/R_ ;
    origin_lng_ = p1.lng - (p1.u - 0) /R_/cos(0.5*(p1.lat+origin_lat_)*PI_/180)*180/PI_;

    cout <<setprecision(12)<< "origin_lat_:"<<origin_lat_ <<",origin_lng_:"<<origin_lng_<<endl;

    SMapEditor::lat_ = origin_lat_;
    SMapEditor::lng_ = origin_lng_;

    Value::LAT = origin_lat_;
    Value::LNG = origin_lng_;


}

void Calculate::pix2gps( double u, double v, double &lat , double &lng)
{
    double x = dim_ * u;
    double y = dim_ * (map_row_ - v);
    lat = y*180/R_/PI_ + origin_lat_;
    lng = x*180/R_/PI_/cos(0.5*(lat+origin_lat_)*PI_/180) + origin_lng_;

}
void Calculate::pix2gps( double u, double v,  double origin_lat,double origin_lng,
                         double &lat , double &lng ,int map_row ,double dim){
    double x = dim * u;
    double y = dim * (map_row - v);
    lat = y*180/R_/PI_ + origin_lat;
    lng = x*180/R_/PI_/cos(0.5*(lat+origin_lat)*PI_/180) + origin_lng;

}

void Calculate::plane2gps( double x, double y, double &lat , double &lng)
{
    lat = y*180/R_/PI_ + origin_lat_;
    lng = x*180/R_/PI_/cos(0.5*(lat+origin_lat_)*PI_/180) + origin_lng_;

}



void Calculate::gps2plane( double &x, double &y, double lat0 , double lng0 ,double lat , double lng )
{
    x = R_*cos(0.5*(lat+lat0)*PI_/180)*PI_/180*(lng - lng0);
    y = R_*(lat - lat0)*PI_/180;

}