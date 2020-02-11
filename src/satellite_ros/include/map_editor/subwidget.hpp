//
// Created by fish on 19-10-22.
//

#ifndef MAP_ED_QT_SUBWIDGET_H
#define MAP_ED_QT_SUBWIDGET_H


#include <QDialog>
#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);

    void sendSlot();

signals:
    /* 信号必须有signals关键字来声明
     * 信号没有返回值，但可以有参数
     * 信号就是函数的声明，只需声明，无需定义
     * 使用：emit mySignal();
     * 信号可以重载
    */

    void mySignal();
    void mySignal(int, QString);

public slots:

private:
    QPushButton b;

};


#endif //MAP_ED_QT_SUBWIDGET_H
