//
// Created by fish on 19-12-20.
//

#ifndef MAP_ED_QT_MY_GRAPHICS_VIEW_H
#define MAP_ED_QT_MY_GRAPHICS_VIEW_H

#ifndef GLOBALPLANNING_MYGRAPHICSVIEW_H
#define GLOBALPLANNING_MYGRAPHICSVIEW_H
#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QColor>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QPicture>
#include <QImage>
#include <QPixmap>
#include <QRect>
#include <QGraphicsPixmapItem>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
QT_BEGIN_NAMESPACE
class QWheelEvent;
QT_END_NAMESPACE

class MyGraphicsView : public QGraphicsView
{
Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent = 0);
    ~MyGraphicsView();


    void show();


    void DrawChoiceWay();


    cv::Mat image_;
    cv::Mat image_show_;
    double scale_ = 90000;
    bool start_ = false;
    bool end_ = false;
//    bool finish_line_ = false;
    cv::Point2i startPoint_;
    cv::Point2i endPoint_;

private:



    void ShowImage(cv::Mat image1);


    void ConstructQtMap();

    void find_nearest_line( const cv::Point2i pt,  const int& sub_num );

    QImage qimage_;
    double edge_width_ = 60;
    QGraphicsScene *scene;
    bool mouse_translate_flag_;
    QPoint last_mouse_pos_;  // 鼠标最后按下的位置

protected:

    void mousePressEvent(QMouseEvent *event);

    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};


#endif //GLOBALPLANNING_MYGRAPHICSVIEW_H


#endif //MAP_ED_QT_MY_GRAPHICS_VIEW_H
