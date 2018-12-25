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
    clarifyModules();
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

    //Конструктор графів
    for(auto pair: clarifiedGroups_)
    {
        QList<Node> currentGraph;
        Node node;
        for(auto op: pair.second)
        {
            node.node = op;
            node.out = new QList<Node>();
            node.in = new QList<Node>();
            currentGraph.append(node);
        }
        for(int i: pair.first)
        {
            Billet bill = billList[i];
            QList<Operation> ops = bill.GetAllOperations();
            for(int j = 0; j < ops.count(); j++)
            {
                Node currNode;
                for(int k = 0; k < currentGraph.count(); k++)
                {
                    currNode = currentGraph[k];
                    if(currNode.node == ops[j] && j == 0)
                    {
                        node = currNode;
                        break;
                    }
                    if(currNode.node == ops[j])
                    {
                        if(!node.out->contains(currNode))
                        {
                            node.out->append(currNode);
                        }
                        currentGraph[currentGraph.indexOf(node)] = node;
                        if(!currNode.in->contains(node))
                        {
                            currNode.in->append(node);
                        }
                        currentGraph[k] = currNode;
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
    ui->textBrowser->append(text);
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
    text.clear();
    text.append(QString("Модулі"));
    ui->textBrowser->append(text);
    for(int i = 0; i < modules_.count(); i++)
    {
        auto module = modules_[i];
        text = QString("Модуль %1: {").arg(QString::number(i));
        for(auto op: module)
        {
            switch(op.GetOperationType())
            {
                case OperationType::TypeT : text.append(QString("T%1 ").arg(QString::number(op.GetOperationNumber())));;
                    break;
                case OperationType::TypeF : text.append(QString("Ф%1 ").arg(QString::number(op.GetOperationNumber())));;
                    break;
                case OperationType::TypeC : text.append(QString("С%1 ").arg(QString::number(op.GetOperationNumber())));;
                    break;
                case OperationType::TypeR : text.append(QString("Р%1 ").arg(QString::number(op.GetOperationNumber())));;
                    break;
            }
        }
        text.append(QString("}"));
        ui->textBrowser->append(text);
    }
}

void Matrix::clarifyModules()
{
    //Впорядкувати модулі
    for(int i = 0; i <= modules_.count(); i++)
    {
        for(int j = i+1; j < modules_.count(); j++)
        {
            auto a = modules_[i];
            auto b = modules_[j];
            if(a.count() > b.count())
            {
                modules_[i] = modules_[j];
                modules_[j] = a;
            }
        }
    }

    //Оптимізувати модулі
    bool contains = true;
    for(int i = 0; i < modules_.count(); i++)
    {
        auto a = modules_[i];
        for(int j = i+1; j < modules_.count(); j++)
        {
            auto b = modules_[j];
            for(auto op : a)
            {
                contains = true;
                if(!b.contains(op))
                {
                    contains = false;
                }
            }
            if(contains)
            {
                modules_.removeAt(i);
                break;
            }
        }
    }

    //Друга оптимізація
    for(int i = 0; i < modules_.count(); i++)
    {
        auto a = modules_[i];
        for(int j = i+1; j < modules_.count(); j++)
        {
            auto b = modules_[j];
            for(auto op : a)
            {
                if(b.contains(op) && b.count() >= a.count())
                {
                    b.removeAt(b.indexOf(op));
                }
                else if(b.contains(op) && a.count() > b.count())
                {
                    a.removeAt(a.indexOf(op));
                }
            }
        }
    }

    QString text;
    text.append(QString("Уточненні модулі"));
    ui->textBrowser->append(text);
    for(int i = 0; i < modules_.count(); i++)
    {
        auto module = modules_[i];
        text = QString("Модуль %1: {").arg(QString::number(i));
        for(auto op: module)
        {
            switch(op.GetOperationType())
            {
                case OperationType::TypeT : text.append(QString("T%1 ").arg(QString::number(op.GetOperationNumber())));;
                    break;
                case OperationType::TypeF : text.append(QString("Ф%1 ").arg(QString::number(op.GetOperationNumber())));;
                    break;
                case OperationType::TypeC : text.append(QString("С%1 ").arg(QString::number(op.GetOperationNumber())));;
                    break;
                case OperationType::TypeR : text.append(QString("Р%1 ").arg(QString::number(op.GetOperationNumber())));;
                    break;
            }
        }
        text.append(QString("}"));
        ui->textBrowser->append(text);
    }
}

void Matrix::checkGraphs()
{
    int m = 0;
    for(auto graphNode: graphs_)
    {
       //перше правило (всі вхідні)
       for(auto node: graphNode)
       {
           if(node.out->isEmpty())
           {
               QList<Operation> module;
               module.append(node.node);
               modules_.append(module);
           }
       }

       //друге правило (всі вихідні)
       for(auto node: graphNode)
       {
           if(node.in->isEmpty())
           {
               QList<Operation> module;
               module.append(node.node);
               modules_.append(module);
           }
       }

       //третє правило (зворотній зв'язок)
       for(auto node1: graphNode)
       {
           QList<Node> nodes;
           for(auto node2: graphNode)
           {
               if(node2.out->contains(node1) && node1.out->contains(node2) && !nodes.contains(node2))
               {
                   nodes.append(node1);
                   nodes.append(node2);
               }
           }
           QList<Operation> module;
           for(auto checkNode: nodes)
           {
               module.append(checkNode.node);
           }
           if(!module.isEmpty())
           {
               modules_.append(module);
           }
       }

       //четверте правило (цикли)
       for(auto node: graphNode)
       {
           cycleStack_.clear();
           cycleFound_ = false;
           recursiveFourthRule(node, node.out);
           if(!cycleFound_)
           {
               continue;
           }
           QList<Operation> module;
           for(auto checkNode: cycleStack_)
           {
               module.append(checkNode.node);
           }
           if(!module.isEmpty())
           {
               modules_.append(module);
           }
       }

       //п'яте правило (ланцюжок)
       Node currNode;
       for(auto node: graphNode)
       {
           cycleStack_.clear();
           cycleFound_ = false;
           isCycle_ = false;
           recursiveFivthRule(node, node.out);
           currNode = node;
           if(!cycleFound_)
           {
               continue;
           }
           cycleStack_.append(currNode);
           QList<Operation> module;
           for(auto checkNode: cycleStack_)
           {
               module.append(checkNode.node);
           }
           if(!module.isEmpty())
           {
               modules_.append(module);
           }
       }

       //шосте правило (для вигнанців)
       bool moduleAppended = false;
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
               QList<Operation> module;
               module.append(node.node);
               modules_.append(module);
           }
           moduleAppended = false;
       }

       //визначити однакові модулі
       bool equal = true;
       QList<QList<Operation>> deleteModules;
       for(int i = m; i < modules_.count(); i++)
       {
           auto module1 = modules_[i];
           for(int j = i+1; j < modules_.count(); j++)
           {
               auto module2 = modules_[j];
               for(auto op: module2)
               {
                   if(!module1.contains(op))
                   {
                       equal = false;
                   }
               }
               if(equal)
               {
                   deleteModules.append(module2);
               }
               equal = true;
           }
       }

       //видалити однакові модулі
       for(auto del: deleteModules)
       {
           modules_.removeAt(modules_.indexOf(del));
       }
       m = modules_.count();
       deleteModules.clear();

       //об'єднати модулі
       for(int i = m; i < modules_.count(); i++)
       {
           auto module1 = modules_[i];
           for(int j = m; j < modules_.count(); j++)
           {
               auto module2 = modules_[j];
               if(i == j)
               {
                   continue;
               }
               for(auto op: module2)
               {
                   if(module1.contains(op))
                   {
                       for(auto op1: module2)
                       {
                           if(!module1.contains(op1))
                           {
                               module1.append(op1);
                           }
                       }
                       deleteModules.append(module2);
                   }
               }
           }
       }

       //видалити модулі які об'єднали з іншим
       for(auto del: deleteModules)
       {
           modules_.removeAt(modules_.indexOf(del));
       }
       m = modules_.count();
    }
}

void Matrix::recursiveFourthRule(Node firstNode, QList<Node> *nextNodes)
{
    for(auto node: *nextNodes)
    {
        if(node.out->isEmpty())
        {
            break;
        }
        if(node == firstNode)
        {
            cycleStack_.append(node);
            cycleFound_ = true;
            break;
        }
        if(node != firstNode)
        {
            if(cycleStack_.contains(node))
            {
                continue;
            }
            cycleStack_.append(node);
            recursiveFourthRule(firstNode, node.out);
            if(cycleFound_)
            {
                return;
            }
            cycleStack_.removeAt(cycleStack_.indexOf(node));
            continue;
        }
    }
    return;
}

void Matrix::recursiveFivthRule(Node firstNode, QList<Node> *nextNodes)
{
    for(auto node: *nextNodes)
    {
        if(firstNode == node)
        {
            isCycle_ = true;
            return;
        }
        if(node.out->isEmpty())
        {
            continue;
        }
        if(firstNode.out->contains(node) && cycleStack_.isEmpty()) // найден второй элемент
        {
            cycleStack_.append(node);
            recursiveFivthRule(firstNode, node.out);
            if(cycleFound_ && !isCycle_)
            {
                break;
            }
            cycleStack_.removeAt(cycleStack_.indexOf(node));
            continue;
        }
        if(firstNode.out->contains(node) && node.in->contains(firstNode) && !cycleStack_.isEmpty()) //найден последний элемент элемент
        {
            cycleStack_.append(node);
            cycleFound_ = true;
            if(cycleFound_ && !isCycle_)
            {
                break;
            }
            cycleStack_.removeAt(cycleStack_.indexOf(node));
            continue;
        }
        if(!firstNode.out->contains(node)) // найден промежуточный элемент
        {
            if(cycleStack_.contains(node))
            {
                continue;
            }
            cycleStack_.append(node);
            recursiveFivthRule(firstNode, node.out);
            if(cycleFound_ && !isCycle_)
            {
                break;
            }
            cycleStack_.removeAt(cycleStack_.indexOf(node));
            continue;
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
