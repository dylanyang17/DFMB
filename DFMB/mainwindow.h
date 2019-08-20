#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include "setdfmbdialog.h"

namespace Ui {
class MainWindow;
}

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
private slots:

    void on_actionSetDFMB_triggered();

private:
    Ui::MainWindow *ui;
    SetDFMBDialog *setdfmbdialog;

    int gridSize, col, row;
    QString inPortStr, outPortStr;
    QPoint leftUp;
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
