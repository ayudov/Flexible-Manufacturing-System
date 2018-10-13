#ifndef OPERATION_H
#define OPERATION_H
namespace OperationNameSpace
{
enum OperationType{
    Empty,
    TypeT,
    TypeF,
    TypeC,
    TypeR
};
}


class Operation
{
public:
    Operation();
    ~Operation();
    Operation(OperationNameSpace::OperationType opType,int opNumber);
    void SetOperationType(OperationNameSpace::OperationType opType);
    void SetOperationNumber(int opNumber);
    OperationNameSpace::OperationType GetOperationType();
    int GetOperationNumber();
    bool operator==(const Operation op1);
private:
    OperationNameSpace::OperationType opType_;
    int opNumber_;
};




#endif // OPERATION_H
