/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "my_graphics_view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open;
    QAction *action22222;
    QWidget *centralwidget;
    QGroupBox *groupBox;
    MyGraphicsView *graphicsView;
    QGroupBox *groupBox_2;
    QPushButton *init;
    QPushButton *openTopoMap;
    QGroupBox *groupBox_3;
    QPushButton *addRoad;
    QPushButton *deleteRoad;
    QPushButton *splitRoad;
    QPushButton *updateMap;
    QGroupBox *groupBox_4;
    QPushButton *saveMap;
    QGroupBox *groupBox_5;
    QPushButton *loadSatelliteImg;
    QLabel *dim;
    QLabel *src_lat;
    QLabel *src_lng;
    QGroupBox *groupBox_6;
    QPushButton *run;
    QPushButton *stop;
    QGroupBox *groupBox_7;
    QPushButton *bt_plan;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menussss;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1011, 777);
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QStringLiteral("action_open"));
        action22222 = new QAction(MainWindow);
        action22222->setObjectName(QStringLiteral("action22222"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(180, 70, 651, 501));
        graphicsView = new MyGraphicsView(groupBox);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setGeometry(QRect(0, 20, 651, 481));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 170, 120, 121));
        init = new QPushButton(groupBox_2);
        init->setObjectName(QStringLiteral("init"));
        init->setGeometry(QRect(20, 40, 89, 25));
        openTopoMap = new QPushButton(groupBox_2);
        openTopoMap->setObjectName(QStringLiteral("openTopoMap"));
        openTopoMap->setGeometry(QRect(20, 70, 91, 25));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 300, 120, 181));
        addRoad = new QPushButton(groupBox_3);
        addRoad->setObjectName(QStringLiteral("addRoad"));
        addRoad->setGeometry(QRect(10, 40, 89, 25));
        deleteRoad = new QPushButton(groupBox_3);
        deleteRoad->setObjectName(QStringLiteral("deleteRoad"));
        deleteRoad->setGeometry(QRect(10, 70, 89, 25));
        splitRoad = new QPushButton(groupBox_3);
        splitRoad->setObjectName(QStringLiteral("splitRoad"));
        splitRoad->setGeometry(QRect(10, 100, 91, 25));
        updateMap = new QPushButton(groupBox_3);
        updateMap->setObjectName(QStringLiteral("updateMap"));
        updateMap->setGeometry(QRect(10, 140, 89, 25));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 490, 121, 80));
        saveMap = new QPushButton(groupBox_4);
        saveMap->setObjectName(QStringLiteral("saveMap"));
        saveMap->setGeometry(QRect(10, 30, 89, 25));
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 70, 120, 80));
        loadSatelliteImg = new QPushButton(groupBox_5);
        loadSatelliteImg->setObjectName(QStringLiteral("loadSatelliteImg"));
        loadSatelliteImg->setGeometry(QRect(20, 40, 71, 25));
        dim = new QLabel(centralwidget);
        dim->setObjectName(QStringLiteral("dim"));
        dim->setGeometry(QRect(200, 30, 101, 21));
        src_lat = new QLabel(centralwidget);
        src_lat->setObjectName(QStringLiteral("src_lat"));
        src_lat->setGeometry(QRect(340, 30, 171, 21));
        src_lng = new QLabel(centralwidget);
        src_lng->setObjectName(QStringLiteral("src_lng"));
        src_lng->setGeometry(QRect(540, 30, 151, 21));
        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(20, 580, 120, 91));
        run = new QPushButton(groupBox_6);
        run->setObjectName(QStringLiteral("run"));
        run->setGeometry(QRect(30, 30, 51, 25));
        stop = new QPushButton(groupBox_6);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setGeometry(QRect(30, 60, 51, 25));
        groupBox_7 = new QGroupBox(centralwidget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(870, 60, 120, 141));
        bt_plan = new QPushButton(groupBox_7);
        bt_plan->setObjectName(QStringLiteral("bt_plan"));
        bt_plan->setGeometry(QRect(10, 30, 101, 25));
        pushButton = new QPushButton(groupBox_7);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 60, 89, 25));
        pushButton_2 = new QPushButton(groupBox_7);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 110, 89, 25));
        MainWindow->setCentralWidget(centralwidget);
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        groupBox_4->raise();
        groupBox_5->raise();
        dim->raise();
        src_lat->raise();
        src_lng->raise();
        groupBox_6->raise();
        groupBox_7->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1011, 28));
        menussss = new QMenu(menubar);
        menussss->setObjectName(QStringLiteral("menussss"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menussss->menuAction());
        menussss->addAction(action_open);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_open->setText(QApplication::translate("MainWindow", "open", 0));
        action22222->setText(QApplication::translate("MainWindow", "22222", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "TMap", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "            \345\210\235\345\247\213\345\214\226  ", 0));
        init->setText(QApplication::translate("MainWindow", "init", 0));
        openTopoMap->setText(QApplication::translate("MainWindow", "openMap", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "     \345\234\260\345\233\276\347\274\226\350\276\221\345\231\250 ", 0));
        addRoad->setText(QApplication::translate("MainWindow", "addRoad", 0));
        deleteRoad->setText(QApplication::translate("MainWindow", "deleteRoad", 0));
        splitRoad->setText(QApplication::translate("MainWindow", "splitRoad", 0));
        updateMap->setText(QApplication::translate("MainWindow", "updateMap", 0));
        updateMap->setShortcut(QApplication::translate("MainWindow", "Ctrl+5", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "     \344\277\235\345\255\230\346\226\260\345\234\260\345\233\276 ", 0));
        saveMap->setText(QApplication::translate("MainWindow", "saveMap", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "    \345\215\253\346\230\237\345\233\276\345\203\217\347\274\226\350\276\221", 0));
        loadSatelliteImg->setText(QApplication::translate("MainWindow", "edit", 0));
        dim->setText(QApplication::translate("MainWindow", "Dim:", 0));
        src_lat->setText(QApplication::translate("MainWindow", "Lat:", 0));
        src_lng->setText(QApplication::translate("MainWindow", "Lng:", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "       \350\275\246\350\276\206\346\230\276\347\244\272  ", 0));
        run->setText(QApplication::translate("MainWindow", "run", 0));
        stop->setText(QApplication::translate("MainWindow", "stop", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "             \350\247\204\345\210\222   ", 0));
        bt_plan->setText(QApplication::translate("MainWindow", "\350\247\204\345\210\222\346\250\241\345\274\217", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\351\200\211\347\202\271", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "start", 0));
        menussss->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
