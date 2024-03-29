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
#include <QException>
#include <QSound>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    soundMove = new QSound(soundMovePath);
    soundSplit1 = new QSound(soundSplit1Path);
    soundSplit2 = new QSound(soundSplit2Path);
    soundMerge = new QSound(soundMergePath);
    gridSize=40;
    tinySize=gridSize/5;
    filePath="./";
    leftUp=QPoint(60,135);
    timeLim=timeNow=0;
    col=row=5;
    debugOn=true;
    timerPlayAll=new QTimer(this);
    timerWash=new QTimer(this);
    connect(timerPlayAll, SIGNAL(timeout()), this, SLOT(on_actionNextStep_triggered()));
    connect(timerWash, SIGNAL(timeout()), this, SLOT(washNext()));
    debugPreLoad();
    init();
    repaint();
}

void MainWindow::debugPreLoad()
{
    if(debugOn){
        int T=1;
        if(T==1){
            col=4;row=6;
            inPortStr="4,6;1,6";
            outPortStr="4,5";
            filePath=tr("E:/作业及课件/大二小学期/作业/贵系程设/Week1/Week1/Input/testcase1.txt");
        }
        parsePortStr(inPortStr, col, row);
        inPortList=tmpList;
        parsePortStr(outPortStr, col, row);
        outPortList=tmpList;
        ui->labelFileName->setText(filePath.mid(filePath.lastIndexOf('/')+1,filePath.length()));
        parseFile();
    }
}

void MainWindow::debug(QString s){
    if(debugOn){
        qDebug() << s;
    }
}

void MainWindow::debugDrop(int drop){
    if(debugOn){
        qDebug() << QString("drop: %1 RGB:(%2,%3,%4)").arg(drop).arg(dropColor.at(drop-1).red())
              .arg(dropColor.at(drop-1).green()).arg(dropColor.at(drop-1).blue());
    }
}

QPoint MainWindow::getPoint(int a, int b){
    //获得网格点的坐标，a=1且b=1时为左下角的网格点，a增大则向右移动，b增大则向上移动
    b=row+2-b; //坐标变换
    return QPoint((a-1)*gridSize+leftUp.x(), (b-1)*gridSize+leftUp.y());
}

QPoint MainWindow::getEdgeInd(QPoint p){
    //从边界的网格索引得到相邻的边界外处的网格索引
    int x=p.x();
    int y=p.y();
    if(y==row)
        return QPoint(x,y+1);
    else if(y==1)
        return QPoint(x,y-1);
    else if(x==1)
        return QPoint(x-1,y);
    else if(x==col)
        return QPoint(x+1,y);
    else {
        assert(0);
        return QPoint(-1,-1);
    }
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

int MainWindow::parsePortStr(QString portStr, int col, int row)
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
    //坐标变换在绘图时实现，其它时候都是按照题目的坐标来做的
    QPainter painter(this) ;
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    //网格线
    for(int i=1;i<=col+1;++i){
        for(int j=1;j<=row+1;++j){
            if(i!=col+1) painter.drawLine(getPoint(i,j),getPoint(i+1,j));
            if(j!=row+1) painter.drawLine(getPoint(i,j),getPoint(i,j+1));
        }
    }
    QPoint tmp = getPoint(col+1,1);
    this->setMinimumSize(tmp.x()+60, tmp.y()+60);
    this->setMaximumSize(tmp.x()+60, tmp.y()+60);

    //输入和输出端口
    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    for(int i=0;i<inPortList.length();++i){
        tmp = inPortList.at(i);
        tmp = getEdgeInd(tmp);
        tmp = getPoint(tmp.x(),tmp.y()+1) ;
        painter.drawRoundRect(tmp.x(),tmp.y(),gridSize,gridSize);
    }
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    for(int i=0;i<outPortList.length();++i){
        tmp = outPortList.at(i);
        tmp = getEdgeInd(tmp);
        tmp = getPoint(tmp.x(),tmp.y()+1) ;
        painter.drawRoundRect(tmp.x(),tmp.y(),gridSize,gridSize);
    }

    //清洗液滴的端口
    if(ui->actionWash->isChecked()){
        painter.setBrush(QBrush(QColor(100,50,80),Qt::SolidPattern));
        tmp = QPoint(0,1);
        tmp = getPoint(tmp.x(),tmp.y()+1);
        painter.drawRoundRect(tmp.x(),tmp.y(),gridSize,gridSize);
        painter.setBrush(QBrush(QColor(50,80,120),Qt::SolidPattern));
        tmp = QPoint(col+1,row);
        tmp = getPoint(tmp.x(),tmp.y()+1);
        painter.drawRoundRect(tmp.x(),tmp.y(),gridSize,gridSize);
    }

    if(timeNow==timeLim && timeNow!=0){
        //最后的显示污染次数
        int maxn=0;
        for(int i=1;i<=col;++i) for(int j=1;j<=row;++j){
            maxn = std::max(maxn, histDrop[i][j].size()) ;
        }
        for(int i=1;i<=col;++i){
            for(int j=1;j<=row;++j){
                QFont font;
                if(maxn<=99) font.setPointSize(20);
                else font.setPointSize(13);
                painter.setFont(font);
                painter.drawText(QRect(getPoint(i,j+1), getPoint(i+1,j)), Qt::AlignCenter, QString::number(histDrop[i][j].size())) ;
            }
        }

    } else{
        //液滴
        for(int i=1;i<=col;++i){
            for(int j=1;j<=row;++j){
                if(ban[i][j]){ //障碍
                    painter.setPen(Qt::red);
                    painter.drawLine(getPoint(i,j+1)+QPoint(1,1), getPoint(i+1,j)-QPoint(1,1));
                    painter.drawLine(getPoint(i+1,j+1)+QPoint(-1,1), getPoint(i,j)+QPoint(1,-1));
                    painter.setPen(Qt::black);
                }
                if(nowDrop[i][j] && !notAlone[i][j] && !midState[i][j].x()){
                    painter.setBrush(QBrush(dropColor.at(nowDrop[i][j]-1),Qt::SolidPattern));
                    tmp = getPoint(i,j+1) ;
                    painter.drawEllipse(tmp.x(),tmp.y(),gridSize,gridSize) ;
                } else if(midState[i][j].x()){
                    painter.setBrush(QBrush(dropColor.at(nowDrop[i][j]-1),Qt::SolidPattern));
                    if(midState[i][j].y()==1){
                        tmp = getPoint(i-1,j+1) ;
                        painter.drawEllipse(tmp.x()+gridSize/2, tmp.y(), gridSize*2, gridSize);
                    } else{
                        tmp = getPoint(i,j+2) ;
                        painter.drawEllipse(tmp.x(), tmp.y()+gridSize/2, gridSize, gridSize*2);
                    }
                }
                if(!nowDrop[i][j] && !notAlone[i][j]){
                    QMapIterator<int, int> it(histDrop[i][j]);
                    while(it.hasNext()){
                        if(it.next().value()>0){
                            painter.setBrush(QBrush(dropColor.at(it.key()-1),Qt::SolidPattern)) ;
                            tmp = getPoint(i,j+1) ;
                            QMap<int, QPoint>::iterator tmpIt = tinyPos[i][j].find(it.key());
                            int x,y;
                            if(tmpIt==tinyPos[i][j].end()){
                                x=rd(tmp.x(),tmp.x()+gridSize-tinySize);
                                y=rd(tmp.y(),tmp.y()+gridSize-tinySize);
                                tinyPos[i][j][it.key()] = QPoint(x,y) ;
                            } else {
                                x=(*tmpIt).x();
                                y=(*tmpIt).y();
                            }
                            painter.drawEllipse(x, y, tinySize, tinySize);
                        }
                    }
                }
            }
        }

        //清洁液滴
        if(isWashing){
            int x=washPath.first().x(), y=washPath.first().y();
            QColor color=QColor(58,159,177) ;
            painter.setBrush(QBrush(color,Qt::SolidPattern));
            tmp = getPoint(x,y+1) ;
            painter.drawEllipse(tmp.x(),tmp.y(),gridSize,gridSize) ;
        }
    }
}

int MainWindow::rd(int l,int r){
    return qrand()%(r-l+1)+l;
}

int MainWindow::newDrop(int type=0, QColor a=QColor(0,0,0), QColor b=QColor(0,0,0)){
    //返回++dropCnt，注意可能产生新颜色
    //type==0时为随机产生新颜色，type==1时为分裂a产生两种颜色，type==2时为合并a、b产生一种颜色
    ++dropCnt;
    if(dropColor.length()<dropCnt){
        if(type==1){
            int tmpRGB[3], newRGB1[3], newRGB2[3];
            tmpRGB[0]=a.red(), tmpRGB[1]=a.green(), tmpRGB[2]=a.blue();
            for(int i=0;i<3;++i){
                int tmp=tmpRGB[i];
                int rang=rd(0,std::min(tmp-20,230-tmp));
                newRGB1[i]=tmpRGB[i]-rang;
                newRGB2[i]=tmpRGB[i]+rang;
                if(rd(0,1)) std::swap(newRGB1[i],newRGB2[i]);
            }
            dropColor.append(QColor(newRGB1[0],newRGB1[1],newRGB1[2]));
            dropColor.append(QColor(newRGB2[0],newRGB2[1],newRGB2[2]));
            debugDrop(dropCnt++);
        } else if(type==2){
            dropColor.append(QColor((a.red()+b.red())/2,(a.green()+b.green())/2,(a.blue()+b.blue())/2));
        }
        else    dropColor.append(QColor(qrand()%200+25,qrand()%200+25,qrand()%200+25));
    } else if(type==1) ++dropCnt;
    debugDrop(dropCnt);
    return dropCnt;
}

void MainWindow::init(){
    //TODO!!!!!!!!!!!!!!!!做整个系统的初始化
    qsrand(time(NULL));
    ui->labelCurTime->setNum(timeNow=0);
    isWashing=false;
    playingAll=false;
    timerPlayAll->stop();
    timerWash->stop();
    memset(ban, 0, sizeof(ban)) ;
    ui->actionNextStep->setEnabled(true);
    on_actionPause_triggered();
    dropCnt=0;
    memset(notAlone,0,sizeof(notAlone));
    memset(midState,0,sizeof(midState));
    memset(nowDrop,0,sizeof(nowDrop));
    disapDropStack.clear();
    for(int i=1;i<=col;++i){
        for(int j=1;j<=row;++j){
            histDrop[i][j].clear();
            tinyPos[i][j].clear();
        }
    }
    dropColor.clear();
    repaint();
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
                instructions[time+i/2-1].append(inst) ;
                lastVis[now.x()][now.y()]=std::max(lastVis[now.x()][now.y()],time+i/2);
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

        //处理lastVis
        if(inst.opt==1){
            lastVis[inst.arg[2]][inst.arg[3]] = std::max(lastVis[inst.arg[2]][inst.arg[3]], time+1);
        } else if(inst.opt==2){
            lastVis[inst.arg[0]][inst.arg[1]] = std::max(lastVis[inst.arg[0]][inst.arg[1]], time+1);
            lastVis[inst.arg[2]][inst.arg[3]] = std::max(lastVis[inst.arg[2]][inst.arg[3]], time+2);
            lastVis[inst.arg[4]][inst.arg[5]] = std::max(lastVis[inst.arg[4]][inst.arg[5]], time+2);
        } else if(inst.opt==3){
            lastVis[inst.arg[0]][inst.arg[1]] = std::max(lastVis[inst.arg[0]][inst.arg[1]], time+1);
            lastVis[inst.arg[2]][inst.arg[3]] = std::max(lastVis[inst.arg[2]][inst.arg[3]], time+1);
            int x=(inst.arg[0]+inst.arg[2])/2, y=(inst.arg[1]+inst.arg[3])/2;
            lastVis[x][y] = std::max(lastVis[x][y], time+2);
        } else if(inst.opt==4){
            lastVis[inst.arg[0]][inst.arg[1]] = std::max(lastVis[inst.arg[0]][inst.arg[1]], time+1);
        }
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
    memset(lastVis,0,sizeof(lastVis));
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

bool isOnEdge(QPoint p, int col, int row);

void MainWindow::autoSet(){
    int maxCol=0, maxRow=0;
    for(int i=0;i<=timeLim;++i){
        for(int j=0;j<instructions[i].length();++j){
            Instruction inst = instructions[i].at(j);
            for(int k=0;k<6;k+=2)
                maxCol=std::max(maxCol, inst.arg[k]);
            for(int k=1;k<6;k+=2)
                maxRow=std::max(maxRow, inst.arg[k]);
        }
    }
    for(int i=0;i<=timeLim;++i){
        for(int j=0;j<instructions[i].length();++j){
            Instruction inst = instructions[i].at(j);
            if(inst.opt==4 || inst.opt==5){
                if(!isOnEdge(QPoint(inst.arg[0],inst.arg[1]),maxCol,maxRow)){
                    QMessageBox::critical(this, "自动配置失败", QString("端口无法设定在边界上")) ;
                    return ;
                }
            }
        }
    }
    col=maxCol; row=maxRow;
    inPortStr=outPortStr="";
    inPortList.clear();
    outPortList.clear();
    for(int i=0;i<=timeLim;++i){
        for(int j=0;j<instructions[i].length();++j){
            Instruction inst = instructions[i].at(j);
            if(inst.opt==4){
                QPoint p=QPoint(inst.arg[0],inst.arg[1]);
                if(inPortList.indexOf(p)==-1){
                    inPortList.append(p);
                    if(inPortList.length()>1) inPortStr=inPortStr+';';
                    inPortStr=inPortStr+QString("%1,%2").arg(p.x()).arg(p.y());
                }
            } else if(inst.opt==5){
                QPoint p=QPoint(inst.arg[0],inst.arg[1]);
                if(outPortList.indexOf(p)==-1){
                    if(outPortList.length()!=0){
                        QMessageBox::critical(this, "自动配置失败", QString("出现多个输出端口")) ;
                        return ;
                    }
                    outPortList.append(p);
                    outPortStr=QString("%1,%2").arg(p.x()).arg(p.y());
                }
            }
        }
    }
}

void MainWindow::on_actionSetDFMB_triggered()
{
    setdfmbdialog = new SetDFMBDialog(this, col, row, inPortStr, outPortStr, this);
    setdfmbdialog -> show();
}

void MainWindow::openFileWithPath(QString path){
    ui->labelFileName->setText(path.mid(path.lastIndexOf('/')+1,path.length()));
    parseFile();
    if(ui->actionAutoSet->isChecked()){
        autoSet();
    }
    init();
}

void MainWindow::on_actionOpenFile_triggered()
{
    filePath = QFileDialog::getOpenFileName(this, "打开文件", filePath.mid(0, filePath.lastIndexOf('/')+1), "All files (*.*)");
    openFileWithPath(filePath);
}

int MainWindow::getMidState(int x1, int y1, int x2, int y2){
    //输入x1,y1和x2,y2，保证这两个点其中有一个是中间点，判断为水平(1)还是竖直(2)
    if(abs(x1-x2)==1){
        return 1;
    } else return 2;
}

void MainWindow::instMove(int x1, int y1,int x2, int y2, bool rev){
    //从x1,y1移动到x2,y2，rev为true时表明撤销移动
    if(ui->actionSound->isChecked()) soundMove->play();
    if(!rev) {
        int drop=nowDrop[x1][y1];
        nowDrop[x2][y2] = drop ;
        nowDrop[x1][y1] = 0;
        histDrop[x2][y2][drop] = histDrop[x2][y2][drop]+1;
    }
    else {
        int drop=nowDrop[x2][y2];
        histDrop[x2][y2][drop] = histDrop[x2][y2][drop]-1;
        nowDrop[x1][y1] = drop;
        nowDrop[x2][y2] = 0;
    }
}

void MainWindow::instSplit1(int x1, int y1,int x2, int y2, int x3, int y3, bool rev){
    //从x1,y1分裂到x2,y2和x3,y3，rev为true时表明撤销分裂的首步
    if(ui->actionSound->isChecked()) soundSplit1->play();
    if(!rev){
        nowDrop[x2][y2] = newDrop(1, dropColor.at(nowDrop[x1][y1]-1))-1;
        nowDrop[x3][y3] = dropCnt;
        histDrop[x2][y2][nowDrop[x2][y2]] = histDrop[x2][y2][nowDrop[x2][y2]]+1;
        histDrop[x3][y3][nowDrop[x3][y3]] = histDrop[x3][y3][nowDrop[x3][y3]]+1;
        notAlone[x2][y2] = notAlone[x3][y3] = true;
        midState[x1][y1] = QPoint(1, getMidState(x1,y1,x2,y2));
    } else{
        midState[x1][y1] = QPoint(0,0);
        notAlone[x2][y2] = notAlone[x3][y3] = false;
        histDrop[x3][y3][nowDrop[x3][y3]] = histDrop[x3][y3][nowDrop[x3][y3]]-1;
        histDrop[x2][y2][nowDrop[x2][y2]] = histDrop[x2][y2][nowDrop[x2][y2]]-1;
        nowDrop[x2][y2] = nowDrop[x3][y3] = 0;
        dropCnt-=2;
    }
}

void MainWindow::instMerge1(int x1, int y1, int x2, int y2, int x3, int y3, bool rev){
    //从x1,y1和x2,y2合并到x3,y3，rev为true是表示撤销合并的首步
    if(!rev){
        nowDrop[x3][y3] = newDrop(2, dropColor.at(nowDrop[x1][y1]-1), dropColor.at(nowDrop[x2][y2]-1));
        histDrop[x3][y3][nowDrop[x3][y3]] = histDrop[x3][y3][nowDrop[x3][y3]]+1;
        notAlone[x1][y1] = notAlone[x2][y2] = true;
        midState[x3][y3] = QPoint(2,getMidState(x2,y2,x3,y3));
    } else{
        midState[x3][y3] = QPoint(0,0);
        notAlone[x1][y1] = notAlone[x2][y2] = false;
        histDrop[x3][y3][nowDrop[x3][y3]] = histDrop[x3][y3][nowDrop[x3][y3]]-1;
        nowDrop[x3][y3] = 0;
        dropCnt--;
    }
}

void MainWindow::instSplit2(int x1, int y1,int x2, int y2, int x3, int y3, bool rev){
    //从x1,y1分裂到x2,y2和x3,y3，rev为true时表明撤销分裂的第二步
    if(ui->actionSound->isChecked()) soundSplit2->play();
    if(!rev){
        disapDropStack.push(nowDrop[x1][y1]);
        nowDrop[x1][y1]=0;
        notAlone[x2][y2]=notAlone[x3][y3]=false;
        midState[x1][y1]=QPoint(0,0);
    } else {
        midState[x1][y1]=QPoint(1,getMidState(x1,y1,x2,y2));
        notAlone[x2][y2]=notAlone[x3][y3]=true;
        nowDrop[x1][y1]=disapDropStack.top();
        disapDropStack.pop();
    }
}

void MainWindow::instMerge2(int x1, int y1, int x2, int y2, int x3, int y3, bool rev){
    //从x1,y1和x2,y2合并到x3,y3，rev为true是表示撤销合并的第二步
   if(ui->actionSound->isChecked()) soundMerge->play();
    if(!rev){
        disapDropStack.push(nowDrop[x1][y1]);
        disapDropStack.push(nowDrop[x2][y2]);
        nowDrop[x1][y1]=nowDrop[x2][y2]=0;
        notAlone[x1][y1]=notAlone[x2][y2]=false;
        midState[x3][y3]=QPoint(0,0);
    } else {
        midState[x3][y3]=QPoint(2,getMidState(x2,y2,x3,y3));
        notAlone[x1][y1]=notAlone[x2][y2]=true;
        nowDrop[x2][y2]=disapDropStack.top();
        disapDropStack.pop();
        nowDrop[x1][y1]=disapDropStack.top();
        disapDropStack.pop();
    }
}

int MainWindow::instInput(int x1, int y1, bool rev){
    //输入到x1,y1，rev为true表示撤销输入
    if(inPortList.indexOf(QPoint(x1,y1))==-1)
        return -1;
    if(!rev){
        nowDrop[x1][y1] = newDrop();
        histDrop[x1][y1][nowDrop[x1][y1]] = histDrop[x1][y1][nowDrop[x1][y1]]+1;
    } else {
        histDrop[x1][y1][nowDrop[x1][y1]] = histDrop[x1][y1][nowDrop[x1][y1]]-1;
        nowDrop[x1][y1] = 0;
        --dropCnt;
    }
    return 0;
}

int MainWindow::instOutput(int x1, int y1, bool rev){
    //从x1,y1输出，rev为true表示撤销输出
    if(outPortList.indexOf(QPoint(x1,y1))==-1)
        return -1;
    if(!rev){
        disapDropStack.push(nowDrop[x1][y1]);
        nowDrop[x1][y1] = 0;
    } else{
        nowDrop[x1][y1] = disapDropStack.top();
        disapDropStack.pop();
    }
    return 0;
}

void MainWindow::handleInst(Instruction inst, bool rev){
    //处理指令，rev为true表示撤销指令
    if(inst.opt==1){
        int x1=inst.arg[0], y1=inst.arg[1], x2=inst.arg[2], y2=inst.arg[3];
        instMove(x1,y1,x2,y2,rev);
    } else if(inst.opt==2){
        int x1=inst.arg[0], y1=inst.arg[1], x2=inst.arg[2], y2=inst.arg[3],
                x3=inst.arg[4], y3=inst.arg[5];
        instSplit1(x1,y1,x2,y2,x3,y3,rev);
    } else if(inst.opt==3){
        int x1=inst.arg[0], y1=inst.arg[1], x2=inst.arg[2], y2=inst.arg[3],
             x3=(x1+x2)/2, y3=(y1+y2)/2;
        instMerge1(x1,y1,x2,y2,x3,y3,rev);
    } else if(inst.opt==4){
        int x1=inst.arg[0], y1=inst.arg[1];
        if(instInput(x1,y1,rev)==-1)
            throw 1;
    } else if(inst.opt==5){
        int x1=inst.arg[0], y1=inst.arg[1];
        if(instOutput(x1,y1,rev)==-1)
            throw 2;
    } else if(inst.opt==6){
        int x1=inst.arg[0], y1=inst.arg[1], x2=inst.arg[2], y2=inst.arg[3],
                x3=inst.arg[4], y3=inst.arg[5];
        instSplit2(x1,y1,x2,y2,x3,y3,rev);
    } else if(inst.opt==7){
        int x1=inst.arg[0], y1=inst.arg[1], x2=inst.arg[2], y2=inst.arg[3],
             x3=(x1+x2)/2, y3=(y1+y2)/2;
        instMerge2(x1,y1,x2,y2,x3,y3,rev);
    }
}

void MainWindow::handleMid(bool rev){
    //处理中间态，当rev为true时逆向处理中间态（即生成中间态）
    if(timeNow==0) return;
    if(!rev){
        for(int i=0;i<instructions[timeNow-1].length();++i){
            Instruction inst = instructions[timeNow-1].at(i);
            if(inst.opt==2){
                inst.opt=6;
                handleInst(inst, rev);
            } else if(inst.opt==3){
                inst.opt=7;
                handleInst(inst, rev);
            }
        }
    } else{
        for(int i=instructions[timeNow-1].length()-1;i>=0;--i){
            Instruction inst = instructions[timeNow-1].at(i);
            if(inst.opt==2){
                inst.opt=6;
                handleInst(inst, rev);
            } else if(inst.opt==3){
                inst.opt=7;
                handleInst(inst, rev);
            }
        }
    }
}

bool MainWindow::outGridRange(QPoint a){
    //判断a格子是否出界
    int x=a.x(), y=a.y();
    return x<1||y<1||x>col||y>row ;
}

bool MainWindow::washCheckPoint(QPoint a){
    //清洗模式下判断能否走a格子
    int x=a.x(), y=a.y();
    if(outGridRange(a)||ban[x][y]) return false;
    for(int i=0;i<BANDIRNUM;++i){
        int tx=x+dir[i][0], ty=y+dir[i][1];
        if(!outGridRange(QPoint(tx,ty)) && nowDrop[tx][ty]) return false;
    }
    return true;
}

void MainWindow::washAddPath(QPoint s, QPoint t){
    //已经以s为起点BFS过了，现在将s到t的路径加入到washPath
    if(s==t) return ;
    washAddPath(s, bfsPre[t.x()][t.y()]);
    washPath.push_back(t);
    washFlag[t.x()][t.y()]=true;
}

bool MainWindow::washCheckNeed(QPoint s){
    //判断s是否为没有被加入washPath的必要清洗格子
    int x=s.x(), y=s.y();
    return lastVis[x][y]>timeNow && !washFlag[x][y] && histDrop[x][y].size()>0 ;
}

QPoint MainWindow::washBFS(QPoint s, bool *ok){
    //从s点开始BFS，返回最靠近的必要清洗格子或是(col,row)，注意若不能到达(col,row)则返回QPoint(-1,-1)
    //ok为true表示找到了必要清洗格子（这是为了处理(col,row)恰好是必要清洗格子的情况）
    bfsQue.clear();
    bfsQue.push_back(s);
    memset(bfsDis,0,sizeof(bfsDis));
    bfsDis[s.x()][s.y()]=1;
    QPoint ret=QPoint(-1,-1);
    *ok = false;
    while(!bfsQue.empty()){
        QPoint a=bfsQue.first();
        bfsQue.pop_front();
        for(int i=0;i<MOVEDIRNUM;++i){
            int x=a.x()+dir[i][0], y=a.y()+dir[i][1];
            if(!washCheckPoint(QPoint(x,y))) continue ;
            if(!bfsDis[x][y]){
                bfsDis[x][y]=bfsDis[a.x()][a.y()]+1;
                bfsPre[x][y]=a;
                bfsQue.push_back(QPoint(x,y));
                if(washCheckNeed(QPoint(x,y)) && ret==QPoint(-1,-1)){
                    ret = QPoint(x,y);
                    *ok = true;
                }
            }
        }
    }
    if(bfsDis[col][row] && ret==QPoint(-1,-1)) ret = QPoint(col,row);
    if(ret!=QPoint(-1,-1)) washAddPath(s,ret);
    return ret;
}

bool MainWindow::wash(){
    //用于做单步下的清洗，返回值表示这一步是否进行清洗
    washPath.clear();
    memset(washFlag,false,sizeof(washFlag));
    washPath.push_back(QPoint(1,1));
    if(washCheckPoint(QPoint(1,1))==false) return false;
    QPoint now=QPoint(1,1);
    bool ok=true;
    bool has=false;
    while(ok){
        now = washBFS(now, &ok);
        if(ok) has=true;
        if(now==QPoint(-1,-1)) return false;
    }
    return has;
}

void MainWindow::washNext(){
    washPath.pop_front();
    if(washPath.empty()){
        ui->actionNextStep->setEnabled(true);
        timerWash->stop();
        isWashing=false;
    } else{
        QPoint a=washPath.first();
        histDrop[a.x()][a.y()].clear();
    }
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton){
        int x=event->x(), y=event->y();
        x = (x-leftUp.x())/gridSize+1;
        y = (y-leftUp.y())/gridSize+1;
        y = row-y+1;
        if(x>=1 && x<=col && y>=1 && y<=row){
            ban[x][y]^=1;
        }
        update();
    }
}

void MainWindow::on_actionNextStep_triggered()
{
    if(!playingAll && ui->actionNextStep->isEnabled()==false) return;
    if(timeNow==timeLim){
        on_actionPause_triggered();
        return;
    }
    ui->actionNextStep->setEnabled(false);
    int tmpDrop[MAXN][MAXN];
    QPoint tmpMidState[MAXN][MAXN];
    memcpy(tmpDrop, nowDrop, sizeof(tmpDrop));
    memcpy(tmpMidState, midState, sizeof(tmpMidState));
    Instruction inst;
    int failCnt=0;
    for(int i=1;i<=col;++i){
        for(int j=1;j<=row;++j){
            if(histDrop[i][j].size()>1){
                failCnt++;
            }
        }
    }
    //处理midState（实际上一个更优的做法是直接把合并和分裂都拆成两条来做）
    handleMid(false);

    //处理指令
    int now;
    try {
        for(now=0;now<instructions[timeNow].length();++now){
            handleInst(instructions[timeNow].at(now), false);
        }
        for(int x1=1;x1<=col;++x1){
            for(int y1=1;y1<=row;++y1){
                if(nowDrop[x1][y1] && !midState[x1][y1].x()){
                    for(int d=0;d<BANDIRNUM;++d){
                        int x2=x1+dir[d][0], y2=y1+dir[d][1];
                        if(x2<1||y2<1||x2>col||y2>row||midState[x2][y2].x()) continue;
                        if(nowDrop[x2][y2] && nowDrop[x2][y2]!=nowDrop[x1][y1]) {
                            qDebug() << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
                            throw 3;
                        }
                        if(tmpDrop[x2][y2] && tmpDrop[x2][y2]!=nowDrop[x1][y1] && !tmpMidState[x2][y2].x() && tmpMidState[x1][y1].y()!=d/2+1) {
                            //qDebug() << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
                            //qDebug() << tmpMidState[x1][y1].x() << ' ' << d << ' ' << tmpMidState[x2][y2].x() << '\n' ;
                            throw 4;
                        }
                    }
                }
            }
        }
    } catch (int a) {
        if(a==1){
            QMessageBox::critical(this, "错误", "输入不在端口相邻处");
        } else if(a==2){
            QMessageBox::critical(this, "错误", "输出不在端口相邻处");
        } else if(a==3){
            QMessageBox::critical(this, "错误", "不满足静态约束");
        } else if(a==4){
            QMessageBox::critical(this, "错误", "不满足动态约束");
        }
        for(now=now-1;now>=0;--now){
            handleInst(instructions[timeNow].at(now), true);
        }
        handleMid(true);
        repaint();
        on_actionPause_triggered();
        return;
    }

    ui->labelCurTime->setNum(++timeNow);
    repaint();

    for(int i=1;i<=col;++i){
        for(int j=1;j<=row;++j){
            if(histDrop[i][j].size()>1){
                failCnt--;
            }
        }
    }
    if(failCnt<0 && ui->actionWash->isChecked()) QMessageBox::warning(this, "警告", "清洗失败，液滴出现污染", "忽略");

    //清洗
    if(ui->actionWash->isChecked()){
        if(wash()){
            timerWash->start(40);
            isWashing=true;
            histDrop[1][1].clear();
            return;
        }
    }

    if(!playingAll) ui->actionNextStep->setEnabled(true);
}

void MainWindow::on_actionPreviousStep_triggered()
{
    if(timeNow==0)
        return;
    Instruction inst;
    ui->labelCurTime->setNum(--timeNow);

    //处理指令
    int now;
    for(now=instructions[timeNow].length()-1;now>=0;--now){
        handleInst(instructions[timeNow].at(now), true);
    }

    //处理midState
    handleMid(true);
    repaint();
}

void MainWindow::on_actionReset_triggered()
{
    init();
}

void MainWindow::on_actionPlayAll_triggered()
{
    playingAll=true;
    timerPlayAll->start(1000);
    ui->actionNextStep->setEnabled(false);
    ui->actionPreviousStep->setEnabled(false);
}

void MainWindow::on_actionPause_triggered()
{
    playingAll=false;
    timerPlayAll->stop();
    ui->actionNextStep->setEnabled(true);
    if(!ui->actionWash->isChecked()) ui->actionPreviousStep->setEnabled(true);
}

void MainWindow::on_actionWash_triggered()
{
    init();
    if(!ui->actionWash->isChecked()){
        ui->actionRoute->setChecked(false);
        ui->actionPreviousStep->setEnabled(true);
    } else{
        ui->actionPreviousStep->setEnabled(false);
    }
    repaint();
}

void MainWindow::on_actionRoute_triggered()
{
    if(ui->actionRoute->isChecked()){
        ui->actionWash->setChecked(true);
        //TODO
    }
}
