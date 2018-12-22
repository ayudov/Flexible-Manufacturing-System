#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>
#include <QMap>
#include <Billet.h>
#include <QGraphicsScene>

namespace Ui {
class Matrix;
}


class Matrix : public QWidget
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = 0);
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
    QList<Operation> computeUniqueOperationsCount(QList<Billet> billList);
    QList<Operation> computeUniqueOperationsCount(Billet billet);
    void checkGraphs();
    int **matrix_;
    int uniqueOperationsCount_ = 0;
    QList<Operation> uniqueOperations_;
    QList<int> group_;
    QMap<int,QList<int>> groups_;
    QMap<int,QPair<QList<int>,QList<Operation>>> clarifiedGroups_;
    QList<QMap<Operation,QList<Operation>>> graphs_;
    QMap<int,QList<int>> modules_;
    Ui::Matrix *ui;
};

#endif // MATRIX_H
