#include "mainwindow.h"

#include <QApplication>
#include <QFile>

// #include <thread>
// float Time=0;
// void timer()
// {
//     float interval = 0.2;//正值间隔
//     int t = static_cast<int>(interval*1000);
//     while (1) {
//         qDebug()<<Time;
//         std::this_thread::sleep_for(std::chrono::milliseconds(t));
//         Time+=interval;
//     }
// }

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
    w.show();

    //std::thread t_time(timer);

    return a.exec();
}
