#include "imageloaderthread.h"


// ImageLoaderThread::ImageLoaderThread(QString path, int i, int j, int pictureMaxSize,QWidget *qw):
//     path(path),i(i),j(j),pictureMaxSize(pictureMaxSize),qw(qw)
// {

// }

ImageLoaderThread::ImageLoaderThread(MyLabel *label,QString path, int i, int j, int pictureMaxSize):
    label(label),path(path),i(i),j(j),pictureMaxSize(pictureMaxSize)
{

}

void ImageLoaderThread::run()
{
    // MyLabel *label = new MyLabel(path,qw);
    // label->setAlignment((Qt::AlignCenter | Qt::AlignVCenter));//设置label中内容为水平和中心对齐
    // label->setMargin(10);//设置图片与label间距

    QPixmap pixmap(path);
    //修改图片尺寸
    int w,h;
    if(pixmap.width()<=pictureMaxSize && pixmap.height()<=pictureMaxSize){
        w=pixmap.width();
        h=pixmap.height();
    }
    else if(pixmap.width()>pixmap.height()){
        w=pictureMaxSize;
        h=pixmap.height()*pictureMaxSize/pixmap.width();
    }
    else{
        h=pictureMaxSize;
        w=pixmap.width()*pictureMaxSize/pixmap.height();
    }
    pixmap = pixmap.scaled(QSize(w,h));

    label->setPixmap(pixmap);

    emit loadSP_signal(i,j,label);
}