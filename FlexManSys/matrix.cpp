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

QMap<int,QList<int>> Matrix::GetFormedGroups()
{
    return groups_;
}

QMap<int,QPair<QList<int>,QList<Operation>>> Matrix::GetClarifiedGroups()
{
    return clarifiedGroups_;
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

    //Оптимізувати группи
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

    //Составить графы
    for(auto pair: clarifiedGroups_)
    {
        QList<Node> currentGraph;
        Node *node = new Node;
        for(auto op: pair.second)
        {
            node->node = op;
            node->out = new QList<Node>();
            node->in = new QList<Node>();
            currentGraph.append(*node);
        }
        for(int i: pair.first)
        {
            Billet bill = billList[i];
            QList<Operation> ops = bill.GetAllOperations();
            for(int i = 0; i < ops.count(); i++)
            {
                Node *currNode = new Node;
                for(int j = 0; j < currentGraph.count(); j++)
                {
                    currNode = &currentGraph[j];
                    if(currNode->node == ops[i] && i == 0)
                    {
                        node = currNode;
                        break;
                    }
                    if(currNode->node == ops[i])
                    {
                        if(!node->out->contains(*currNode))
                        {
                            node->out->append(*currNode);
                            currentGraph[j-1] = *node;
                        }
                        if(!currNode->in->contains(*node))
                        {
                            currNode->in->append(*node);
                            currentGraph[j] = *currNode;
                        }
                        node = currNode;
                        break;
                    }
                }
            }
        }
        graphs_.append(currentGraph);
    }

    checkGraphs();

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
   int m = 1;
   bool moduleAppended = false;
   for(int i = 0; i < graphs_.count(); i++)
   {       
       for(auto graphNode: graphs_)
       {
           //перше правило (всі вхідні)
           moduleAppended = false;
           for(auto node: graphNode)
           {
               if(node.out->isEmpty())
               {
                   for(auto module: modules_)
                   {
                       if(module.contains(node.node))
                       {
                           moduleAppended = true;
                           break;
                       }
                   }
                   if(!moduleAppended)
                   {
                       modules_[m].append(node.node);
                       m++;
                   }
                   moduleAppended = false;
               }
           }

           //друге правило (всі вихідні)
           moduleAppended = false;
           for(auto node: graphNode)
           {
               if(node.in->isEmpty())
               {
                   for(auto module: modules_)
                   {
                       if(module.contains(node.node))
                       {
                           moduleAppended = true;
                           break;
                       }
                   }
                   if(!moduleAppended)
                   {
                       modules_[m].append(node.node);
                       m++;
                   }
                   moduleAppended = false;
               }
           }

           //третє правило (зворотній зв'язок)
           moduleAppended = false;
           for(auto node1: graphNode)
           {
               QList<Node> nodes;
               nodes.append(node1);
               for(auto node2: graphNode)
               {
                   if(node2.out->contains(node1) && node1.out->contains(node2) && !nodes.contains(node2))
                   {
                       nodes.append(node2);
                   }
               }
               for(auto module: modules_)
               {
                   for(auto checkNode: nodes)
                   {
                       if(module.contains(checkNode.node))
                       {
                           moduleAppended = true;
                           break;
                       }
                   }

               }
               if(!moduleAppended)
               {
                   for(auto checkNode: nodes)
                   {
                       modules_[m].append(checkNode.node);
                   }
                   m++;
               }
               moduleAppended = false;
           }

           //четверте правило (цикли)
           for(auto node: graphNode)
           {
               cycleStack_.clear();
               recursiveFourthRule(node, node.out);
               for(auto module: modules_)
               {
                   for(auto checkNode: cycleStack_)
                   {
                       if(module.contains(checkNode.node))
                       {
                           moduleAppended = true;
                           break;
                       }
                   }

               }
               if(!moduleAppended)
               {
                   for(auto checkNode: cycleStack_)
                   {
                       modules_[m].append(checkNode.node);
                   }
                   m++;
               }
               moduleAppended = false;
           }

           //п'яте правило (ланцюжок)
           Node currNode;
           for(auto node: graphNode)
           {
               cycleStack_.clear();
               cycleStack_.append(node);
               currNode = node;
               for(auto node2: graphNode)
               {
                   if(node2 == node)
                   {
                       continue;
                   }
                   if(node2 != currNode && (currNode.out->contains(node2) && node2.in->contains(currNode)))
                   {
                       cycleStack_.append(node2);
                       currNode = node2;
                   }
                   if(node2.in->contains(node) && !node.out->contains(node2))
                   {
                       cycleStack_.append(node2);
                   }

               }
               for(auto module: modules_)
               {
                   for(auto checkNode: cycleStack_)
                   {
                       if(module.contains(checkNode.node))
                       {
                           moduleAppended = true;
                           break;
                       }
                   }

               }
               if(!moduleAppended)
               {
                   for(auto checkNode: cycleStack_)
                   {
                       modules_[m].append(checkNode.node);
                   }
                   m++;
               }
               moduleAppended = false;
           }

           //шосте правило (для вигнанців)
           for(auto node: graphNode)
           {
               moduleAppended = false;
               for(auto module: modules_)
               {
                   if(module.contains(node.node))
                   {
                       moduleAppended = true;
                       break;
                   }
               }
               if(!moduleAppended)
               {
                   modules_[m].append(node.node);
                   m++;
               }
               moduleAppended = false;
           }
       }
   }
}

void Matrix::recursiveFourthRule(Node firstNode, QList<Node> *nextNodes)
{
    for(auto node: *nextNodes)
    {
        if(node != firstNode && node.out->isEmpty())
        {
            cycleStack_.clear();
            return;
        }
        if(node != firstNode && !node.out->isEmpty())
        {
            cycleStack_.append(node);
            recursiveFourthRule(node, node.out);
        }
        if(node == firstNode)
        {
            cycleStack_.append(node);
            break;
        }
    }
    return;
}


Matrix::~Matrix()
{
    delete matrix_;
    ui->textBrowser->clear();
    delete ui;
}
