/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *addBillet;
    QPushButton *removeBillet;
    QLabel *label;
    QPushButton *pushButton;
    QListWidget *listWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(674, 537);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(85, 255, 127, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(213, 255, 223, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(149, 255, 175, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(42, 127, 63, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(56, 170, 84, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(170, 255, 191, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        MainWindow->setPalette(palette);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        addBillet = new QPushButton(centralWidget);
        addBillet->setObjectName(QStringLiteral("addBillet"));
        addBillet->setGeometry(QRect(210, 340, 31, 23));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        addBillet->setPalette(palette1);
        QFont font;
        font.setFamily(QStringLiteral("Bauhaus 93"));
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        addBillet->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/add_remove/plus-icon-green-md.png"), QSize(), QIcon::Normal, QIcon::Off);
        addBillet->setIcon(icon);
        addBillet->setIconSize(QSize(16, 16));
        removeBillet = new QPushButton(centralWidget);
        removeBillet->setObjectName(QStringLiteral("removeBillet"));
        removeBillet->setGeometry(QRect(240, 340, 31, 23));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Active, QPalette::NoRole, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::NoRole, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::NoRole, brush6);
        removeBillet->setPalette(palette2);
        removeBillet->setFont(font);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/add_remove/256-256-ad37efe2ebc423365b783fa170de6027.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeBillet->setIcon(icon1);
        removeBillet->setIconSize(QSize(16, 16));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 340, 181, 21));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        label->setPalette(palette3);
        QFont font1;
        font1.setFamily(QStringLiteral("Bauhaus 93"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label->setFont(font1);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(290, 50, 131, 131));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/add_remove/dot_matrix.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon2);
        pushButton->setIconSize(QSize(150, 125));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(21, 51, 256, 281));
        QPalette palette4;
        QBrush brush9(QColor(255, 170, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush9);
        QBrush brush10(QColor(243, 255, 14, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush10);
        QBrush brush11(QColor(255, 0, 0, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Highlight, brush11);
        palette4.setBrush(QPalette::Active, QPalette::HighlightedText, brush11);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush10);
        palette4.setBrush(QPalette::Inactive, QPalette::Highlight, brush11);
        palette4.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush11);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Highlight, brush11);
        palette4.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush11);
        listWidget->setPalette(palette4);
        QFont font2;
        font2.setFamily(QStringLiteral("Bauhaus 93"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        listWidget->setFont(font2);
        listWidget->setAutoFillBackground(false);
        listWidget->setStyleSheet(QStringLiteral(""));
        MainWindow->setCentralWidget(centralWidget);
        addBillet->raise();
        removeBillet->raise();
        label->raise();
        pushButton->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        addBillet->setText(QString());
        removeBillet->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270/\320\262\320\270\320\264\320\260\320\273\320\270\321\202\320\270 \320\276\320\261'\321\224\320\272\321\202", 0));
        pushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        listWidget->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
