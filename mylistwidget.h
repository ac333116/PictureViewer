#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QMenu>

class myListWidget : public QListWidget
{
    Q_OBJECT

public:
    myListWidget(QWidget *parent = nullptr);

    ~myListWidget();

private:
    QMenu *floatMenu;//右键菜单
    QAction *removeAction;//文件移除Action
    int removeRow;//文件移除行

    void Initialization();

    void mousePressEvent(QMouseEvent *event) override;//鼠标点击事件

signals:
    void removeProject(QString path);

};

#endif // MYLISTWIDGET_H
