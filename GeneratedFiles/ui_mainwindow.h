/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "graphwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QPushButton *resumeBtn;
    QPushButton *stopBtn;
    QSpacerItem *verticalSpacer;
    QPushButton *preBtn;
    QPushButton *nextBtn;
    QSpacerItem *verticalSpacer_2;
    QPushButton *startMoveBtn;
    QPushButton *stopMoveBtn;
    GraphWidget *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(880, 599);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        startBtn = new QPushButton(centralWidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));

        verticalLayout->addWidget(startBtn);

        pauseBtn = new QPushButton(centralWidget);
        pauseBtn->setObjectName(QString::fromUtf8("pauseBtn"));

        verticalLayout->addWidget(pauseBtn);

        resumeBtn = new QPushButton(centralWidget);
        resumeBtn->setObjectName(QString::fromUtf8("resumeBtn"));

        verticalLayout->addWidget(resumeBtn);

        stopBtn = new QPushButton(centralWidget);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));

        verticalLayout->addWidget(stopBtn);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        preBtn = new QPushButton(centralWidget);
        preBtn->setObjectName(QString::fromUtf8("preBtn"));

        verticalLayout->addWidget(preBtn);

        nextBtn = new QPushButton(centralWidget);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));

        verticalLayout->addWidget(nextBtn);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        startMoveBtn = new QPushButton(centralWidget);
        startMoveBtn->setObjectName(QString::fromUtf8("startMoveBtn"));

        verticalLayout->addWidget(startMoveBtn);

        stopMoveBtn = new QPushButton(centralWidget);
        stopMoveBtn->setObjectName(QString::fromUtf8("stopMoveBtn"));

        verticalLayout->addWidget(stopMoveBtn);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        graphicsView = new GraphWidget(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 880, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(startBtn, SIGNAL(clicked()), MainWindow, SLOT(Start()));
        QObject::connect(pauseBtn, SIGNAL(clicked()), MainWindow, SLOT(Pause()));
        QObject::connect(stopBtn, SIGNAL(clicked()), MainWindow, SLOT(Stop()));
        QObject::connect(preBtn, SIGNAL(clicked()), MainWindow, SLOT(PreviousStep()));
        QObject::connect(nextBtn, SIGNAL(clicked()), MainWindow, SLOT(NextStep()));
        QObject::connect(startMoveBtn, SIGNAL(clicked()), MainWindow, SLOT(StartMoveAnimation()));
        QObject::connect(stopMoveBtn, SIGNAL(clicked()), MainWindow, SLOT(StopMoveAnimation()));
        QObject::connect(resumeBtn, SIGNAL(clicked()), MainWindow, SLOT(Resume()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        startBtn->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pauseBtn->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        resumeBtn->setText(QApplication::translate("MainWindow", "Resume", 0, QApplication::UnicodeUTF8));
        stopBtn->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        preBtn->setText(QApplication::translate("MainWindow", "Previous", 0, QApplication::UnicodeUTF8));
        nextBtn->setText(QApplication::translate("MainWindow", "NextStep", 0, QApplication::UnicodeUTF8));
        startMoveBtn->setText(QApplication::translate("MainWindow", "StartMove", 0, QApplication::UnicodeUTF8));
        stopMoveBtn->setText(QApplication::translate("MainWindow", "StopMove", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
