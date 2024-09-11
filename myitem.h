#ifndef MYITEM_H
#define MYITEM_H

#include <QListWidgetItem>
#include <QMouseEvent>

class MyItem : public QListWidgetItem
{

public:
    MyItem();

    //每个item所代表的文件夹的路径
    QString filePath;



};

#endif // MYITEM_H
