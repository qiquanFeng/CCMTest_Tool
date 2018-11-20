/********************************************************************************
** Form generated from reading UI file 'ccmtest.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCMTEST_H
#define UI_CCMTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ccmTest
{
public:
    QWidget *widget;

    void setupUi(QDockWidget *ccmTest)
    {
        if (ccmTest->objectName().isEmpty())
            ccmTest->setObjectName(QStringLiteral("ccmTest"));
        ccmTest->resize(400, 300);
        widget = new QWidget();
        widget->setObjectName(QStringLiteral("widget"));
        ccmTest->setWidget(widget);

        retranslateUi(ccmTest);

        QMetaObject::connectSlotsByName(ccmTest);
    } // setupUi

    void retranslateUi(QDockWidget *ccmTest)
    {
        ccmTest->setWindowTitle(QApplication::translate("ccmTest", "ccmTest", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ccmTest: public Ui_ccmTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCMTEST_H
