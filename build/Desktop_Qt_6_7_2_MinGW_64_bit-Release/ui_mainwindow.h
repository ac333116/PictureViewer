/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *hl_cen;
    QHBoxLayout *hl_main;
    QVBoxLayout *vl_left;
    QVBoxLayout *vl_left_top;
    QWidget *widget_vl_left_top;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QVBoxLayout *vl_left_main;
    QWidget *widget_vl_left_main;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *file_list;
    QListWidget *file_list_widget;
    QVBoxLayout *vl_right;
    QVBoxLayout *vl_right_top;
    QWidget *widget_vl_right_top;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QVBoxLayout *vl_right_main;
    QWidget *widget_vl_right_main;
    QGridLayout *gridLayout;
    QGridLayout *picture_list;
    QTableWidget *picture_table_widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(701, 523);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        hl_cen = new QHBoxLayout(centralwidget);
        hl_cen->setSpacing(2);
        hl_cen->setObjectName("hl_cen");
        hl_cen->setContentsMargins(2, 2, 2, 2);
        hl_main = new QHBoxLayout();
        hl_main->setSpacing(2);
        hl_main->setObjectName("hl_main");
        vl_left = new QVBoxLayout();
        vl_left->setSpacing(1);
        vl_left->setObjectName("vl_left");
        vl_left_top = new QVBoxLayout();
        vl_left_top->setObjectName("vl_left_top");
        widget_vl_left_top = new QWidget(centralwidget);
        widget_vl_left_top->setObjectName("widget_vl_left_top");
        horizontalLayout_2 = new QHBoxLayout(widget_vl_left_top);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(widget_vl_left_top);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color:white;\n"
"	font-size:15px;\n"
"}"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);


        vl_left_top->addWidget(widget_vl_left_top);


        vl_left->addLayout(vl_left_top);

        vl_left_main = new QVBoxLayout();
        vl_left_main->setObjectName("vl_left_main");
        widget_vl_left_main = new QWidget(centralwidget);
        widget_vl_left_main->setObjectName("widget_vl_left_main");
        verticalLayout_7 = new QVBoxLayout(widget_vl_left_main);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        file_list = new QVBoxLayout();
        file_list->setObjectName("file_list");
        file_list_widget = new QListWidget(widget_vl_left_main);
        file_list_widget->setObjectName("file_list_widget");
        file_list_widget->setStyleSheet(QString::fromUtf8("background-color:rgb(110,110,110);"));

        file_list->addWidget(file_list_widget);


        verticalLayout_7->addLayout(file_list);


        vl_left_main->addWidget(widget_vl_left_main);


        vl_left->addLayout(vl_left_main);

        vl_left->setStretch(0, 1);
        vl_left->setStretch(1, 15);

        hl_main->addLayout(vl_left);

        vl_right = new QVBoxLayout();
        vl_right->setSpacing(1);
        vl_right->setObjectName("vl_right");
        vl_right_top = new QVBoxLayout();
        vl_right_top->setObjectName("vl_right_top");
        widget_vl_right_top = new QWidget(centralwidget);
        widget_vl_right_top->setObjectName("widget_vl_right_top");
        horizontalLayout_3 = new QHBoxLayout(widget_vl_right_top);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(widget_vl_right_top);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color:white;\n"
"	font-size:15px;\n"
"}"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_2);


        vl_right_top->addWidget(widget_vl_right_top);


        vl_right->addLayout(vl_right_top);

        vl_right_main = new QVBoxLayout();
        vl_right_main->setObjectName("vl_right_main");
        widget_vl_right_main = new QWidget(centralwidget);
        widget_vl_right_main->setObjectName("widget_vl_right_main");
        gridLayout = new QGridLayout(widget_vl_right_main);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(2, 2, 2, 2);
        picture_list = new QGridLayout();
        picture_list->setObjectName("picture_list");
        picture_table_widget = new QTableWidget(widget_vl_right_main);
        picture_table_widget->setObjectName("picture_table_widget");
        picture_table_widget->setStyleSheet(QString::fromUtf8("background-color:rgb(80,80,80);"));

        picture_list->addWidget(picture_table_widget, 0, 0, 1, 1);


        gridLayout->addLayout(picture_list, 0, 0, 1, 1);


        vl_right_main->addWidget(widget_vl_right_main);


        vl_right->addLayout(vl_right_main);

        vl_right->setStretch(0, 1);
        vl_right->setStretch(1, 15);

        hl_main->addLayout(vl_right);

        hl_main->setStretch(0, 1);
        hl_main->setStretch(1, 10);

        hl_cen->addLayout(hl_main);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 701, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\345\244\271", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\265\217\350\247\210\347\252\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
