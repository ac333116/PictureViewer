#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QFileDialog>
#include <QSpacerItem>
#include <QWheelEvent>
#include <QTimer>
#include <QThread>

#include "myitem.h"
#include "largerviewdialog.h"
#include "mylabel.h"
#include "imageloaderwork.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    QString showPath;//展示文件夹的路径
    int columnCount = 4;//一列的格子数量
    int rowCount = 50;//一行的格子行数
    int labelMargin = 10;//标签间距
    int pictureMaxSize = 400;//单图片最大尺寸
    int pictureMaxSizeOverall=800;//全局图片最大尺寸
    int pictureNum=0;//当前图片数量
    // qint64 lastWheelTime=0;//记录鼠标上次滚动事件
    int workNum = 0;//当前线程组中的总工作数量
    int threadMaxNum = 10;//记录线程最大数量
    int threadNext = 0;//下一个待使用线程
    QVector<MyLabel*> labelGroup;//图片标签组
    QVector<QPixmap*> pixmapGroup;//图片pixmap组
    QVector<QThread*> threadGroup;//线程组

private:
    //界面初始化
    void InterfaceInitialization();
    //菜单初始化
    void menuInitialization();
    //文件列表初始化
    void fileListInitialization();
    //图片表格初始化
    void pictureTableInitialization();
    //变量初始化
    void variateInitialization();
    //配置初始化
    void configInitialization();

    void columnCountUpdate();//计算新的一列格子数
    QString getName(QString str);//取得文件名(指定路径)
    int getMargin(int size);//根据图片尺寸计算label间距
    void showPicture();//图片组显示函数(showPath路径)
    //void addSinglePicture(QString &path,int i,int j);
    void reloadPicture();//图片重加载
    void loadSinglePicture(int i,int j,MyLabel *label,ImageLoaderWork *worker);//单图片加载函数

    void SlotSelectProject(bool);//创建工程槽函数
    void CreateProject(QString path);
    void SlotClearProject();//项目清空
    void SlotZoomIn();//展示图片放大
    void SlotZoomOut();//展示图片放大
    void wheelEvent(QWheelEvent *event);//重写鼠标滚轮事件：通过鼠标滚轮控制缩放


signals:
    void startImageLoad(MyLabel *label,QPixmap *pixmap,QString path,int i,int j,int pictureMaxSizeOverall,int pictureMaxSize);

};
#endif // MAINWINDOW_H
