/********************************************************************************
** Form generated from reading UI file 'calculaterUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATERUI_H
#define UI_CALCULATERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *m_funcListLable;
    QListWidget *m_funcList;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *m_ExprLable;
    QTextEdit *m_expr;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_resultLable;
    QTextBrowser *m_result;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_registFunc;
    QPushButton *m_loadDll;
    QPushButton *m_executeExpr;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(785, 503);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        m_funcListLable = new QLabel(centralwidget);
        m_funcListLable->setObjectName(QString::fromUtf8("m_funcListLable"));

        verticalLayout_4->addWidget(m_funcListLable);

        m_funcList = new QListWidget(centralwidget);
        m_funcList->setObjectName(QString::fromUtf8("m_funcList"));

        verticalLayout_4->addWidget(m_funcList);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_ExprLable = new QLabel(centralwidget);
        m_ExprLable->setObjectName(QString::fromUtf8("m_ExprLable"));

        verticalLayout_2->addWidget(m_ExprLable);

        m_expr = new QTextEdit(centralwidget);
        m_expr->setObjectName(QString::fromUtf8("m_expr"));

        verticalLayout_2->addWidget(m_expr);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_resultLable = new QLabel(centralwidget);
        m_resultLable->setObjectName(QString::fromUtf8("m_resultLable"));

        horizontalLayout->addWidget(m_resultLable);

        m_result = new QTextBrowser(centralwidget);
        m_result->setObjectName(QString::fromUtf8("m_result"));
        m_result->setMaximumSize(QSize(1000, 30));

        horizontalLayout->addWidget(m_result);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_registFunc = new QPushButton(centralwidget);
        m_registFunc->setObjectName(QString::fromUtf8("m_registFunc"));

        horizontalLayout_2->addWidget(m_registFunc);

        m_loadDll = new QPushButton(centralwidget);
        m_loadDll->setObjectName(QString::fromUtf8("m_loadDll"));

        horizontalLayout_2->addWidget(m_loadDll);

        m_executeExpr = new QPushButton(centralwidget);
        m_executeExpr->setObjectName(QString::fromUtf8("m_executeExpr"));

        horizontalLayout_2->addWidget(m_executeExpr);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(verticalLayout_3);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 785, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        m_funcListLable->setText(QApplication::translate("MainWindow", "Functions List", nullptr));
        m_ExprLable->setText(QApplication::translate("MainWindow", "Input Expressions", nullptr));
        m_resultLable->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        m_registFunc->setText(QApplication::translate("MainWindow", "Register", nullptr));
        m_loadDll->setText(QApplication::translate("MainWindow", "LoadDll", nullptr));
        m_executeExpr->setText(QApplication::translate("MainWindow", "Execute", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATERUI_H
