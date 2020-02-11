#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ros/ros.h>
#include "ui_mainwindow.hpp"
#include "subwidget.hpp"
#include <QPushButton>
#include <QDebug> //打印
#include <QMessageBox>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QPainter>
#include <QBrush>
#include <QString>
#include <QTextEdit>
#include <QDockWidget>
#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <vector>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <QAction>
#include <opencv2/imgproc.hpp>
#include <QMenu>
#include <QMenuBar>
#include "stdlib.h"
#include <stdio.h>
#include "config.h"
#include "sMapEditor.h"
#include "my_graphics_view.h"
#include "topo_map.h"
#include "my_thread.h"
namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TopoMap *topoMap;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int n_ = 1;

    void paintEvent(QPaintEvent *event);

    void zoomPixmap();

    //MapLabel* mapLabel_;
    //QLabel* mapLabel_1;
    SMapEditor sMap_editor_;
    //MyGraphicsView* myGraphicsView_;

public slots:
    void mySlot();
    void changeWin();
    void btn_clicked();
/**************************************************
 * @name: MainWindow::OnFileOpen()
 * @brief: ui->open回调函数，加载原始图像文件
 *         并在ui->label_src_img中显示
 * @操作对象: my_src_img_
***************************************************/
    void loadSatellite();

    void initCall();
    void openTopoMapCall( );

    void m_addRoad();
    void m_deleteRoad();
    void m_splitRoad();

    void updateMap();
    void saveMap();

    void realtime_run();

private:
    Ui::MainWindow*  ui;

    myThread*        thread2;
    SubWidget        subWin;

    bool             REAL_TIME = false ;
    QDialog          dlg;
//  QMenu*           file_menu;
//  QPushButton*     b2;
//  QPushButton      b3;

};

#endif // MAINWINDOW_H
