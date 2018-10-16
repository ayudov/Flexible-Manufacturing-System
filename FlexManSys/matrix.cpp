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
    uniqueOperations_ = computeUniqueOperationsCount(billList);
    computeMatrix(billList);
    setGroups(matrix_, billList.count());
    delete matrix_;
}

QList<Operation> Matrix::computeUniqueOperationsCount(Billet billet)
{
    QList<Billet> billList;
    billList.append(billet);
    return computeUniqueOperationsCount(billList);
}

QList<Operation> Matrix::computeUniqueOperationsCount(QList<Billet> billList)
{
    QList<Operation> uniqueOps;
    for(Billet bill : billList)
    {
        for(Operation op : bill.GetAllOperations())
        {
            if(!uniqueOps.contains(op))
            {
                uniqueOps.append(op);
            }
        }
    }
    if(uniqueOperationsCount_ == 0)
    {
        uniqueOperationsCount_ = uniqueOps.count();
    }
    return uniqueOps;
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
    matrix_ = new int*[billList.count()];
    for(int i = 0; i < billList.count(); i++)
    {
        matrix_[i] = new int[billList.count()];
        for(int j = 0; j < billList.count(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            i==j ? item->setText("-") : item->setText("0");
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            table->setItem(i,j,item);
            matrix_[i][j]=0;
        }
    }
    for(int i = 0; i < billList.count(); i++)
    {
        QList<Operation> ops = billList[i].GetAllOperations();
        for(int j = i+1; j < billList.count(); j++)
        {
            QList<Operation> opsNext = billList[j].GetAllOperations();
            int a = computeUniqueOperationsCount(billList[j]).count();
            int b = computeUniqueOperationsCount(billList[i]).count();
            int count = uniqueOperationsCount_ - (a + b);
            for(Operation op : ops)
            {
                if(opsNext.contains(op))
                {
                    count+=2;
                }
            }
            table->item(i,j)->setText(QString::number(count));
            matrix_[i][j] = matrix_[j][i] = count;
            table->item(j,i)->setText(QString::number(count));
        }
    }
}

void Matrix::setGroups(int **matrix,int size)
{
    int max = 0;
    int column = 0;
    int row = 0;
    int objectsNumber = ui->tableWidget->rowCount();
    bool containsRow = false;
    bool containsColumn = false;
    int currentElement = 0;
    do
    {
        max = 0;
        containsColumn = containsRow = false;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < i; j++)
            {
                currentElement = matrix[i][j];
                if(max <= currentElement)
                {
                    max = currentElement;
                    column = j;
                    row = i;
                }
            }
        }
        matrix[row][column] = 0;
        for(QList<int> value: groups_.values())
        {
            if(value.contains(row))
            {
                containsRow = true;
            }
            if(value.contains(column))
            {
                containsColumn = true;
            }
        }
        if(objectsNumber == 1 && !(containsRow && containsColumn))
        {
            QList<int> obj;
            if(!containsRow)
            {
                objectsNumber-=1;
                obj.append(row);
            }
            if(!containsColumn)
            {
                objectsNumber-=1;
                obj.append(column);
            }
            if(!obj.isEmpty())
            {
                groups_.insert(max,obj);
            }
            break;
        }
        if(!(containsRow && containsColumn) && groups_.contains(max))
        {
            if(!groups_[max].contains(row))
            {
                objectsNumber-=1;
                groups_[max].append(row);
            }
            if(!groups_[max].contains(column))
            {
                objectsNumber-=1;
                groups_[max].append(column);
            }
        }
        if(!groups_.contains(max) && !(containsRow || containsColumn))
        {
            QList<int> obj;
            if(!containsRow)
            {
                objectsNumber-=1;
                obj.append(row);
            }
            if(!containsColumn)
            {
                objectsNumber-=1;
                obj.append(column);
            }
            if(!obj.isEmpty())
            {
                groups_.insert(max,obj);
            }
        }
    } while(objectsNumber != 0);
    QString text;
    int i = 0;
    for(int key : groups_.keys())
    {
        text = QString("Група %1: {").arg(QString::number(i));
        for(int value : groups_[key])
        {
            text.append(QString("%1 ").arg(QString::number(value)));
        }
        text.append(QString("}"));
        ui->textBrowser->append(text);
        i++;
    }
    groups_.clear();
}


Matrix::~Matrix()
{
    delete matrix_;
    ui->textBrowser->clear();
    delete ui;
}
