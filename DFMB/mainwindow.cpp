#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setdfmbdialog.h"
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <QPaintEvent>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gridSize=40;
    leftUp=QPoint(50,70);
    col=row=5;
    repaint();
}

QPoint MainWindow::getPoint(int a, int b){
    return QPoint((a-1)*gridSize+leftUp.x(), (b-1)*gridSize+leftUp.y());
}

int MainWindow::getCol()
{
    return col;
}

int MainWindow::getRow()
{
    return row;
}

QString MainWindow::getInPortStr()
{
    return inPortStr;
}

QString MainWindow::getOutPortStr()
{
    return outPortStr;
}

void MainWindow::setCol(int col)
{
    this->col = col;
}

void MainWindow::setRow(int row)
{
    this->row = row;
}

void MainWindow::setInPortStr(QString inPortStr)
{
    this->inPortStr = inPortStr;
}

void MainWindow::setOutPortStr(QString outPortStr)
{
    this->outPortStr = outPortStr;
}

int MainWindow::parsePortStr(QString portStr)
{
    // 解析表示端口的字符串，存储到tmpList这个成员变量中，类型为QList<QPoint>。返回-1表示解析出错，-2表示数字范围出错，否则返回长度
    QStringList strList = portStr.split(';');
    int len = strList.length();
    tmpList.clear();
    for(int i=0;i<len;++i){
        QString nowStr = strList.at(i) ;
        QStringList strList2 = nowStr.split(',');
        if(strList2.length()!=2) return -1;
        bool ok;
        int x=strList2.at(0).toInt(&ok);
        if(!ok) return -1;
        int y=strList2.at(1).toInt(&ok);
        if(!ok) return -1;
        if(x<1 || x>col || y<1 || y>row) return -2;
        tmpList.append(QPoint(x,y));
    }
    return len;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this) ;
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    for(int i=1;i<=col+1;++i){
        for(int j=1;j<=row+1;++j){
            if(i!=col+1) painter.drawLine(getPoint(i,j),getPoint(i+1,j));
            if(j!=row+1) painter.drawLine(getPoint(i,j),getPoint(i,j+1));
        }
    }
    QPoint tmp = getPoint(col+1,row+1);
    this->setMinimumSize(tmp.x()+50, tmp.y()+50);
    this->setMaximumSize(tmp.x()+50, tmp.y()+50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSetDFMB_triggered()
{
    setdfmbdialog = new SetDFMBDialog(this, col, row, inPortStr, outPortStr, this);
    setdfmbdialog -> show();
}
