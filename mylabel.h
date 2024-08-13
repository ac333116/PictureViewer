#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "largerviewdialog.h"

class MyLabel : public QLabel
{
    //Q_OBJECT

public:
    MyLabel(QString path,QWidget *parent=nullptr);

    QString path;
private:
    LargerViewDialog *lvd=nullptr;//大图浏览窗口

    void mousePressEvent(QMouseEvent *event);//鼠标点击事件
};

#endif // MYLABEL_H
