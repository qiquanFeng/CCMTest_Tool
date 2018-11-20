/********************************************************************************
** Form generated from reading UI file 'dtccmtest.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTCCMTEST_H
#define UI_DTCCMTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dtCCMTestClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *dtCCMTestClass)
    {
        if (dtCCMTestClass->objectName().isEmpty())
            dtCCMTestClass->setObjectName(QStringLiteral("dtCCMTestClass"));
        dtCCMTestClass->resize(600, 400);
        centralWidget = new QWidget(dtCCMTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dtCCMTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(dtCCMTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        dtCCMTestClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(dtCCMTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        dtCCMTestClass->setStatusBar(statusBar);

        retranslateUi(dtCCMTestClass);

        QMetaObject::connectSlotsByName(dtCCMTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *dtCCMTestClass)
    {
        dtCCMTestClass->setWindowTitle(QApplication::translate("dtCCMTestClass", "dtCCMTest", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dtCCMTestClass: public Ui_dtCCMTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTCCMTEST_H
