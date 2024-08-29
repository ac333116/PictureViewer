#include "mytablewidget.h"


MyTableWidget::MyTableWidget(QWidget *parent):QTableWidget(parent) {}

void MyTableWidget::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        // 如果按下了Ctrl键，不执行默认的滚动行为
        event->ignore();
    }
    else{
        // 如果没有按下Ctrl键，则调用基类的wheelEvent来执行默认的滚动行为
        QTableWidget::wheelEvent(event);
    }
}


