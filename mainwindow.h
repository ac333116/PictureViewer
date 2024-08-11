#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QFileDialog>
#include <QSpacerItem>

#include "myitem.h"
#include "largerviewdialog.h"
#include "mylabel.h"


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

    //展示文件夹的路径
    QString showPath;
    //大浏览图片窗口
    //LargerViewDialog *lvd;
    //每列的格子数量
    int columnCount = 4;
    //格子行数
    int rowCount = 50;

    //记录存入文件列表
    // QStringList pathlist;
    // void showPathList();

    // QList<File>fileList;
    // void showFileList();
    // void addFile(File file);



    //取得文件名(指定路径)
    QString getName(QString str);

    //图片组显示函数(showPath路径)
    void showPicture();
    void addSinglePicture(QString path,int i,int j);



private slots:
    void SlotCreateProject(bool);//创建工程槽函数


};
#endif // MAINWINDOW_H
