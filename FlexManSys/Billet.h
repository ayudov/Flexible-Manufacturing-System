#ifndef BILLET_H
#define BILLET_H
#include <QString>
#include <QList>
#include <Operation.h>
using namespace OperationNameSpace;

class Billet
{
public:
    Billet();
    ~Billet();
    Billet(QList<Operation> opCollection);
    bool ContainsOperation(Operation operation);
    Operation GetOperation(OperationType opType, int opNum);
    QList<Operation> GetTypicalOperations(OperationType opType);
    QList<Operation> GetTypicalOperations(int opNum);
    QList<Operation> GetAllOperations();
private:
    QList<Operation> operationsCollection_;
};


#endif // BILLET_H
