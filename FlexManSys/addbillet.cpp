#include "addbillet.h"
#include "ui_addbillet.h"
#include <Operation.h>
using namespace OperationNameSpace;

addBillet::addBillet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBillet)
{
    ui->setupUi(this);
    ui->buttonBox->setEnabled(false);
    ui->opTypeBox->addItem("",OperationType::Empty);
    ui->opTypeBox->addItem("Ф",OperationType::TypeF);
    ui->opTypeBox->addItem("Т",OperationType::TypeT);
    ui->opTypeBox->addItem("С",OperationType::TypeC);
    ui->opTypeBox->addItem("Р",OperationType::TypeR);
}

void addBillet::on_AddButton_clicked()
{
    if(ui->opTypeBox->currentData(Qt::UserRole)!=OperationType::Empty && ui->opNumBox->currentText()!="")
    {
        ui->buttonBox->setEnabled(true);
        Operation op;
        QString s(ui->opTypeBox->currentText());
        s.append(ui->opNumBox->currentText());
        ui->textEdit->insertPlainText(s);
        op.SetOperationNumber(ui->opNumBox->currentText().toInt());
        OperationType type = (OperationType)qvariant_cast<qint32>(ui->opTypeBox->currentData(Qt::UserRole));
        op.SetOperationType(type);
        resultCollection_.append(op);
        op.~Operation();
    }
}

void addBillet::on_buttonBox_rejected()
{
    close();
}

void addBillet::on_buttonBox_accepted()
{
    this->resultString_=ui->textEdit->toPlainText();
    close();
}

QList<Operation> addBillet::GetResultCollection()
{
    return resultCollection_;
}

QString addBillet::GetResultString()
{
    return resultString_;
}

addBillet::~addBillet()
{
    delete ui;
}

void addBillet::on_discardLast_clicked()
{
    if(ui->textEdit->toPlainText().isEmpty())
    {
        return;
    }
    ui->textEdit->textCursor().deletePreviousChar();
    ui->textEdit->textCursor().deletePreviousChar();
    this->resultCollection_.removeLast();
    ui->buttonBox->setEnabled(false);
}

void addBillet::on_discardAll_clicked()
{
    if(ui->textEdit->toPlainText().isEmpty())
    {
        return;
    }
    ui->textEdit->clear();
    this->resultCollection_.clear();
    ui->buttonBox->setEnabled(false);
}
