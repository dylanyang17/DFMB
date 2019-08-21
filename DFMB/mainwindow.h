#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QStack>
#include "setdfmbdialog.h"

namespace Ui {
class MainWindow;
}

struct Instruction{
    int opt, arg[6];

    Instruction(int _opt=0, int _arg0=0, int _arg1=0, int _arg2=0, int _arg3=0, int _arg4=0, int _arg5=0){
        opt=_opt, arg[0]=_arg0, arg[1]=_arg1, arg[2]=_arg2, arg[3]=_arg3, arg[4]=_arg4, arg[5]=_arg5;
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

    QPoint getMidPoint(int a, int b);
    QPoint getEdgeInd(QPoint p);
    void parseFile();
    int parseLine(QString str);
    void toIntError(bool ok);
    void init();
    int newDrop();
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
private slots:

    void on_actionSetDFMB_triggered();

    void on_actionOpenFile_triggered();

    void on_actionNextStep_triggered();

    void on_actionPreviousStep_triggered();

    void on_actionReset_triggered();

    void on_actionPlayAll_triggered();

    void on_actionPause_triggered();

private:
    Ui::MainWindow *ui;
    SetDFMBDialog *setdfmbdialog;

    int gridSize, col, row, timeLim, timeNow, dropCnt;
    QString inPortStr, outPortStr, filePath;
    QList<Instruction> instructions[MAXTIME+5];
    int nowDrop[MAXN][MAXN];               //某个格子当前的液滴标号
    QMap<int, int> histDrop[MAXN][MAXN];   //某个格子被某液滴经过了多少次
    QList<QColor> dropColor;               //记录每个液滴的颜色
    QPoint midState[MAXN][MAXN];           //标记中间结点，第一个参数为0表示不在中间状态，为1表示正在分裂，为2表示正在合并，
                                           //第二个参数为1表示水平中间结点，2表示垂直中间结点
    bool notAlone[MAXN][MAXN];             //标记不单独画出的格子
    QStack<int> disapDropStack;            //消失的液滴栈
    QPoint leftUp;
    QTimer *timerPlayAll;
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
