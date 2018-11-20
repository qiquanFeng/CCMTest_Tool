/********************************************************************************
** Form generated from reading UI file 'pdf_demo.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDF_DEMO_H
#define UI_PDF_DEMO_H

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

class Ui_PDF_DemoClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PDF_DemoClass)
    {
        if (PDF_DemoClass->objectName().isEmpty())
            PDF_DemoClass->setObjectName(QStringLiteral("PDF_DemoClass"));
        PDF_DemoClass->resize(600, 400);
        centralWidget = new QWidget(PDF_DemoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PDF_DemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PDF_DemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        PDF_DemoClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(PDF_DemoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PDF_DemoClass->setStatusBar(statusBar);

        retranslateUi(PDF_DemoClass);

        QMetaObject::connectSlotsByName(PDF_DemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *PDF_DemoClass)
    {
        PDF_DemoClass->setWindowTitle(QApplication::translate("PDF_DemoClass", "PDF_Demo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PDF_DemoClass: public Ui_PDF_DemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDF_DEMO_H
