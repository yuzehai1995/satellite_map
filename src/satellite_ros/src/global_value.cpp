//
// Created by fish on 19-12-22.
//

#include "global_value.h"
using namespace std;
double Value::LAT =0;
double Value::LNG=0 ;
double Value::DIM=0 ;
int Value::MAP_ROW=0;
int Value::MAP_COL=0;
int Value::EDIT_STATUS = 0;

bool Value::REAL_TIME  = false;
cv::Mat Value::MAP ;


double Value::CUR_LAT=0 ;
double Value::CUR_LNG=0 ;


shared_ptr<Value> Value::value_ = nullptr;

void Value::initialize(){
    if ( value_ == nullptr )
        value_ = shared_ptr<Value>(new Value);

}

Value::~Value()
{

}

