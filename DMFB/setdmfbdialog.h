#ifndef SETDFMBDIALOG_H
#define SETDFMBDIALOG_H

#include <QDialog>
//#include "mainwindow.h"

namespace Ui {
class SetDFMBDialog;
}

class MainWindow;

class SetDMFBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDMFBDialog(QWidget *parent = nullptr, int col=5, int row=5, QString inPortStr="", QString outPortStr="", MainWindow *mainWindow=NULL);
    ~SetDMFBDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SetDFMBDialog *ui;
    MainWindow *mainWindow;
};

#endif // SETDFMBDIALOG_H
