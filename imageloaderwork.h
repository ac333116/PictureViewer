#ifndef IMAGELOADERWORK_H
#define IMAGELOADERWORK_H

#include <QObject>
#include "mylabel.h"

class ImageLoaderWork : public QObject
{
    Q_OBJECT
public:
    explicit ImageLoaderWork(QObject *parent = nullptr);


signals:
    void loadSP_signal(int i, int j, MyLabel *label, ImageLoaderWork *worker);

public:
    void imageLoad(MyLabel *label,QPixmap *pixmap,QString path,int i,int j,int pictureMaxSizeOverall,int pictureMaxSize);

private:
    void modifySize(int &w,int &h,int maxSize);

};

#endif // IMAGELOADERWORK_H
