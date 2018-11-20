/********************************************************************************
** Form generated from reading UI file 'widimagelist.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDIMAGELIST_H
#define UI_WIDIMAGELIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidImageList
{
public:

    void setupUi(QWidget *WidImageList)
    {
        if (WidImageList->objectName().isEmpty())
            WidImageList->setObjectName(QStringLiteral("WidImageList"));
        WidImageList->resize(400, 300);

        retranslateUi(WidImageList);

        QMetaObject::connectSlotsByName(WidImageList);
    } // setupUi

    void retranslateUi(QWidget *WidImageList)
    {
        WidImageList->setWindowTitle(QApplication::translate("WidImageList", "WidImageList", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WidImageList: public Ui_WidImageList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDIMAGELIST_H
