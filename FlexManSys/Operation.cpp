#include <Operation.h>

Operation::Operation()
{
}

Operation::Operation(OperationNameSpace::OperationType opType, int opNum)
{
    this->opType_ = opType;
    this->opNumber_ = opNum;
}

void Operation::SetOperationNumber(int opNumber)
{
    this->opNumber_=opNumber;
}

void Operation::SetOperationType(OperationNameSpace::OperationType opType)
{
    this->opType_=opType;
}

OperationNameSpace::OperationType Operation::GetOperationType()
{
    return this->opType_;
}

int Operation::GetOperationNumber()
{
    return this->opNumber_;
}

bool Operation::operator==(const Operation op1)
{
    return &op1==this || (op1.opType_==opType_ && op1.opNumber_==opNumber_);
}

Operation::~Operation()
{

}
