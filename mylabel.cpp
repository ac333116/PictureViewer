#include "mylabel.h"

MyLabel::MyLabel(QString path,QWidget *parent):QLabel(parent) {
    this->path = path;

}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    if(lvd==nullptr)//保证一个label最多创建一个窗口
        lvd = new LargerViewDialog(path,this);
    lvd->show();
}
