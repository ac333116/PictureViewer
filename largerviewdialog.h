#ifndef LARGERVIEWDIALOG_H
#define LARGERVIEWDIALOG_H

#include <QDialog>
#include <QDir>

namespace Ui {
class LargerViewDialog;
}

class LargerViewDialog : public QDialog
{
    Q_OBJECT

public:
    //explicit LargerViewDialog(QWidget *parent = nullptr);
    explicit LargerViewDialog(QString path,QWidget *parent = nullptr);
    ~LargerViewDialog();

private:
    Ui::LargerViewDialog *ui;

public:
    QString path;

};

#endif // LARGERVIEWDIALOG_H
