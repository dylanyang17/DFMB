/********************************************************************************
** Form generated from reading UI file 'setdfmbdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDFMBDIALOG_H
#define UI_SETDFMBDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SetDFMBDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *spinBoxCol;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBoxRow;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditInPort;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEditOutPort;
    QLabel *label_6;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SetDFMBDialog)
    {
        if (SetDFMBDialog->objectName().isEmpty())
            SetDFMBDialog->setObjectName(QString::fromUtf8("SetDFMBDialog"));
        SetDFMBDialog->resize(275, 226);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SetDFMBDialog->sizePolicy().hasHeightForWidth());
        SetDFMBDialog->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(SetDFMBDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(7);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(SetDFMBDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        spinBoxCol = new QSpinBox(SetDFMBDialog);
        spinBoxCol->setObjectName(QString::fromUtf8("spinBoxCol"));
        spinBoxCol->setMinimum(1);
        spinBoxCol->setValue(5);

        horizontalLayout_3->addWidget(spinBoxCol);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SetDFMBDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBoxRow = new QSpinBox(SetDFMBDialog);
        spinBoxRow->setObjectName(QString::fromUtf8("spinBoxRow"));
        spinBoxRow->setMinimum(1);
        spinBoxRow->setValue(5);

        horizontalLayout->addWidget(spinBoxRow);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(SetDFMBDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        lineEditInPort = new QLineEdit(SetDFMBDialog);
        lineEditInPort->setObjectName(QString::fromUtf8("lineEditInPort"));

        horizontalLayout_4->addWidget(lineEditInPort);


        verticalLayout->addLayout(horizontalLayout_4);

        label_5 = new QLabel(SetDFMBDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label_5);

        verticalSpacer_3 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(SetDFMBDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        lineEditOutPort = new QLineEdit(SetDFMBDialog);
        lineEditOutPort->setObjectName(QString::fromUtf8("lineEditOutPort"));

        horizontalLayout_5->addWidget(lineEditOutPort);


        verticalLayout->addLayout(horizontalLayout_5);

        label_6 = new QLabel(SetDFMBDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label_6);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SetDFMBDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(SetDFMBDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetDFMBDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetDFMBDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetDFMBDialog);
    } // setupUi

    void retranslateUi(QDialog *SetDFMBDialog)
    {
        SetDFMBDialog->setWindowTitle(QApplication::translate("SetDFMBDialog", "DFMB\350\256\276\347\275\256", nullptr));
        label_2->setText(QApplication::translate("SetDFMBDialog", "\345\210\227\346\225\260", nullptr));
        label->setText(QApplication::translate("SetDFMBDialog", "\350\241\214\346\225\260", nullptr));
        label_3->setText(QApplication::translate("SetDFMBDialog", "\350\276\223\345\205\245\347\253\257\345\217\243", nullptr));
        label_5->setText(QApplication::translate("SetDFMBDialog", "(\346\240\274\345\274\217\345\275\242\345\246\202\357\274\2321,5)", nullptr));
        label_4->setText(QApplication::translate("SetDFMBDialog", "\350\276\223\345\207\272\347\253\257\345\217\243", nullptr));
        label_6->setText(QApplication::translate("SetDFMBDialog", "(\346\240\274\345\274\217\345\275\242\345\246\202\357\274\2321,3;2,5;5,5)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetDFMBDialog: public Ui_SetDFMBDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDFMBDIALOG_H
