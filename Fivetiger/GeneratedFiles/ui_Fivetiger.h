/********************************************************************************
** Form generated from reading UI file 'Fivetiger.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIVETIGER_H
#define UI_FIVETIGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FivetigerClass
{
public:
    QAction *acToSelfPlay;
    QAction *action;
    QAction *acEasy;
    QAction *acMid;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *lblFGoal;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *lblDGoal;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *lblcurrentFlag;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *lblPhrase;
    QLabel *lblInfo;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_3;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FivetigerClass)
    {
        if (FivetigerClass->objectName().isEmpty())
            FivetigerClass->setObjectName(QStringLiteral("FivetigerClass"));
        FivetigerClass->resize(743, 566);
        acToSelfPlay = new QAction(FivetigerClass);
        acToSelfPlay->setObjectName(QStringLiteral("acToSelfPlay"));
        action = new QAction(FivetigerClass);
        action->setObjectName(QStringLiteral("action"));
        acEasy = new QAction(FivetigerClass);
        acEasy->setObjectName(QStringLiteral("acEasy"));
        acMid = new QAction(FivetigerClass);
        acMid->setObjectName(QStringLiteral("acMid"));
        centralWidget = new QWidget(FivetigerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(560, 80, 130, 291));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lblFGoal = new QLabel(layoutWidget);
        lblFGoal->setObjectName(QStringLiteral("lblFGoal"));
        lblFGoal->setFrameShadow(QFrame::Plain);
        lblFGoal->setLineWidth(3);
        lblFGoal->setIndent(0);

        horizontalLayout->addWidget(lblFGoal);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lblDGoal = new QLabel(layoutWidget);
        lblDGoal->setObjectName(QStringLiteral("lblDGoal"));

        horizontalLayout_2->addWidget(lblDGoal);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lblcurrentFlag = new QLabel(layoutWidget);
        lblcurrentFlag->setObjectName(QStringLiteral("lblcurrentFlag"));

        horizontalLayout_3->addWidget(lblcurrentFlag);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        lblPhrase = new QLabel(layoutWidget);
        lblPhrase->setObjectName(QStringLiteral("lblPhrase"));

        horizontalLayout_4->addWidget(lblPhrase);


        verticalLayout->addLayout(horizontalLayout_4);

        lblInfo = new QLabel(centralWidget);
        lblInfo->setObjectName(QStringLiteral("lblInfo"));
        lblInfo->setGeometry(QRect(610, 430, 54, 12));
        FivetigerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FivetigerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 743, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_3 = new QMenu(menu);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        FivetigerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FivetigerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FivetigerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FivetigerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FivetigerClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(acToSelfPlay);
        menu->addAction(menu_3->menuAction());
        menu_3->addAction(acEasy);
        menu_3->addAction(acMid);
        menu_2->addAction(action);

        retranslateUi(FivetigerClass);
        QObject::connect(acToSelfPlay, SIGNAL(triggered()), FivetigerClass, SLOT(startToSelfClick()));
        QObject::connect(acEasy, SIGNAL(triggered()), FivetigerClass, SLOT(startToEasyClick()));
        QObject::connect(action, SIGNAL(triggered()), FivetigerClass, SLOT(helpClick()));
        QObject::connect(acMid, SIGNAL(triggered()), FivetigerClass, SLOT(startToMidClick()));

        QMetaObject::connectSlotsByName(FivetigerClass);
    } // setupUi

    void retranslateUi(QMainWindow *FivetigerClass)
    {
        FivetigerClass->setWindowTitle(QApplication::translate("FivetigerClass", "Fivetiger", 0));
        acToSelfPlay->setText(QApplication::translate("FivetigerClass", "\345\215\225\344\272\272\347\240\224\347\251\266", 0));
        action->setText(QApplication::translate("FivetigerClass", "\344\272\224\350\231\216\346\243\213\350\257\264\346\230\216", 0));
        acEasy->setText(QApplication::translate("FivetigerClass", "\347\256\200\345\215\225\351\232\276\345\272\246", 0));
        acMid->setText(QApplication::translate("FivetigerClass", "\344\270\255\347\255\211\351\232\276\345\272\246", 0));
        label->setText(QApplication::translate("FivetigerClass", "\345\205\210\346\211\213\346\226\271\345\276\227\345\210\206\357\274\232", 0));
        lblFGoal->setText(QApplication::translate("FivetigerClass", "0", 0));
        label_3->setText(QApplication::translate("FivetigerClass", "\345\220\216\346\211\213\346\226\271\345\276\227\345\210\206\357\274\232", 0));
        lblDGoal->setText(QApplication::translate("FivetigerClass", "0", 0));
        label_5->setText(QApplication::translate("FivetigerClass", "\345\275\223\345\211\215\350\265\260\346\243\213\346\226\271\357\274\232", 0));
        lblcurrentFlag->setText(QApplication::translate("FivetigerClass", "0", 0));
        label_6->setText(QApplication::translate("FivetigerClass", "\350\265\260\346\243\213\351\230\266\346\256\265\357\274\232", 0));
        lblPhrase->setText(QString());
        lblInfo->setText(QString());
        menu->setTitle(QApplication::translate("FivetigerClass", "\346\270\270\346\210\217", 0));
        menu_3->setTitle(QApplication::translate("FivetigerClass", "\345\257\271\346\210\230\347\224\265\350\204\221", 0));
        menu_2->setTitle(QApplication::translate("FivetigerClass", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class FivetigerClass: public Ui_FivetigerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIVETIGER_H
