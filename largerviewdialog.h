#ifndef LARGERVIEWDIALOG_H
#define LARGERVIEWDIALOG_H

#include <QDialog>
#include <QDir>
#include <QPixmap>

namespace Ui {
class LargerViewDialog;
}

class LargerViewDialog : public QDialog
{
    Q_OBJECT
public:
    //explicit LargerViewDialog(QWidget *parent = nullptr);
    explicit LargerViewDialog(QString path,QWidget *parent = nullptr);
    ~LargerViewDialog();
private:
    Ui::LargerViewDialog *ui;

public:
    QString path;
    int maxSizeInitial_h=800;//照片初始最大长度
    int maxSizeInitial_w=800*1.6;//照片初始最大宽度
    QPixmap *pixmap = new QPixmap;

private:
    void InterfaceInitialization();//界面初始化
    void pictureInitialization();//图片初始化

    void modifySize(int &w,int &h,int size,int maxSize_h);//尺寸调整

    void resizeEvent(QResizeEvent *event) override;//重写窗口尺寸变化事件

};

#endif // LARGERVIEWDIALOG_H
