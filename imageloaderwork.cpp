#include "imageloaderwork.h"
#include <QImageReader>

ImageLoaderWork::ImageLoaderWork(QObject *parent)
    : QObject{parent}
{}

void ImageLoaderWork::imageLoad(MyLabel *label,QPixmap *pixmap,QString path,int i,int j,int pictureMaxSizeOverall,int pictureMaxSize)
{
    //控制照片保存尺寸
    // if(path!=""){
    //     pixmap->load(path);
    //     //照片尺寸限制
    //     if(pixmap->width()>pictureMaxSizeOverall || pixmap->height()>pictureMaxSizeOverall){
    //         int w = pixmap->width();
    //         int h = pixmap->height();
    //         modifySize(w,h,pictureMaxSizeOverall);
    //         *pixmap = pixmap->scaled(w,h);
    //     }
    // }
    if(path!=""){
        QImageReader reader(path);
        //照片尺寸限制
        int w = reader.size().width();
        int h = reader.size().height();
        if(w>pictureMaxSizeOverall || h>pictureMaxSizeOverall){
            modifySize(w,h,pictureMaxSizeOverall);
        }
        reader.setScaledSize(QSize(w,h));
        *pixmap = QPixmap::fromImageReader(&reader);
    }

    //控制照片显示尺寸
    int w = pixmap->width();
    int h = pixmap->height();
    if(w>pictureMaxSize || h>pictureMaxSize){
        modifySize(w,h,pictureMaxSize);
    }
    QPixmap pixmap_temp = pixmap->scaled(QSize(w,h));

    label->setPixmap(pixmap_temp);

    emit loadSP_signal(i, j, label, this);
}

void ImageLoaderWork::modifySize(int &w, int &h, int maxSize)
{
    if(w>h){
        double ratio = maxSize*1.0/w;
        w = maxSize;
        h = ratio*h;
    }
    else{
        double ratio = maxSize*1.0/h;
        h = maxSize;
        w = ratio*w;
    }
}

