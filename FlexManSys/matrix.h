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
    ~Matrix();
signals:
    void openWindow();

private:
    void computeMatrix(QList<Billet> billList);
    QList<Operation> computeUniqueOperationsCount(QList<Billet> billList);
    QList<Operation> computeUniqueOperationsCount(Billet billet);
    void setGroups(int **matrix,int size);
    void collectGroup(int maxElement, int row, int colomn, int size, bool direction);
    int **matrix_;
    int uniqueOperationsCount_ = 0;
    QList<Operation> uniqueOperations_;
    QList<int> group_;
    QMap<int,QList<int>> groups_;
    Ui::Matrix *ui;
};

#endif // MATRIX_H
