#include "imageloaderwork.h"

ImageLoaderWork::ImageLoaderWork(QObject *parent)
    : QObject{parent}
{}

void ImageLoaderWork::imageLoad(MyLabel *label,QPixmap *pixmap,QString path,int i,int j,int pictureMaxSizeOverall,int pictureMaxSize)
{
    if(path!=""){
        pixmap->load(path);
        //照片尺寸限制
        if(pixmap->width()>pictureMaxSizeOverall || pixmap->height()>pictureMaxSizeOverall){
            int w = pixmap->width();
            int h = pixmap->height();
            modifySize(w,h,pictureMaxSizeOverall);
            *pixmap = pixmap->scaled(w,h);
        }
    }

    //调整图片尺寸，防止图片过大
    // int w,h;
    // if(pixmap->width()<=pictureMaxSize && pixmap->height()<=pictureMaxSize){
    //     w=pixmap->width();
    //     h=pixmap->height();
    // }
    // else if(pixmap->width()>pixmap->height()){
    //     w=pictureMaxSize;
    //     h=pixmap->height()*pictureMaxSize/pixmap->width();
    // }
    // else{
    //     h=pictureMaxSize;
    //     w=pixmap->width()*pictureMaxSize/pixmap->height();
    // }
    // QPixmap pixmap_temp = pixmap->scaled(QSize(w,h));

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

