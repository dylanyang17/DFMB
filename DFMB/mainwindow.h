#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
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

    const static int MAXTIME=10000;

    QPoint getPoint(int a, int b);
    int getCol();
    int getRow();
    QString getInPortStr();
    QString getOutPortStr();
    void setCol(int col);
    void setRow(int row);
    void setInPortStr(QString inPortStr);
    void setOutPortStr(QString outPortStr);
    int parsePortStr(QString portStr) ;
    QList<QPoint> tmpList;
    QList<QPoint> inPortList;
    QList<QPoint> outPortList;

    QPoint getMidPoint(int a, int b);
    QPoint getEdgeInd(QPoint p);
    void parseFile();
    int parseLine(QString str);
    void toIntError(bool ok);
private slots:

    void on_actionSetDFMB_triggered();

    void on_actionOpenFile_triggered();

private:
    Ui::MainWindow *ui;
    SetDFMBDialog *setdfmbdialog;

    int gridSize, col, row, timeLim;
    QString inPortStr, outPortStr, filePath;
    QList<Instruction> instructions[MAXTIME+5];
    QPoint leftUp;
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
