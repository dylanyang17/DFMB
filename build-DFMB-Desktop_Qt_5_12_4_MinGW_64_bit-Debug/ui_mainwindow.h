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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
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
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
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
        MainWindow->resize(747, 533);
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
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_2);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 747, 23));
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
        label->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\346\226\207\344\273\266:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\347\251\272", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\346\227\266\351\227\264:", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "0", nullptr));
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
