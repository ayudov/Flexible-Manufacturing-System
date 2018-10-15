/********************************************************************************
** Form generated from reading UI file 'matrix.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIX_H
#define UI_MATRIX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Matrix
{
public:
    QTableWidget *tableWidget;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *Matrix)
    {
        if (Matrix->objectName().isEmpty())
            Matrix->setObjectName(QStringLiteral("Matrix"));
        Matrix->resize(640, 480);
        tableWidget = new QTableWidget(Matrix);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setGeometry(QRect(9, 9, 621, 311));
        tableWidget->setShowGrid(true);
        textBrowser = new QTextBrowser(Matrix);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(140, 340, 301, 121));

        retranslateUi(Matrix);

        QMetaObject::connectSlotsByName(Matrix);
    } // setupUi

    void retranslateUi(QWidget *Matrix)
    {
        Matrix->setWindowTitle(QApplication::translate("Matrix", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Matrix: public Ui_Matrix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIX_H
