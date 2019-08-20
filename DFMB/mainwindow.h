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
    int opt, arg1, arg2, arg3, arg4, arg5, arg6;

    Instruction(int _opt=0, int _arg1=0, int _arg2=0, int _arg3=0, int _arg4=0, int _arg5=0, int _arg6=0){
        opt=_opt, arg1=_arg1, arg2=_arg2, arg3=_arg3, arg4=_arg4, arg5=_arg5, arg6=_arg6;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
private slots:

    void on_actionSetDFMB_triggered();

    void on_actionOpenFile_triggered();

private:
    Ui::MainWindow *ui;
    SetDFMBDialog *setdfmbdialog;

    int gridSize, col, row;
    QString inPortStr, outPortStr, filePath;
    QList<Instruction> instructions[10005];
    QPoint leftUp;
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
