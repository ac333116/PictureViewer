#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>
#include <QWheelEvent>

class MyTableWidget : public QTableWidget
{
public:
    MyTableWidget(QWidget *parent);


private:
    void wheelEvent(QWheelEvent *event) override;

};

#endif // MYTABLEWIDGET_H
