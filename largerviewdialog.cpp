#include "largerviewdialog.h"
#include "ui_largerviewdialog.h"

LargerViewDialog::LargerViewDialog(QString path,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LargerViewDialog)
{
    ui->setupUi(this);

    setWindowTitle("照片阅览");
    this->path=path;//设置图片路径

    ui->label->setAlignment((Qt::AlignCenter | Qt::AlignVCenter));//设置label中内容为水平和中心对齐
    //ui->label->setMargin(10);//设置label间距

    QPixmap pixmap(path);
    //修改图片尺寸
    int w,h;
    int max_w=1280,max_h=800;
    if(pixmap.width()<max_w && pixmap.height()<max_h){
        w=pixmap.width();
        h=pixmap.height();
    }
    else{
        if((pixmap.width()/max_w)>(pixmap.height()/max_h)){
            w=max_w;
            h=pixmap.height()*max_w/pixmap.width();
        }
        else{
            h=max_h;
            w=pixmap.width()*max_h/pixmap.height();
        }
    }
    pixmap = pixmap.scaled(QSize(w,h));
    //qDebug()<<"w="<<w<<"  h="<<h<<"\n";

    setFixedSize(w,h);//固定窗口尺寸

    ui->label->setPixmap(pixmap);//加载图片

}

LargerViewDialog::~LargerViewDialog()
{
    delete ui;
}
