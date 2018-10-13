#include "matrix.h"
#include "ui_matrix.h"
#include <Operation.h>
#include <QDebug>
using namespace OperationNameSpace;

Matrix::Matrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);
}

void Matrix::SetMatrix(QList<Billet> billList)
{
    computeUniqueOperationsCount(billList);
    computeMatrix(billList);
}

void Matrix::computeUniqueOperationsCount(QList<Billet> billList)
{
    for(Billet bill : billList)
    {
        for(Operation op : bill.GetAllOperations())
        {
            if(!uniqueOperations.contains(op))
            {
                uniqueOperations.append(op);
            }
        }
    }
    uniqueOperationsCount_=uniqueOperations.count();
}

int Matrix::GetUniqueOperationsCount()
{
    return uniqueOperationsCount_;
}

void Matrix::computeMatrix(QList<Billet> billList)
{
    QTableWidget *table = ui->tableWidget;
    table->setRowCount(billList.count());
    table->setColumnCount(billList.count());
    for(int i = 0; i < billList.count(); i++)
    {
        for(int j = 0; j < billList.count(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            i==j ? item->setText("-") : item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            table->setItem(i,j,item);
        }
    }
   /* for(Billet bill : billList)
    {

    }*/
}


Matrix::~Matrix()
{
    delete ui;
}
