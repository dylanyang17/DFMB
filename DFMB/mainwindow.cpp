#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setdfmbdialog.h"
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <QPaintEvent>
#include <QSizePolicy>
#include <QColor>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <cmath>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gridSize=40;
    leftUp=QPoint(60,105);
    timeLim=timeNow=0;
    col=row=5;
    repaint();
}

QPoint MainWindow::getPoint(int a, int b){
    //获得网格点的坐标，a=1且b=1时为左上角的网格点，a增大则向右移动
    return QPoint((a-1)*gridSize+leftUp.x(), (b-1)*gridSize+leftUp.y());
}

QPoint MainWindow::getMidPoint(int a, int b){
    //获得网格中心点的坐标
    return QPoint((2*a-1)*gridSize/2+leftUp.x(), (2*b-1)*gridSize/2+leftUp.y());
}

QPoint MainWindow::getEdgeInd(QPoint p){
    //从边界的网格索引得到相邻的边界外处的网格索引
    int x=p.x();
    int y=p.y();
    if(x==1)
        return QPoint(x-1,y);
    else if(x==col)
        return QPoint(x+1,y);
    else if(y==row)
        return QPoint(x,y+1);
    else if(y==1)
        return QPoint(x,y-1);

    else assert(0);
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
    if(portStr==""){
        return 0;
    }
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

    //网格线
    for(int i=1;i<=col+1;++i){
        for(int j=1;j<=row+1;++j){
            if(i!=col+1) painter.drawLine(getPoint(i,j),getPoint(i+1,j));
            if(j!=row+1) painter.drawLine(getPoint(i,j),getPoint(i,j+1));
        }
    }
    QPoint tmp = getPoint(col+1,row+1);
    this->setMinimumSize(tmp.x()+60, tmp.y()+60);
    this->setMaximumSize(tmp.x()+60, tmp.y()+60);

    //输入和输出端口
    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    for(int i=0;i<inPortList.length();++i){
        tmp = inPortList.at(i);
        tmp = getEdgeInd(tmp);
        tmp = getPoint(tmp.x(),tmp.y()) ;
        painter.drawRoundRect(tmp.x(),tmp.y(),gridSize,gridSize);
    }
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    for(int i=0;i<outPortList.length();++i){
        tmp = outPortList.at(i);
        tmp = getEdgeInd(tmp);
        tmp = getPoint(tmp.x(),tmp.y()) ;
        painter.drawRoundRect(tmp.x(),tmp.y(),gridSize,gridSize);
    }

    //清洗液滴的端口
    painter.setBrush(QBrush(QColor(100,50,80),Qt::SolidPattern));
    tmp = getEdgeInd(QPoint(1,row));
    tmp = getPoint(tmp.x(),tmp.y());
    painter.drawRoundRect(tmp.x(),tmp.y(),gridSize,gridSize);
    painter.setBrush(QBrush(QColor(50,80,120),Qt::SolidPattern));
    tmp = getEdgeInd(QPoint(col,1));
    tmp = getPoint(tmp.x(),tmp.y());
    painter.drawRoundRect(tmp.x(),tmp.y(),gridSize,gridSize);

    //液滴
    for(int i=1;i<=col;++i){
        for(int j=1;j<=row;++j){
            if(nowDrop[i][j]){
                painter.setBrush(QBrush(dropColor.at(nowDrop[i][j]),Qt::SolidPattern));
                tmp = getPoint(i,j) ;
                painter.drawEllipse(tmp.x(),tmp.y(),gridSize,gridSize) ;
            }
        }
    }
}

int MainWindow::newDrop(){
    //返回++dropCnt，注意可能产生新颜色
    ++dropCnt;
    if(dropColor.length()<dropCnt){
        dropColor.append(QColor(qrand()%230,qrand()%230,qrand()%230));
    }
    return dropCnt;
}

void MainWindow::init(){
    //TODO!!!!!!!!!!!!!!!!做整个系统的初始化
    qsrand(time(NULL));
    dropCnt=0;
    memset(nowDrop,0,sizeof(nowDrop));
    for(int i=1;i<=col;++i){
        for(int j=1;j<=row;++j){
            histDrop[i][j].clear();
        }
    }
    dropColor.clear();
}

int  MainWindow::parseLine(QString str){
    //失败返回-1，否则返回该条指令的最后执行时刻，注意执行时刻大于MAXTIME时同样返回-1
    Instruction inst;
    QStringList argList = str.split(',') ;
    int time=-1, len=argList.length();
    bool ok;
    QString tmp = argList.at(0);
    time = tmp.right(tmp.length()-tmp.lastIndexOf(' ')).toInt(&ok) ;
    if(!ok) return -1;
    int ret=time+1;

    if(str.left(str.indexOf(' '))=="Move"){
        inst.opt=1;
    } else if(str.left(str.indexOf(' '))=="Split"){
        inst.opt=2;
        ret++;
    } else if(str.left(str.indexOf(' '))=="Merge"){
        inst.opt=3;
        ret++;
    } else if(str.left(str.indexOf(' '))=="Input"){
        inst.opt=4;
    } else if(str.left(str.indexOf(' '))=="Output"){
        inst.opt=5;
    } else if(str.left(str.indexOf(' '))=="Mix"){
        if(len<=1 || (len&1)==0) return -1;
        QPoint last;
        for(int i=1;i<len;i+=2){
            QPoint now;
            QString s = argList.at(i).simplified();
            if(s.endsWith(';')) s = s.left(s.length()-1);
            now.setX(s.toInt(&ok));
            if(!ok) return -1;

            s = argList.at(i+1).simplified();
            if(s.endsWith(';')) s = s.left(s.length()-1);
            now.setY(s.toInt(&ok));
            if(!ok) return -1;

            if(i!=1){
                inst.opt=1;
                inst.arg[0]=last.x();
                inst.arg[1]=last.y();
                inst.arg[2]=now.x();
                inst.arg[3]=now.y();
                if(time+i/2>MAXTIME) return -1;
                instructions[time+i/2].append(inst) ;
            }
            last=now;
        }
        ret=ret+(len-2)/2;
        inst.opt=0;
    }

    if(inst.opt!=0){
        if((inst.opt==1 && len!=5) || (inst.opt==2 && len!=7) || (inst.opt==3 && len!=5)
                || (inst.opt==4 && len!=3) || (inst.opt==5 && len!=3))
            return -1; //操作数个数不对应
        for(int i=1;i<len;++i){
            QString s = argList.at(i);
            s = s.simplified();
            if(s.endsWith(';')) s = s.left(s.length()-1);
            inst.arg[i-1] = s.toInt(&ok);
            if(!ok) return -1;
        }
        if(time>MAXTIME) return -1;
        instructions[time].append(inst) ;
    }
    return ret;
}

void MainWindow::parseFile(){
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, "错误", "打开文件失败");
        return;
    }
    //因为重新打开了文件，记得初始化!!!!
    for(int i=0;i<=timeLim;++i)
        instructions[i].clear();
    timeLim=0;
    QTextStream in(&file);
    QString line = in.readLine(); ;
    int cnt=0;
    while(!line.isNull()){
        ++cnt;
        if(line==""){
            line = in.readLine();
            continue;
        }
        int ret = parseLine(line) ;
        if(ret==-1){
            QMessageBox::critical(this, "错误", QString("第%1行指令出错").arg(cnt));
            return;
        }
        if(ret>timeLim) timeLim=ret;
        line = in.readLine();
    }
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

void MainWindow::on_actionOpenFile_triggered()
{
    filePath = QFileDialog::getOpenFileName(this, "打开文件", "./", "All files (*.*)");
    ui->labelFileName->setText(filePath.mid(filePath.lastIndexOf('/')+1,filePath.length()));
    parseFile();
    init();
}

void MainWindow::on_actionNextStep_triggered()
{
    if(timeNow==timeLim)
        return;
    Instruction inst;
    for(int i=0;i<instructions[timeNow].length();++i){
        inst = instructions[timeNow].at(i);
        if(inst.opt==1){

        } else if(inst.opt==2){

        } else if(inst.opt==3){

        } else if(inst.opt==4){

        } else if(inst.opt==5){

        }
        //TODO!!!!!!!
    }
    ui->labelCurTime->setNum(++timeNow);
}
