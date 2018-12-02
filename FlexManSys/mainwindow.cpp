#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addbillet.h"
#include <QDebug>
#include <Billet.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    matrix_ = new Matrix();
    ui->listWidget->setBackgroundRole(QPalette::Base);
}

void MainWindow::on_addBillet_clicked()
{
    addbill_ = new addBillet();
    addbill_->exec();
    QString objString(addbill_->GetResultString());
    if(objString.isEmpty())
    {
        return;
    }
    objString = QString("Об'єкт %1: %2").arg(QString::number(ui->listWidget->count()),objString);
    Billet b(addbill_->GetResultCollection());
    billetCollection_.append(b);
    ui->listWidget->addItem(objString);
    delete addbill_;
}


void MainWindow::on_removeBillet_clicked()
{
    QListWidget *qlW = ui->listWidget;
    int currRow = qlW->row(ui->listWidget->currentItem());
    billetCollection_.removeAt(currRow);
    QStringList strList;
    if(qlW->count()>1)
    {
        for(int i=currRow+1;i<qlW->count();i++)
        {
            strList = qlW->item(i)->text().split(":");
            strList.first()= QString("Об'єкт %1: ").arg(QString::number(i-1));
            qlW->item(i)->setText(QString("%1%2").arg(strList.first(),strList.last()));
        }
    }
    delete ui->listWidget->takeItem(currRow);
}

void MainWindow::on_pushButton_clicked()
{
    if(billetCollection_.count()>=2)
    {
        matrix_->SetMatrix(this->billetCollection_);
        matrix_->show();
    }
    else
    {
        QMessageBox::about(this, "Помилка!", "Матриця пуста або має менше двох об'єктів");
    }
}

MainWindow::~MainWindow()
{
    ui->listWidget->clear();
    delete ui;
}
