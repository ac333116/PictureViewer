#include "largerviewdialog.h"
#include "ui_largerviewdialog.h"

LargerViewDialog::LargerViewDialog(QString path,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LargerViewDialog)
{
    ui->setupUi(this);

    this->path=path;//设置图片路径

    InterfaceInitialization();//界面初始化
    pictureInitialization();//图片初始化

}

LargerViewDialog::~LargerViewDialog()
{
    delete pixmap;
    delete ui;
}

//界面初始化
void LargerViewDialog::InterfaceInitialization()
{
    setWindowTitle("照片阅览");
    ui->label->setAlignment((Qt::AlignCenter | Qt::AlignVCenter));//设置label中内容为水平和中心对齐
    //ui->label->setMargin(10);//设置label间距
}

//图片初始化
void LargerViewDialog::pictureInitialization()
{
    pixmap->load(path);//加载图片路径

    //调整照片初始长宽
    int w = pixmap->width();
    int h = pixmap->height();
    if(w>maxSizeInitial_w || h>maxSizeInitial_h)
        modifySize(w,h,maxSizeInitial_w,maxSizeInitial_h);
    QPixmap pixmap_temp = pixmap->scaled(w,h);
    ui->label->setPixmap(pixmap_temp);//加载图片
}

//将宽w,长h限制在maxSize_w和maxSize_h之间
void LargerViewDialog::modifySize(int &w,int &h,int maxSize_w,int maxSize_h)
{
    if(w/maxSize_w>h/maxSize_h){
        double ratio = maxSize_w*1.0/w;
        w = maxSize_w;
        h = ratio*h;
    }
    else{
        double ratio = maxSize_h*1.0/h;
        h = maxSize_h;
        w = ratio*w;
    }
}

//窗口尺寸变化事件
void LargerViewDialog::resizeEvent(QResizeEvent *event)
{
    //当窗口变化不影响图片尺寸时，避免重加载
    if((ui->label->pixmap().height()==height())||(ui->label->pixmap().width()==width())){
        return;
    }
    //根据窗口大小重新计算图片尺寸，并重新加载
    int w = pixmap->width();
    int h = pixmap->height();
    if(w>width() || h>height()){
        modifySize(w,h,width(),height());
    }
    QPixmap pixmap_temp = pixmap->scaled(w,h);
    ui->label->setPixmap(pixmap_temp);
}
