#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QGuiApplication>
#include <QRect>

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
    //变量初始化
    variateInitialization();

}

MainWindow::~MainWindow()
{
    for(int i=0; i<labelGroup.size(); i++){
        if(labelGroup[i]!=nullptr){
            delete labelGroup[i];
        }
    }
    for(int i=0; i<pixmapGroup.size(); i++){
        if(pixmapGroup[i]!=nullptr){
            delete pixmapGroup[i];
        }
    }
    for(int i=0; i<threadGroup.size(); i++){
        if(threadGroup[i]!=nullptr){
            threadGroup[i]->exit();
            threadGroup[i]->wait();
            delete threadGroup[i];
        }
    }

    delete ui;
}

//界面初始化
void MainWindow::InterfaceInitialization(){
    setWindowTitle("Album"); //设置主窗口标题
    setWindowIcon(QIcon(":/icon/pic-one.png"));//设置窗口图标
    showMaximized();//窗口最大化
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
        connect(act_clear_project,&QAction::triggered,this,&MainWindow::SlotClearProject);
        //打开项目动作
        QAction* act_open_project = new QAction(QIcon(":/icon/afferent.png"),tr("打开项目"));
        act_create_project->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
        menu_file->addAction(act_open_project);

    //创建设置菜单
    QMenu* menu_set = menuBar()->addMenu(tr("设置(&S)"));
        //设置菜单
        QAction* act_music = new QAction(QIcon(":icon/add-music.png"),tr("设置菜单"),this);
        act_music->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_M));
        menu_set->addAction(act_music);
        // connect(act_music,&QAction::triggered,[this](){
        //     for(int i=0; i<threadGroup.size(); i++){
        //         qDebug()<<"threadGroup["<<i<<"]->isFinished()"<<threadGroup[i]->isFinished();
        //         qDebug()<<"threadGroup["<<i<<"]->isRunning()"<<threadGroup[i]->isRunning();
        //     }
        // });
        //图片展示放大
        QAction* act_zoom_in = new QAction(QIcon(":icon/zoom-in.png"),tr("图片放大"),this);
        menu_set->addAction(act_zoom_in);
        connect(act_zoom_in,&QAction::triggered,this,&MainWindow::SlotZoomIn);
        //图片展示缩小
        QAction* act_zoom_out = new QAction(QIcon(":icon/zoom-out.png"),tr("图片缩小"),this);
        menu_set->addAction(act_zoom_out);
        connect(act_zoom_out,&QAction::triggered,this,&MainWindow::SlotZoomOut);
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
    //隐藏垂直和水平表头
    ui->picture_table_widget->horizontalHeader()->setVisible(false);
    ui->picture_table_widget->verticalHeader()->setVisible(false);
    //隐藏表格边框
    ui->picture_table_widget->setShowGrid(false);
    //设置滚动模式：按像素
    ui->picture_table_widget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->picture_table_widget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //图片加载信号连接
    //connect(this,&MainWindow::loadSP_signal,this,&MainWindow::loadSinglePicture);
}
//变量初始化
void MainWindow::variateInitialization()
{
    //设置线程最大数量为理想数量
    threadMaxNum = QThread::idealThreadCount()-2;
    //初始化线程组
    for(int i=0; i<threadMaxNum; i++){
        QThread *th = new QThread;
        threadGroup.push_back(th);
    }

    //全局图像最大尺寸初始化
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    pictureMaxSizeOverall = screenGeometry.width()/2;
}

//计算新的一列格子数
void MainWindow::columnCountUpdate()
{
    int distance = columnCount * (pictureMaxSize+2*labelMargin) - 0.9*width();

    int varianceNum=distance/pictureMaxSize;
    if(distance>0&&(distance%pictureMaxSize>0.2*pictureMaxSize)){
        varianceNum++;
    }
    columnCount = columnCount - varianceNum;
    ui->picture_table_widget->setColumnCount(columnCount);
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
    QPixmap originalPixmap(":icon/picture-album.png");//传入图标图像
    QPixmap scaledPixmap = originalPixmap.scaled(QSize(25, 25)); //调整图标尺寸
    QIcon icon;
    icon.addPixmap(scaledPixmap);
    //icon.addFile("D:\\QT\\Projects\\myPhotoAlbum\\icon\\picture-album");
    item->setIcon(icon);
    item->setSizeHint(QSize(100,40));//调整item尺寸
    ui->file_list_widget->addItem(item);//添加至file_list_widget
    //ui->file_list_widget->addItem(getName(qFileDialog.selectedFiles()[0]));
}

//项目清空
void MainWindow::SlotClearProject()
{
    ui->file_list_widget->clear();

    ui->picture_table_widget->clearContents();
    for(int i=0; i<pictureNum; i++){
        if(labelGroup[i]!=nullptr){
            delete labelGroup[i];
            labelGroup[i] = nullptr;
        }
        if(pixmapGroup[i]!=nullptr){
            delete pixmapGroup[i];
            pixmapGroup[i] = nullptr;
        }
    }
    labelGroup.clear();
    pixmapGroup.clear();

    showPath = "";
    pictureNum = 0;
}

//菜单:图片放大
void MainWindow::SlotZoomIn()
{
    if(workNum!=0)return;
    if(pictureMaxSize < 0.9*width()/2){
        pictureMaxSize+=100;
        labelMargin = getMargin(pictureMaxSize);
        reloadPicture();
    }
}
//菜单:图片缩小
void MainWindow::SlotZoomOut()
{
    if(workNum!=0)return;
    if(pictureMaxSize>100){
        pictureMaxSize-=100;
        labelMargin = getMargin(pictureMaxSize);
        reloadPicture();
    }
    else if(pictureMaxSize>10){
        pictureMaxSize-=10;
        labelMargin = getMargin(pictureMaxSize);
        reloadPicture();
    }
}
//鼠标滑轮事件
void MainWindow::wheelEvent(QWheelEvent *event)
{
    Qt::KeyboardModifiers modifiers = event->modifiers();

    // Ctrl键被按下
    if (modifiers & Qt::ControlModifier)
    {
        if(workNum!=0)return;
        // if(QDateTime::currentMSecsSinceEpoch()-lastWheelTime < 80){//禁止80ms以内操作
        //     return;
        // }
        if (event->angleDelta().y() > 0) // Ctrl + 滚轮向上
        {
            if(pictureMaxSize < 0.9*width()/2){
                pictureMaxSize+=50;
                labelMargin = getMargin(pictureMaxSize);
                reloadPicture();
            }
        }
        else// Ctrl + 滚轮向下
        {
            if(pictureMaxSize>100){
                pictureMaxSize-=50;
                labelMargin = getMargin(pictureMaxSize);
                reloadPicture();
            }
            else if(pictureMaxSize>10){
                pictureMaxSize-=10;
                labelMargin = getMargin(pictureMaxSize);
                reloadPicture();
            }
        }
        //lastWheelTime = QDateTime::currentMSecsSinceEpoch();//更新时间戳
    }
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

int MainWindow::getMargin(int size)
{
    if(size>400)
        return 10;
    else if(size>100)
        return 5;
    else
        return 2;
}

//图片显示函数
//  输入：文件路径
//  结果：将目标路径内的所有图片展示在picture_table_widget
void MainWindow::showPicture(){
    if(workNum!=0)return;

    QDir dir(showPath);
    // 检查目录是否存在
    if (!dir.exists()) {
        qDebug() << "path does not exist:";
        return;
    }
    QStringList imagePaths;//定义用于图片路径存放的列表
    // 设置过滤条件，只查找图片文件
    QStringList imageFormats = QStringList() << "*.jpg" << "*.jpeg" << "*.png" << "*.gif";
    QFileInfoList fileList = dir.entryInfoList(imageFormats, QDir::Files);
    // 遍历文件列表
    foreach (const QFileInfo &fileInfo, fileList) {
        imagePaths.append(fileInfo.absoluteFilePath());//将文件的完整路径添加到列表中
    }
    //打印检查所有存入的图片的路径
    // for(QString str:imagePaths){
    //     qDebug()<<str<<"\n";
    // }

    ui->picture_table_widget->clearContents();
    for(int i=0; i<pictureNum; i++){
        if(labelGroup[i]!=nullptr){
            delete labelGroup[i];
            labelGroup[i] = nullptr;
        }
        if(pixmapGroup[i]!=nullptr){
            delete pixmapGroup[i];
            pixmapGroup[i] = nullptr;
        }
    }
    labelGroup.clear();
    pixmapGroup.clear();

    pictureNum = imagePaths.size();//更新图片数量

    if(pictureNum>columnCount*rowCount){//如果单元格小于图片数量，增加单元格
        ui->picture_table_widget->setRowCount(imagePaths.size()/columnCount+1);
    }

    //将所有图片添加到picture_table_widget中
    int i=0,j=0;
    for(QString str:imagePaths)
    {
        //创建label对象
        MyLabel *label = new MyLabel(str,this);
        //labelGroup[j+i*columnCount] = label;
        labelGroup.push_back(label);
        label->setAlignment((Qt::AlignCenter | Qt::AlignVCenter));//设置label中内容为水平和中心对齐
        label->setMargin(labelMargin);//设置图片与label间距

        //创建pixmap对象
        QPixmap *pixmap = new QPixmap;
        pixmapGroup.push_back(pixmap);

        //在子线程中操作对象
        // ImageLoaderThread *th = new ImageLoaderThread(label,pixmap,str,i,j,pictureMaxSize);
        // connect(th,&ImageLoaderThread::loadSP_signal,this,&MainWindow::loadSinglePicture);
        // th->start();

        workNum++;
        //将图片载入加入到子线程
        ImageLoaderWork *worker = new ImageLoaderWork;//创建工作对象
        worker->moveToThread(threadGroup[threadNext]);//加入线程
        connect(this, &MainWindow::startImageLoad, worker, &ImageLoaderWork::imageLoad);
        connect(worker,&ImageLoaderWork::loadSP_signal,this,&MainWindow::loadSinglePicture);//获得工作结果
        if(!threadGroup[threadNext]->isRunning())
            threadGroup[threadNext]->start();//启动线程
        emit startImageLoad(label, pixmap, str, i, j, pictureMaxSizeOverall, pictureMaxSize);//开始工作
        disconnect(this, &MainWindow::startImageLoad, worker, &ImageLoaderWork::imageLoad);

        threadNext++;
        if(threadNext==threadMaxNum)
            threadNext=0;

        j++;
        if(j==columnCount){
            j=0;
            i++;
        }
    }
}
//图片重载
void MainWindow::reloadPicture()
{
    ui->picture_table_widget->clearContents();
    for(int i=0; i<pictureNum; i++){
        if(labelGroup[i]!=nullptr){
            QString str = labelGroup[i]->path;
            delete labelGroup[i];
            //labelGroup[i] = nullptr;
            labelGroup[i] = new MyLabel(str,this);
            labelGroup[i]->setAlignment((Qt::AlignCenter | Qt::AlignVCenter));
            labelGroup[i]->setMargin(labelMargin);
        }
    }

    columnCountUpdate();
    if(pictureNum>columnCount*rowCount){//如果单元格小于图片数量，增加单元格
        ui->picture_table_widget->setRowCount(pictureNum/columnCount+1);
    }

    int i=0,j=0;
    for(int n=0; n<pictureNum; n++)
    {   
        // ImageLoaderThread *th = new ImageLoaderThread(labelGroup[n],pixmapGroup[n],"",i,j,pictureMaxSize);
        // connect(th,&ImageLoaderThread::loadSP_signal,this,&MainWindow::loadSinglePicture);
        // th->start();

        workNum++;
        ImageLoaderWork *worker = new ImageLoaderWork;
        worker->moveToThread(threadGroup[threadNext]);
        connect(this, &MainWindow::startImageLoad, worker, &ImageLoaderWork::imageLoad);
        connect(worker,&ImageLoaderWork::loadSP_signal,this,&MainWindow::loadSinglePicture);
        if(!threadGroup[threadNext]->isRunning())
            threadGroup[threadNext]->start();
        emit startImageLoad(labelGroup[n], pixmapGroup[n], "", i, j, pictureMaxSizeOverall, pictureMaxSize);
        disconnect(this, &MainWindow::startImageLoad, worker, &ImageLoaderWork::imageLoad);

        threadNext++;
        if(threadNext==threadMaxNum)
            threadNext=0;

        j++;
        if(j==columnCount){
            j=0;
            i++;
        }
    }
}

//单个图片加载
void MainWindow::loadSinglePicture(int i, int j, MyLabel *label, ImageLoaderWork *worker)
{
    //label->setPixmap(pixmap);

    // 将QLabel添加到表格指定位置单元格中
    ui->picture_table_widget->setCellWidget(i, j, label);

    //自动调整所有行或列的大小以适应其内容
    ui->picture_table_widget->resizeColumnsToContents();
    ui->picture_table_widget->resizeRowsToContents();

    //QCoreApplication::processEvents();//等待将当前图片绘制进窗口

    delete worker;//释放worker占用空间
    workNum--;
}



