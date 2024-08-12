#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QFileDialog>
#include <QSpacerItem>
#include <QWheelEvent>

#include "myitem.h"
#include "largerviewdialog.h"
#include "mylabel.h"
#include "imageloaderthread.h"


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
    //界面初始化
    void InterfaceInitialization();
    //菜单初始化
    void menuInitialization();
    //文件列表初始化
    void fileListInitialization();
    //图片表格初始化
    void pictureTableInitialization();

    QString showPath;//展示文件夹的路径
    //LargerViewDialog *lvd;//大浏览图片窗口
    int columnCount = 4;//一列的格子数量
    int rowCount = 50;//一行的格子行数
    int pictureMaxSize = 400;

    //记录存入文件列表
    // QStringList pathlist;
    // void showPathList();

    // QList<File>fileList;
    // void showFileList();
    // void addFile(File file);

    //计算新的一列格子数
    void columnCountUpdate();

    //取得文件名(指定路径)
    QString getName(QString str);

    //图片组显示函数(showPath路径)
    void showPicture();
    //void addSinglePicture(QString &path,int i,int j);



signals:
    void loadSP_signal(int i,int j,MyLabel *label);

private slots:
    void SlotCreateProject(bool);//创建工程槽函数
    void SlotZoomIn();//展示图片放大
    void SlotZoomOut();//展示图片放大
    void wheelEvent(QWheelEvent *event);//重写鼠标滚轮事件：通过鼠标滚轮控制缩放
    void loadSinglePicture(int i,int j,MyLabel *label);


};
#endif // MAINWINDOW_H
