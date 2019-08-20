/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionReset;
    QAction *actionOpenFile;
    QAction *actionPreviousStep;
    QAction *actionNextStep;
    QAction *actionPlayAll;
    QAction *actionSound;
    QAction *actionWash;
    QAction *actionSetDFMB;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuTEST;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 550);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionOpenFile = new QAction(MainWindow);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        actionPreviousStep = new QAction(MainWindow);
        actionPreviousStep->setObjectName(QString::fromUtf8("actionPreviousStep"));
        actionNextStep = new QAction(MainWindow);
        actionNextStep->setObjectName(QString::fromUtf8("actionNextStep"));
        actionPlayAll = new QAction(MainWindow);
        actionPlayAll->setObjectName(QString::fromUtf8("actionPlayAll"));
        actionSound = new QAction(MainWindow);
        actionSound->setObjectName(QString::fromUtf8("actionSound"));
        actionSound->setCheckable(true);
        actionWash = new QAction(MainWindow);
        actionWash->setObjectName(QString::fromUtf8("actionWash"));
        actionWash->setCheckable(true);
        actionSetDFMB = new QAction(MainWindow);
        actionSetDFMB->setObjectName(QString::fromUtf8("actionSetDFMB"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 750, 23));
        menuTEST = new QMenu(menuBar);
        menuTEST->setObjectName(QString::fromUtf8("menuTEST"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuTEST->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuTEST->addAction(actionOpenFile);
        menu->addAction(actionReset);
        menu->addAction(actionPreviousStep);
        menu->addAction(actionNextStep);
        menu->addAction(actionPlayAll);
        menu_2->addAction(actionSound);
        menu_2->addAction(actionWash);
        menu_2->addSeparator();
        menu_2->addAction(actionSetDFMB);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DFMB\346\250\241\346\213\237\347\263\273\347\273\237", nullptr));
        actionReset->setText(QApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        actionOpenFile->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        actionPreviousStep->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\346\255\245", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPreviousStep->setShortcut(QApplication::translate("MainWindow", "F3", nullptr));
#endif // QT_NO_SHORTCUT
        actionNextStep->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\346\255\245", nullptr));
#ifndef QT_NO_SHORTCUT
        actionNextStep->setShortcut(QApplication::translate("MainWindow", "F4", nullptr));
#endif // QT_NO_SHORTCUT
        actionPlayAll->setText(QApplication::translate("MainWindow", "\345\205\250\351\203\250\346\222\255\346\224\276", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPlayAll->setShortcut(QApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_NO_SHORTCUT
        actionSound->setText(QApplication::translate("MainWindow", "\351\237\263\346\225\210", nullptr));
        actionWash->setText(QApplication::translate("MainWindow", "\346\270\205\346\264\227", nullptr));
        actionSetDFMB->setText(QApplication::translate("MainWindow", "DFMB\350\256\276\347\275\256", nullptr));
        menuTEST->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\351\200\211\351\241\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
