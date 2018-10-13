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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Matrix
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *Matrix)
    {
        if (Matrix->objectName().isEmpty())
            Matrix->setObjectName(QStringLiteral("Matrix"));
        Matrix->resize(640, 480);
        gridLayout = new QGridLayout(Matrix);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(Matrix);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEnabled(true);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


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
