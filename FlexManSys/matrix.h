#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>
#include <QMap>
#include <Billet.h>
#include <QGraphicsScene>

namespace Ui {
class Matrix;
}

struct Node
{
    Operation node;
    QList<Node> *out;
    QList<Node> *in;
    bool operator== (const Node n)
    {
        return this->node == n.node;
    }
    bool operator!= (const Node n)
    {
        return this->node != n.node;
    }
};


class Matrix : public QWidget
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = nullptr);
    void SetMatrix(QList<Billet> billList);
    int GetUniqueOperationsCount();
    QMap<int,QList<int>> GetFormedGroups();
    QMap<int,QPair<QList<int>,QList<Operation>>> GetClarifiedGroups();
    ~Matrix();

private:
    void setGroups(int **matrix,int size);
    void computeMatrix(QList<Billet> billList);
    void collectGroup(int maxElement, int row, int colomn, int size, bool direction);
    void clarifyGroups(QList<Billet> billList);
    void clarifyModules();
    QList<Operation> computeUniqueOperationsCount(QList<Billet> billList);
    QList<Operation> computeUniqueOperationsCount(Billet billet);
    void checkGraphs();
    void recursiveFourthRule(Node firstNode, QList<Node> *nextNodes);
    void recursiveFivthRule(Node firstNode, QList<Node> *nextNodes);
    bool cycleFound_;
    bool isCycle_;
    int **matrix_;
    int uniqueOperationsCount_ = 0;
    QList<Operation> uniqueOperations_;
    QList<Node> cycleStack_;
    QList<int> group_;
    QMap<int,QList<int>> groups_;
    QMap<int,QPair<QList<int>,QList<Operation>>> clarifiedGroups_;
    QList<QList<Node>> graphs_;
    QList<QList<Operation>> modules_;
    Ui::Matrix *ui;
};

#endif // MATRIX_H
