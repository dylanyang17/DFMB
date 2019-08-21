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

bool isOnEdge(QPoint p, int col, int row)
{
    return p.x()==1||p.x()==col||p.y()==1||p.y()==row;
}

void SetDFMBDialog::on_buttonBox_accepted()
{
    int col=ui->spinBoxCol->value();
    int row=ui->spinBoxRow->value();
    if(col<=3 && row<=3){
        QMessageBox::critical(this, "参数错误", "行列不允许同时小于等于3");
        this->show();
        return;
    }
    int ret1 = mainWindow->parsePortStr(ui->lineEditInPort->text(), col, row);
    if(ret1==-1){
        QMessageBox::critical(this, "参数错误", "输入端口格式错误");
        this->show();
        return;
    }
    else if(ret1==-2){
        QMessageBox::critical(this, "参数错误", "输入端口坐标超出范围");
        this->show();
        return;
    }
    else if(ret1>1){
        QMessageBox::critical(this, "参数错误", "输入端口不唯一");
        this->show();
        return;
    }
    if(ret1!=0 && !isOnEdge(mainWindow->tmpList.at(0),col,row)){
        QMessageBox::critical(this, "参数错误", "输入端口不在边界上");
        this->show();
        return;
    }
    QList<QPoint> inPortList=mainWindow->tmpList;
    int ret2 = mainWindow->parsePortStr(ui->lineEditOutPort->text(), col, row);
    if(ret2==-1){
        QMessageBox::critical(this, "参数错误", "输出端口格式错误");
        this->show();
        return;
    }
    else if(ret2==-2){
        QMessageBox::critical(this, "参数错误", "输出端口坐标超出范围");
        this->show();
        return;
    }
    for(int i=0;i<ret2;++i){
        if(!isOnEdge(mainWindow->tmpList.at(i),col,row)){
            QMessageBox::critical(this, "参数错误", "输出端口不在边界上");
            this->show();
            return;
        }
    }
    mainWindow->setCol(col);
    mainWindow->setRow(row);
    mainWindow->setInPortStr(ui->lineEditInPort->text());
    mainWindow->setOutPortStr(ui->lineEditOutPort->text());
    if(ret1>0) mainWindow->inPortList  = inPortList;
    else mainWindow->inPortList.clear();
    if(ret2>0) mainWindow->outPortList = mainWindow->tmpList;
    else mainWindow->outPortList.clear();
    mainWindow->init();
}
