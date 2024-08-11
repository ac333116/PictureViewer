#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss("D:\\QT\\Projects\\myPhotoAlbum\\style\\style.qss");
    if(qss.open(QFile::ReadOnly)){
        //qDebug()<<"qss打开成功\n";
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        //qDebug("qss打开失败");
        return 0;
    }

    MainWindow w;
    //设置主窗口标题和窗口最大化
    w.setWindowTitle("Album");
    w.showMaximized();
    w.show();

    return a.exec();
}
