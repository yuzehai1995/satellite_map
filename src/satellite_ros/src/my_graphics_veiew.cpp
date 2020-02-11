//
// Created by fish on 19-12-20.
//

#include "my_graphics_view.h"
#include "topo_map.h"
#include <QWheelEvent>
#include <QPoint>
#include <QDebug>
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()
using namespace std;
using namespace cv;

MyGraphicsView::MyGraphicsView(QWidget *parent)
        : QGraphicsView(parent)
{
    scene = new QGraphicsScene;
}

MyGraphicsView::~MyGraphicsView()
{
    delete scene;

}


void MyGraphicsView::ShowImage(cv::Mat image1){

    qimage_ = QImage((unsigned char*)image1.data, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
    scene->addPixmap(QPixmap::fromImage(qimage_));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);
}


void MyGraphicsView::show()
{

    ShowImage(image_show_);
}


void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem();
        QPointF map_pos= pixmapItem->mapFromScene(mapToScene(event->pos()));

        std::cout << map_pos.x() <<" "<<map_pos.y()<<endl;



        //cout<<"zuobiao:"<<map_pos.x()<<","<<map_pos.y()<<endl;
        mouse_translate_flag_ = true;
        last_mouse_pos_ = event->pos();


        //******************************************************************//
        //*********   Value::EDIT_STATUS == 1  即添加road模式   *************//
        //******************************************************************//
        if(start_ && Value::EDIT_STATUS == 1)//选择起点
        {
            startPoint_.x = map_pos.x();
            startPoint_.y = map_pos.y();

            cv::circle(image_show_,startPoint_,6,cv::Scalar(0,255,0),2);

            TopoMap::new_line_.uB = startPoint_.x;
            TopoMap::new_line_.vB = startPoint_.y;

            start_ = false;
            end_  = true;
            ShowImage(image_show_);
        }
        else if(end_ && !start_ && Value::EDIT_STATUS == 1)//选择终点
        {

            endPoint_.x = map_pos.x();
            endPoint_.y = map_pos.y();

            cv::circle(image_show_,endPoint_,3,cv::Scalar(255,0,0),2);

            end_ = false;
            start_= true;

            TopoMap::new_line_.uE = endPoint_.x;
            TopoMap::new_line_.vE = endPoint_.y;

            TopoMap::add_line_ = true;
            ShowImage(image_show_);
        }


        //******************************************************************//
        //*********   Value::EDIT_STATUS == 2  即删除road模式   *************//
        //******************************************************************//
        else if(Value::EDIT_STATUS == 2)
        {


            TopoMap::delete_point_.x = map_pos.x();
            TopoMap::delete_point_.y = map_pos.y();

            TopoMap::delete_line_ = true;
            cv::circle(image_show_,TopoMap::delete_point_,8,cv::Scalar(255,0,0),3);
            ShowImage(image_show_);

        }

            //******************************************************************//
            //*********   Value::EDIT_STATUS == 3  即断开road模式   *************//
            //******************************************************************//
        else if(Value::EDIT_STATUS == 3)
        {

            TopoMap::split_point_.x = map_pos.x();
            TopoMap::split_point_.y = map_pos.y();

            TopoMap::split_line_ = true;
            cv::circle(image_show_,TopoMap::split_point_,8,cv::Scalar(255,0,0),3);
            ShowImage(image_show_);



        }


        delete pixmapItem;
    }
}







void MyGraphicsView:: mouseDoubleClickEvent(QMouseEvent *event)
{

}
void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    int wheelDeltaValue = event->delta();
    // 向上滚动，放大;
    if (wheelDeltaValue > 0)
    {
        this->scale(1.2, 1.2);
    }else// 向下滚动，缩小;
    {
        this->scale(1.0 / 1.2, 1.0 / 1.2);
    }

}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse_translate_flag_){
        QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(last_mouse_pos_);
        // view 根据鼠标下的点作为锚点来定位 scene
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        QPoint newCenter(VIEW_WIDTH / 2 - mouseDelta.x(),  VIEW_HEIGHT / 2 - mouseDelta.y());
        centerOn(mapToScene(newCenter));
        // scene 在 view 的中心点作为锚点
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    }

    last_mouse_pos_ = event->pos();
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_translate_flag_ = false;
}
