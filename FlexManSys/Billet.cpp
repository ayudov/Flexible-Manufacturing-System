#include <Billet.h>
#include <QList>
#include <Operation.h>

Billet::Billet(QList<Operation> op)
{
    this->operationsCollection_= op;
}

QList<Operation> Billet::GetAllOperations()
{
    return operationsCollection_;
}

Billet::~Billet()
{
}
