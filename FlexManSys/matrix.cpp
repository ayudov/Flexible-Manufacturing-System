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
    clarifyGroups(billList);
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
    int group = 1;
    groups_.clear();
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
        for(int i = 1; i <= groups_.count(); i++)
        {
            if(groups_[i].contains(row))
            {
                containsRow = true;
            }
            if(groups_[i].contains(column))
            {
                containsColumn = true;
            }
        }
        if(!containsRow && !containsColumn)
        {
            group_.append(row);
            group_.append(column);
            collectGroup(max, row, column, size, true);
            collectGroup(max, row, column, size, false);
            groups_.insert(group, group_);
            objectsNumber-=group_.count();
            group_.clear();
            group++;
        }
        if((containsRow ^ containsColumn) && objectsNumber == 1)
        {
            group_.append(containsRow ? column : row);
            groups_.insert(group, group_);
            break;
        }
    } while(objectsNumber != 0);
    QString text;
    for(int key : groups_.keys())
    {
        text = QString("Група %1: {").arg(QString::number(key));
        for(int value : groups_[key])
        {
            text.append(QString("%1 ").arg(QString::number(value)));
        }
        text.append(QString("}"));
        ui->textBrowser->append(text);
    }
    delete matrix_;
}

void Matrix::collectGroup(int maxElement, int row, int colomn, int size, bool direction)
{
    matrix_[row][colomn] = 0;
    bool contains = false;
    if(direction)
    {
        for(int i = 0; i < size ; i++)
        {
            if(matrix_[row][i] == maxElement)
            {
                for(int j = 1; j <= groups_.count(); j++)
                {
                    if(groups_[j].contains(i))
                    {
                        contains = true;
                        break;
                    }
                }
                if(!contains && !group_.contains(i))
                {
                    matrix_[row][i] = 0;
                    group_.append(i);
                    collectGroup(maxElement, row, i, size, !direction);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < size ; i++)
        {
            if(matrix_[i][colomn] == maxElement)
            {
                for(int j = 1; j <= groups_.count(); j++)
                {
                    if(groups_[j].contains(i))
                    {
                        contains = true;
                        break;
                    }
                }
                if(!contains && !group_.contains(i))
                {
                    matrix_[i][colomn] = 0;
                    group_.append(i);
                    collectGroup(maxElement, row, i, size, !direction);
                }
            }
        }
    }
    return;
}

QMap<int,QList<int>> Matrix::GetFormedGroups()
{
    return groups_;
}

QMap<int,QPair<QList<int>,QList<Operation>>> Matrix::GetClarifiedGroups()
{
    return clarifiedGroups_;
}


void Matrix::clarifyGroups(QList<Billet> billList)
{
    QPair<QList<int>,QList<Operation>> pair;
    int g = 1;

    //Сформувати групи
    for(QList<int> value : groups_.values())
    {
        QList<Operation> groupOps;
        groupOps.clear();
        for(int i : value)
        {
            for(Operation op : billList[i].GetAllOperations())
            {
                if(!groupOps.contains(op))
                {
                    groupOps.append(op);
                }
            }
        }
        pair.first = value;
        pair.second = groupOps;
        clarifiedGroups_.insert(g, pair);
        groupOps.clear();
        g++;
    }

    //Впорядкувати групи
    for(int i = 1; i <= clarifiedGroups_.count(); i++)
    {
        for(int j = i+1; j <= clarifiedGroups_.count(); j++)
        {
            auto a = clarifiedGroups_[i];
            auto b = clarifiedGroups_[j];
            if(a.second.count() < b.second.count())
            {
                clarifiedGroups_[i] = clarifiedGroups_[j];
                clarifiedGroups_[j] = a;
            }
        }

    }

    //Оптимізація групп
    bool contains = true;
    for(int i = 1; i <= clarifiedGroups_.count(); i++)
    {
        auto a = clarifiedGroups_[i];
        for(int j = i+1; j <= clarifiedGroups_.count(); j++)
        {
            auto b = clarifiedGroups_[j];
            for(int k : b.first)
            {
                contains = true;
                auto billet = billList[k];
                for(Operation op : billet.GetAllOperations())
                {
                    if(!a.second.contains(op))
                    {
                        contains = false;
                    }
                }
                if(contains)
                {
                    clarifiedGroups_[i].first.append(k);
                    clarifiedGroups_[j].first.removeOne(k);
                }
            }
            if(b.first.count()==0)
            {
                clarifiedGroups_.remove(j);
            }
        }
    }
    g = 0;
    /*for(auto pair: clarifiedGroups_)
    {
        QMap<Operation,QList<Operation>> currentGraph = graphs_[g];
        QList<Operation> connections;
        connections.clear();
        for(Operation op: pair.second)
        {
            currentGraph.insert(op,connections);
        }
        for(int i: pair.first)
        {
            Billet bill = billList[i];
            Operation current;
            Operation previous;
            current = bill.GetAllOperations()[0];
            for(Operation op: bill.GetAllOperations())
            {
                if(current == op)
                {
                    continue;
                }
                previous = current;
                current = op;
                if(!currentGraph[previous].contains(current))
                {
                    currentGraph[previous].append(current);
                }
            }
        }
        graphs_[g] = currentGraph;
        g++;
    }*/
    //checkGraphs();
    QString text;
    text.append(QString("Уточненні группи"));
    for(int key : clarifiedGroups_.keys())
    {
        text = QString("Група %1: {").arg(QString::number(key));
        for(int value : clarifiedGroups_[key].first)
        {
            text.append(QString("%1 ").arg(QString::number(value)));
        }
        text.append(QString("}"));
        ui->textBrowser->append(text);
    }
}


void Matrix::checkGraphs()
{
   //перше правило (всі вхідні)
 /*  int m = 1;
   bool moduleAppended = false;
   for(int i = 0; i < graphs_.count(); i++)
   {
       for(QMap<Operation,QList<Operation>> graph: graphs_[i])
       {
           for(auto item: graph)
           {
               if(item.value.isEmpty)
               {
                   modules_[m].append(item.key);
                   moduleAppended = true;
               }
           }
       }
       if(moduleAppended)
       {
           m++;
           moduleAppended = false;
       }
   }

   //друге правило (всі вихідні)
   bool moduleAppended = false;
   for(int i = 0; i < graphs_.count(); i++)
   {
       for(Operation key: graphs_[i].keys())
       {
           for(Operation value: graphs_[i].values())
           {
               if(value == key)
               {
                  continue;
               }
               modules_[m].append(item.key);
               moduleAppended = true;
           }
       }
       if(moduleAppended)
       {
           m++;
       }
   }
   //третє правило (всі цикли)
   bool moduleAppended = false;
   for(int i = 0; i < graphs_.count(); i++)
   {
       for(Operation key: graphs_[i].keys())
       {
           for(int value: modules_.value)
           {
               if(value == key)
               {
                  continue;
               }
               modules_[m].append(item.key);
               moduleAppended = true;
           }
       }
       if(moduleAppended)
       {
           m++;
       }
   }*/
}

Matrix::~Matrix()
{
    delete matrix_;
    ui->textBrowser->clear();
    delete ui;
}
