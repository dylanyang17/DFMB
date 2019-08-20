#include "setdfmbdialog.h"
#include "ui_setdfmbdialog.h"
#include <QString>
#include "mainwindow.h"
#include <QMessageBox>

SetDFMBDialog::SetDFMBDialog(QWidget *parent, int col, int row, QString inPortStr, QString outPortStr, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::SetDFMBDialog)
{
    ui->setupUi(this);
    ui->spinBoxCol->setValue(col);
    ui->spinBoxRow->setValue(row);
    ui->lineEditInPort->setText(inPortStr);
    ui->lineEditOutPort->setText(outPortStr);
    this->mainWindow = mainWindow;
}

SetDFMBDialog::~SetDFMBDialog()
{
    delete ui;
}

void SetDFMBDialog::on_buttonBox_accepted()
{
    int col=ui->spinBoxCol->value();
    int row=ui->spinBoxRow->value();
    if(col<=3 && row<=3){
        QMessageBox::critical(this, "参数错误", "行列不允许同时小于等于3");
        return;
    }
    int ret = mainWindow->parsePortStr(ui->lineEditInPort->text());
    if(ret==-1){
        QMessageBox::critical(this, "参数错误", "输入端口格式错误");
        return;
    }
    else if(ret==-2){
        QMessageBox::critical(this, "参数错误", "输入端口坐标超出范围");
        return;
    }
    else if(ret>1){
        QMessageBox::critical(this, "参数错误", "输入端口应当唯一");
        return;
    }
    QList<QPoint> inPortList=mainWindow->tmpList;
    ret = mainWindow->parsePortStr(ui->lineEditOutPort->text());
    if(ret==-1){
        QMessageBox::critical(this, "参数错误", "输出端口格式错误");
        return;
    }
    else if(ret==-2){
        QMessageBox::critical(this, "参数错误", "输出端口坐标超出范围");
        return;
    }
    mainWindow->setCol(col);
    mainWindow->setRow(row);
    mainWindow->setInPortStr(ui->lineEditInPort->text());
    mainWindow->setOutPortStr(ui->lineEditOutPort->text());
    mainWindow->inPortList  = inPortList;
    mainWindow->outPortList = mainWindow->tmpList;
}
