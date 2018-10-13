#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>
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
    void computeUniqueOperationsCount(QList<Billet> billList);
    int uniqueOperationsCount_;
    QGraphicsScene *scene;
    QList<Operation> uniqueOperations;
    Ui::Matrix *ui;
};

#endif // MATRIX_H
