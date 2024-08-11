#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //界面初始化
    InterfaceInitialization();
    //菜单初始化
    menuInitialization();
    //图片表格初始化
    pictureTableInitialization();
    //文件列表初始化
    fileListInitialization();




}

MainWindow::~MainWindow()
{
    delete ui;
}

//界面初始化
void MainWindow::InterfaceInitialization(){
    setWindowIcon(QIcon(":/icon/pic-one.png"));
}
//菜单栏初始化
void MainWindow::menuInitialization(){
//创建文件菜单
QMenu* menu_file = menuBar()->addMenu(tr("文件(&F)"));
    //创建项目动作
    QAction* act_create_project = new QAction(QIcon(":icon/doc_add"),tr("创建项目"));
    act_create_project->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
    menu_file->addAction(act_create_project);
    connect(act_create_project,&QAction::triggered,this,&MainWindow::SlotCreateProject);
    //清空项目
    QAction* act_clear_project = new QAction(QIcon(":icon/delete-five"),tr("清空项目"));
    menu_file->addAction(act_clear_project);
    connect(act_clear_project,&QAction::triggered,[this](){ui->file_list_widget->clear();ui->picture_table_widget->clear();});
    //打开项目动作
    QAction* act_open_project = new QAction(QIcon(":/icon/afferent.png"),tr("打开项目"));
    act_create_project->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
    menu_file->addAction(act_open_project);

//创建设置菜单
QMenu* menu_set = menuBar()->addMenu(tr("设置(&S)"));
    //
    QAction* act_music = new QAction(QIcon("D:\\QT\\Projects\\myPhotoAlbum\\icon\\add-music"),tr("设置"),this);
    act_music->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_M));
    menu_set->addAction(act_music);
}
//文件列表初始化
void MainWindow::fileListInitialization(){
    //设置图标大小
    ui->file_list_widget->setIconSize(QSize(25, 25));

    //当点击条目(item)时，根据条目内存储的路径在图片表格内加载图片
    connect(ui->file_list_widget,&QListWidget::itemClicked,[this](QListWidgetItem *item){
        MyItem *myitem = static_cast<MyItem*>(item);
        //qDebug()<<myitem->filePath;

        //加载指定路径
        if(showPath!=myitem->filePath){  //判断是否与原路径相同，以防重加载
            showPath = myitem->filePath;
            showPicture();
        }
    });



}
//图片表格初始化
void MainWindow::pictureTableInitialization()
{
     //ui->file_list_widget->setViewMode(QListView::IconMode);//设置filelistwidget为图标展示

    //设置行列数量
    ui->picture_table_widget->setRowCount(rowCount);
    ui->picture_table_widget->setColumnCount(columnCount);
    // ui->picture_table_widget->setRowHeight(0, 500);
    // ui->picture_table_widget->setColumnWidth(0, 500);
    //隐藏垂直和水平表头
    ui->picture_table_widget->horizontalHeader()->setVisible(false);
    ui->picture_table_widget->verticalHeader()->setVisible(false);
    //隐藏表格边框
    ui->picture_table_widget->setShowGrid(false);
    //设置滚动模式：按像素
    ui->picture_table_widget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->picture_table_widget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}



//槽函数：创建文件夹
void MainWindow::SlotCreateProject(bool)
{
    //通过文件对话框选择目标文件夹
    QFileDialog qFileDialog;
    qFileDialog.setFileMode(QFileDialog::Directory);//设置模式：选择文件夹
    qFileDialog.exec();//打开文件选择窗口

    //将路径添加到pathlist
    // pathlist.append(qFileDialog.selectedFiles());
    // showPathList();

    //向file_list_widget列表添加选中的文件(通过Item)
    //QListWidgetItem *item = new QListWidgetItem();
    MyItem *item = new MyItem();
    item->setText(getName(qFileDialog.selectedFiles()[0]));//设置标签名称
    item->filePath=qFileDialog.selectedFiles()[0];//添加文件路径
    //修改字体大小
    QFont f = item->font();
    f.setPointSize(12);
    item->setFont(f);
    //设置图标图片
    QPixmap originalPixmap("D:\\QT\\Projects\\myPhotoAlbum\\icon\\picture-album.png");//传入图标图像
    QPixmap scaledPixmap = originalPixmap.scaled(QSize(25, 25)); //调整图标尺寸
    QIcon icon;
    icon.addPixmap(scaledPixmap);
    //icon.addFile("D:\\QT\\Projects\\myPhotoAlbum\\icon\\picture-album");
    item->setIcon(icon);
    item->setSizeHint(QSize(100,40));//调整item尺寸
    ui->file_list_widget->addItem(item);//添加至file_list_widget
    //ui->file_list_widget->addItem(getName(qFileDialog.selectedFiles()[0]));
}


//打印已存入的相册文件路径到命令窗口
// void MainWindow::showPathList(){
//     qDebug()<<"pathlist:"<<":\n";
//     for(QString str:pathlist){//遍历pathlist
//         qDebug()<<str<<"\n";
//     }
// }

//从路径中取得最后一个文件的文件名
QString MainWindow::getName(QString str){
    int pos = str.lastIndexOf("/");
    if(pos==-1)
        pos = str.lastIndexOf("\\");
    if(pos==-1)
        return "flase";

    QString name;
    // //限制文件名长度=16
    // int length = 16;
    // if(str.size()-pos<length-1){
    //     name = str.mid(pos+1,length);
    //     int num = length-name.size();
    //     for(int i=0; i<num; i++){
    //         name = name+" ";
    //     }
    // }
    // else{
    //     name = str.mid(pos+1,length-3)+"...";
    // }
    name = str.mid(pos+1,20);

    return name;
}


//图片显示函数
//  输入：文件路径
//  结果：将目标路径内的所有图片展示在picture_table_widget
void MainWindow::showPicture(){
    QDir dir(showPath);
    // 检查目录是否存在
    if (!dir.exists()) {
        qDebug() << "path does not exist:";
        return;
    }


    //定义用于图片路径存放的列表
    QStringList imagePaths;
    // 设置过滤条件，只查找图片文件
    QStringList imageFormats = QStringList() << "*.jpg" << "*.jpeg" << "*.png" << "*.gif";
    QFileInfoList fileList = dir.entryInfoList(imageFormats, QDir::Files);
    // 遍历文件列表
    foreach (const QFileInfo &fileInfo, fileList) {
        // 将文件的完整路径添加到列表中
        imagePaths.append(fileInfo.absoluteFilePath());
    }

    //打印检查所有存入的图片的路径
    // for(QString str:imagePaths){
    //     qDebug()<<str<<"\n";
    // }

    ui->picture_table_widget->clearContents();//清除旧图片
    //qDebug()<<"清除图片";
    if(imagePaths.size()>columnCount*rowCount){//如果单元格小于图片数量，增加单元格
        ui->picture_table_widget->setRowCount(imagePaths.size()/columnCount+1);
    }


    //将所有图片添加到picture_table_widget中
    int i=0,j=0;
    for(QString str:imagePaths)
    {

        addSinglePicture(str,i,j);

        j++;
        if(j==columnCount){
            j=0;
            i++;
        }
    }

    //自动调整所有行或列的大小以适应其内容
    ui->picture_table_widget->resizeColumnsToContents();
    ui->picture_table_widget->resizeRowsToContents();
}

void MainWindow::addSinglePicture(QString path,int i,int j){
    //QLabel *label = new QLabel(this);
    MyLabel *label = new MyLabel(path,this);
    label->setAlignment((Qt::AlignCenter | Qt::AlignVCenter));//设置label中内容为水平和中心对齐
    label->setMargin(10);//设置图片与label间距

    QPixmap pixmap(path);
        //label->setSizeIncrement(QSize(pixmap.width(),pixmap.height()));
        //可以选择调整pixmap的大小以适应单元格，或者保持原样
        //pixmap = pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //修改图片尺寸
    int w,h;
    if(pixmap.width()>pixmap.height()){
        w=400;
        h=pixmap.height()*400/pixmap.width();
    }
    else{
        h=400;
        w=pixmap.width()*400/pixmap.height();
    }
    pixmap = pixmap.scaled(QSize(w,h));

    label->setPixmap(pixmap);

    // 将QLabel添加到表格指定位置单元格中
    ui->picture_table_widget->setCellWidget(i, j, label);
    //qDebug()<<"添加"<<i<<"  "<<j<<"\n";

}



