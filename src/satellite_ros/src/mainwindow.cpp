#include "mainwindow.hpp"
#include "ui_mainwindow.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("map_editor");

    thread2 = new myThread;
        //mapLabel_ = new MapLabel(this);
        //myGraphicsView_ = new MyGraphicsView(this);
    //    b2 = new QPushButton(this);
    //    b2->setText("test");
    //    b2->move(500,100);
    //    b2->resize(80,30);
    //    connect(b2, &QPushButton::released, this, &MainWindow::mySlot);

    connect(ui->loadSatelliteImg    ,  &QPushButton::released,
            this                    ,  &MainWindow::loadSatellite  );

    connect(ui->init           ,  &QPushButton::released,
            this               ,  &MainWindow::initCall  );

    connect(ui->openTopoMap    ,  &QPushButton::released,
            this               ,  &MainWindow::openTopoMapCall  );

    connect(ui->addRoad        ,  &QPushButton::released,
            this               ,  &MainWindow::m_addRoad);
    connect(ui->deleteRoad     ,  &QPushButton::released,
            this               ,  &MainWindow::m_deleteRoad);
    connect(ui->splitRoad      ,  &QPushButton::released,
            this               ,  &MainWindow::m_splitRoad);

    connect(ui->updateMap      ,  &QPushButton::released,
            this               ,  &MainWindow::updateMap);

    connect(ui->saveMap        ,  &QPushButton::released,
            this               ,  &MainWindow::saveMap);

    connect(ui->run            ,  &QPushButton::released,
            this               ,  &MainWindow::realtime_run);
    connect(ui->stop           ,  &QPushButton::released, [this](){
                                                                    Value::REAL_TIME = false;
                                                                    this->thread2->quit();
                                                                                               }  );



}

MainWindow::~MainWindow()
{
    delete ui;
    //delete b2;
}





void MainWindow::initCall() {

    std::string s = Config::get<string>("src_map_dir");
    sMap_editor_.init(s);
    std::string str_dim = " dim : " + std::to_string(Value::DIM) ;
    std::string str_lat = " src_lat : " + std::to_string(Value::LAT) ;
    std::string str_lng = " src_lng : " + std::to_string(Value::LNG ) ;

    QString qstr = QString::fromStdString(str_dim);
    ui->dim->setText(qstr);

    qstr = QString::fromStdString(str_lat);
    ui->src_lat ->setText(qstr);

    qstr = QString::fromStdString(str_lng);
    ui->src_lng ->setText(qstr);
}
/**************************************************
 * @name: loadSatellite
 * @brief:  ui->loadSatelliteImg 触发的函数
 *          用于加载和显示原始卫星图像，
 *          并初始化地图编辑器sMap_editor_
***************************************************/
void MainWindow::loadSatellite(){

    QString fileName = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
    std::string s = fileName.toStdString();

    if(s.empty() ){
        s = Config::get<string>("src_map_dir");
    }
    sMap_editor_.init(s);
    sMap_editor_.editMap();


    cv::Mat my_src_img_ = cv::imread(s);
    //myGraphicsView_->ShowImage(my_src_img_);
    my_src_img_.copyTo(ui->graphicsView->image_show_) ;
    ui->graphicsView->show();

    cvtColor(my_src_img_, my_src_img_, CV_BGR2RGB);
    QImage q_image(my_src_img_.data,
                   my_src_img_.cols,
                   my_src_img_.rows,
                   my_src_img_.step,
                   QImage::Format_RGB888);


}

/**************************************************
 * @name: openTopoMapCall
 * @brief:  ui->openTopoMapCall 触发的函数
 *          用于加载并显示txt格式的拓扑地图
***************************************************/
void MainWindow::openTopoMapCall()  {

    QString fileName = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
    std::string s = fileName.toStdString();
    if (s.empty() ){
        s = "/home/fish/0my_catkin/ws_satellite/src/satellite_ros/map.txt" ;
    }
    sMap_editor_.lat_;
    topoMap = new TopoMap(s, sMap_editor_.satelliteMap_,
                             sMap_editor_.lat_         , sMap_editor_.lng_,
                             sMap_editor_.dim_         , sMap_editor_.map_row_);
    topoMap->loadLine();
    cv::Mat returnMap;
    topoMap->getMap(returnMap);
    returnMap.copyTo(ui->graphicsView->image_show_) ;
    ui->graphicsView->show();

}

/**************************************************
 * @name: m_addRoad
 * @brief:  添加道路，将标志位  置1
***************************************************/
void MainWindow::m_addRoad(){

    cout<<"adding road model"<<endl;
    Value::EDIT_STATUS = 1;
    ui->graphicsView->start_ = true ;

}

/**************************************************
 * @name: m_deleteRoad
 * @brief:  删除道路，将标志位  置2
***************************************************/

void MainWindow::m_deleteRoad(){
    cout<<"deleting road model"<<endl;

    Value::EDIT_STATUS = 2;


}


/**************************************************
 * @name: m_splitRoad
 * @brief:  断开道路，将标志位  置3
***************************************************/
void MainWindow::m_splitRoad(){
    cout<<"splitting road model"<<endl;

    Value::EDIT_STATUS = 3;

}


/**************************************************
 * @name: realtime_run
 * @brief:  实时显示当前车辆所在位置
***************************************************/
void MainWindow::realtime_run(){

    Value::REAL_TIME = true;    //ros::Rate r(1);

    thread2->start();

    //    QString qstr;
    //    string s_value = to_string(Value::CUR_LAT );
    //    qstr = QString::fromStdString(s_value);
    //
    //    ui->dim->setText(qstr);

}
/**************************************************
 * @name: saveMap
 * @brief:  将当前拓扑地图保存为txt格式文本
***************************************************/
void MainWindow::saveMap(){

    topoMap->saveMap();
}

/**************************************************
 * @name: updateMap
 * @brief:  刷新当前地图
***************************************************/
void MainWindow::updateMap(){
    if( TopoMap::add_line_ && Value::EDIT_STATUS == 1){

        topoMap->addRoad();

        cv::Mat returnMap;
        topoMap->getMap(returnMap);
        returnMap.copyTo(ui->graphicsView->image_show_) ;
        ui->graphicsView->show();
        Value::EDIT_STATUS = 0;
        cout<<"initial model"<<endl;


    }

    if( TopoMap::delete_line_ && Value::EDIT_STATUS == 2){

        topoMap->deleteRoad();

        topoMap->topoImg_.copyTo(ui->graphicsView->image_show_) ;
        ui->graphicsView->show();

        cv::Mat returnMap;
        topoMap->getMap(returnMap);
        returnMap.copyTo(ui->graphicsView->image_show_) ;
        ui->graphicsView->show();

        Value::EDIT_STATUS = 0;
        cout<<"initial model"<<endl;

    }

    if( TopoMap::split_line_ && Value::EDIT_STATUS == 3){

        topoMap->splitRoad();

        cv::Mat returnMap;
        topoMap->getMap(returnMap);
        returnMap.copyTo(ui->graphicsView->image_show_) ;
        ui->graphicsView->show();

        Value::EDIT_STATUS = 0;
        cout<<"initial model"<<endl;

    }



}

void MainWindow::btn_clicked()
{
//子窗口显示
    subWin.show();
}
void MainWindow::mySlot() {

}

void MainWindow::changeWin(){
//子窗口显示
    subWin.show();
}


void MainWindow::paintEvent(QPaintEvent *event)
{


}
//放大缩小函数
void MainWindow::zoomPixmap()
{

}

////鼠标按键按下事件
//void MainWindow::mousePressEvent(QMouseEvent *ev)
//{
//    //鼠标按下时记录当前按下的坐标
//    if(ev->button() == Qt::LeftButton)
//    {
//        if(ev->x()>rect.x() && ev->x()<rect.x()+rect.width())
//        {
//            if(ev->y()>rect.y() && ev->y()<rect.y()+rect.height())
//            {
//                LastCoordinates = ev->pos();
//            }
//        }
//    }
//}
////鼠标滚轮事件
//void MainWindow::wheelEvent(QWheelEvent *ev)
//{
//
//    //如果滚轮向上滚动就放大尺寸
//    if(ev->delta() > 0)
//    {
//        zoom = 1.1;
//    }
//    else//如果滚轮向下滚动就缩小尺寸
//    {
//        zoom = 0.9;
//    }
//    zoomPixmap();
//    update();
//}
