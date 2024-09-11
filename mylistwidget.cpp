#include "mylistwidget.h"
#include "myitem.h"

myListWidget::myListWidget(QWidget *parent):QListWidget(parent)
{
    Initialization();


}


myListWidget::~myListWidget()
{
    delete floatMenu;
    delete removeAction;
}

void myListWidget::Initialization()
{
    //创建菜单
    floatMenu = new QMenu();
    //创建移除文件夹行为
    removeAction = new QAction();
    removeAction->setText("移除");
    floatMenu->addAction(removeAction);
    connect(removeAction,&QAction::triggered,this,[this](){
        //获取被移除的路径，并返回给主窗口
        QListWidgetItem *item_temp = this->item(removeRow);
        MyItem *myItem_temp = static_cast<MyItem*>(item_temp);
        QString removePath = myItem_temp->filePath;
        emit removeProject(removePath);

        delete takeItem(removeRow);//移除指定行的Item,并释放被移除Item的内存(takeItem会返回指向Item的指针)
    });
}


void myListWidget::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event); // 调用基类的事件处理函数
    //如果是右键
    if (event->button() == Qt::RightButton) {
        //将鼠标位置转换为项索引
        QPoint pos = event->pos();
        QModelIndex index = indexAt(pos);
        removeRow = index.row();
        if (index.isValid()) {
            //悬浮菜单显示
            floatMenu->exec(QCursor::pos());
        }
    }
}
