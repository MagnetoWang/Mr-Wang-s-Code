/********************************************************************************
** Form generated from reading UI file 'stack.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STACK_H
#define UI_STACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Stack
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Stack)
    {
        if (Stack->objectName().isEmpty())
            Stack->setObjectName(QStringLiteral("Stack"));
        Stack->resize(400, 300);
        menuBar = new QMenuBar(Stack);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Stack->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Stack);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Stack->addToolBar(mainToolBar);
        centralWidget = new QWidget(Stack);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Stack->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Stack);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Stack->setStatusBar(statusBar);

        retranslateUi(Stack);

        QMetaObject::connectSlotsByName(Stack);
    } // setupUi

    void retranslateUi(QMainWindow *Stack)
    {
        Stack->setWindowTitle(QApplication::translate("Stack", "Stack", 0));
    } // retranslateUi

};

namespace Ui {
    class Stack: public Ui_Stack {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STACK_H
