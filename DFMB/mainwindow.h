#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QMap>
#include <QSound>
#include <QTimer>
#include <QQueue>
#include <QStack>
#include "setdfmbdialog.h"

namespace Ui {
class MainWindow;
}

struct Instruction{
    int opt, arg[6];

    Instruction(int _opt=0, int _arg0=0, int _arg1=0, int _arg2=0, int _arg3=0, int _arg4=0, int _arg5=0){
        opt=_opt; arg[0]=_arg0; arg[1]=_arg1; arg[2]=_arg2; arg[3]=_arg3; arg[4]=_arg4; arg[5]=_arg5;
    }
};

struct RouteInstruction{
    int opt;
    QList<int> args;

    RouteInstruction(int _opt=0, QList<int> _args = QList<int>()){
        opt=_opt; args=_args;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool debugOn;
    const static int MAXTIME=10000; //时间上界
    const static int MAXN=105;      //长宽上界
    const static int MAXM=10000;     //液滴上界
    const static int BANDIRNUM=8;   //约束的八个方向
    const static int MOVEDIRNUM=4;  //移动的四个方向
    int dir[BANDIRNUM][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}} ;
    QPoint getPoint(int a, int b);
    int getCol();
    int getRow();
    QString getInPortStr();
    QString getOutPortStr();
    void setCol(int col);
    void setRow(int row);
    void setInPortStr(QString inPortStr);
    void setOutPortStr(QString outPortStr);
    int parsePortStr(QString portStr, int col, int row) ;
    QList<QPoint> tmpList;
    QList<QPoint> inPortList;
    QList<QPoint> outPortList;

    QPoint getEdgeInd(QPoint p);
    int parseFile();
    int parseLine(QString str);
    void toIntError(bool ok);
    void init();
    int newDrop(int type, QColor a, QColor b);
    int getMidState(int x1, int y1, int x2, int y2);
    void handleMid(bool rev);
    void instMove(int x1, int y1, int x2, int y2, bool rev);
    void instSplit1(int x1, int y1, int x2, int y2, int x3, int y3, bool rev);
    void instMerge1(int x1, int y1, int x2, int y2, int x3, int y3, bool rev);
    int instInput(int x1, int y1, bool rev);
    int instOutput(int x1, int y1, bool rev);
    void handleInst(Instruction inst, bool rev);
    void instSplit2(int x1, int y1, int x2, int y2, int x3, int y3, bool rev);
    void instMerge2(int x1, int y1, int x2, int y2, int x3, int y3, bool rev);
    void debug(QString s);
    void debugDrop(int drop);
    void autoSet();
    void openFileWithPath(QString path);
    int rd(int l, int r);
    void mousePressEvent(QMouseEvent *event);
    QPoint washBFS(QPoint s, bool *ok);
    bool outGridRange(QPoint a);
    bool washCheckPoint(QPoint a);
    void washAddPath(QPoint s, QPoint t);
    bool wash();
    bool washCheckNeed(QPoint s);
    void routeNextStep();
    void routeInit();
    void routeParseFile();
    void routeParseLine(QString str);
private slots:

    void on_actionSetDFMB_triggered();

    void on_actionOpenFile_triggered();

    void on_actionNextStep_triggered();

    void on_actionPreviousStep_triggered();

    void on_actionReset_triggered();

    void on_actionPlayAll_triggered();

    void on_actionPause_triggered();

    void on_actionWash_triggered();

    void on_actionRoute_triggered();

    void washNext();

private:
    Ui::MainWindow *ui;
    SetDFMBDialog *setdfmbdialog;

    int tinySize, gridSize, col, row, timeLim, timeNow, dropCnt;
    const QString soundDir="res\\", soundMovePath=soundDir+"move.wav",
            soundSplit1Path=soundDir+"split1.wav", soundSplit2Path=soundDir+"split2.wav",
            soundMergePath=soundDir+"merge.wav";
    QSound *soundMove, *soundSplit1, *soundSplit2, *soundMerge;
    QString inPortStr, outPortStr, filePath;
    QList<Instruction> instructions[MAXTIME+5];
    int nowDrop[MAXN][MAXN];               //某个格子当前的液滴标号
    QMap<int, int> histDrop[MAXN][MAXN];   //某个格子被某液滴经过了多少次
    QList<QColor> dropColor;               //记录每个液滴的颜色
    QPoint midState[MAXN][MAXN];           //标记中间结点，第一个参数为0表示不在中间状态，为1表示正在分裂，为2表示正在合并，
                                           //第二个参数为1表示水平中间结点，2表示垂直中间结点
    bool notAlone[MAXN][MAXN];             //标记不单独画出的格子
    QStack<int> disapDropStack;            //消失的液滴栈
    QMap<int, QPoint> tinyPos[MAXN][MAXN]; //某个格子对于各种颜色标记的小圆位置
    bool ban[MAXN][MAXN];                  //记录是否设置障碍
    QQueue<QPoint> washPath;               //记录清洁液滴的路径
    QQueue<QPoint> bfsQue;                 //BFS队列
    int bfsDis[MAXN][MAXN];                //BFS中的距离
    QPoint bfsPre[MAXN][MAXN];             //BFS路径中的前一位置
    int lastVis[MAXN][MAXN];               //记录每个格子最后被液滴访问的时刻
    bool washFlag[MAXN][MAXN];             //是否已经被当前的washPath覆盖
    bool isWashing;                        //记录是否正在清洗
    QTimer *timerWash;                     //清洗时的计时器
    QTimer *timerPlayAll;                  //全部播放时的计时器
    QPoint leftUp;                         //左上角坐标
    bool playingAll;                       //正在播放全部


    //For route

    //预处理用
    int routeNowDrop[MAXN][MAXN];                               //记录每个位置的液滴编号
    QList<RouteInstruction> routeInstructions[MAXTIME+5];       //存储route模式格式的指令

    //其它变量
    int routeDropNum;                                           //不同的液滴总数
    int routeInPortOfDrop[MAXM+5], routeOutPortOfDrop[MAXM+5];  //记录每个液滴的输入/出端口编号，**注意在index的基础上加了1**
    QList<QPoint> routeInPort, routeOutPort;                    //记录第i个输入/出端口所在位置
    QPoint routeWashInPort, routeWashOutPort;                   //记录清洗液滴的入口和出口

    void paintEvent(QPaintEvent *);
    void debugPreLoad();
};

#endif // MAINWINDOW_H
