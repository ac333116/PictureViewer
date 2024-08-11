/********************************************************************************
** Form generated from reading UI file 'largerviewdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LARGERVIEWDIALOG_H
#define UI_LARGERVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_LargerViewDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QDialog *LargerViewDialog)
    {
        if (LargerViewDialog->objectName().isEmpty())
            LargerViewDialog->setObjectName("LargerViewDialog");
        LargerViewDialog->resize(400, 300);
        horizontalLayout = new QHBoxLayout(LargerViewDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(LargerViewDialog);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);


        retranslateUi(LargerViewDialog);

        QMetaObject::connectSlotsByName(LargerViewDialog);
    } // setupUi

    void retranslateUi(QDialog *LargerViewDialog)
    {
        LargerViewDialog->setWindowTitle(QCoreApplication::translate("LargerViewDialog", "Dialog", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LargerViewDialog: public Ui_LargerViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LARGERVIEWDIALOG_H
