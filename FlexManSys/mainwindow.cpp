#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addbillet.h"
#include <QProcess>
#include <QDebug>
#include <Billet.h>
#include <QMessageBox>
#include <QFile>

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
        makeGraphs();
        matrix_->show();
    }
    else
    {
        QMessageBox::about(this, "Помилка!", "Матриця пуста або має менше двох об'єктів");
    }
}

void MainWindow::makeGraphs()
{
    QFile file;
    QMap<int,QPair<QList<int>,QList<Operation>>> clarifiedGroups;
    clarifiedGroups = matrix_->GetClarifiedGroups();
    for(auto value : clarifiedGroups)
    {
        file.setFileName("myGraph"+QString::number(clarifiedGroups.key(value))+".dot");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            QTextStream writeStream(&file);
            writeStream.setCodec("Windows-1251");
            writeStream << "digraph Group" << QString::number(clarifiedGroups.key(value)) << "{ \n";
            for(int bill: value.first)
            {
                Billet billet = billetCollection_[bill];
                Operation lastOp = billet.GetAllOperations().last();
                for(Operation op : billet.GetAllOperations())
                {
                    QString last = lastOp == op ? ";\n" : "->";
                    switch(op.GetOperationType())
                    {
                        case OperationType::TypeT : writeStream << "T" << QString::number(op.GetOperationNumber()) << last;
                            break;
                        case OperationType::TypeF : writeStream << "F" << QString::number(op.GetOperationNumber()) << last;
                            break;
                        case OperationType::TypeC : writeStream << "C" << QString::number(op.GetOperationNumber()) << last;
                            break;
                        case OperationType::TypeR : writeStream << "R" << QString::number(op.GetOperationNumber()) << last;
                            break;
                    default: writeStream << "\n";
                    }
                }
            }
            writeStream << "}\n";
            file.close();
        }
    }
}

MainWindow::~MainWindow()
{
    ui->listWidget->clear();
    delete ui;
}
