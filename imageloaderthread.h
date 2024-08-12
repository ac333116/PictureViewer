#ifndef IMAGELOADERTHREAD_H
#define IMAGELOADERTHREAD_H

#include <QThread>
#include "mylabel.h"
#include <QWidget>


class ImageLoaderThread : public QThread
{
    Q_OBJECT

public:
    // ImageLoaderThread(QString path,int i,int j,int pictureMaxSize,QWidget *qw);
    ImageLoaderThread(MyLabel *label,QString path,int i,int j,int pictureMaxSize);

    void run() override ;


signals:
    void loadSP_signal(int i,int j,MyLabel *label);

private:
    MyLabel *label;
    QString path;
    int i;
    int j;
    int pictureMaxSize;
    //QWidget *qw;

};

#endif // IMAGELOADERTHREAD_H
