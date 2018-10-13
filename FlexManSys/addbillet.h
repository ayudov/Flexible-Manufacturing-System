#ifndef ADDBILLET_H
#define ADDBILLET_H
#include <Operation.h>
#include <QDialog>

namespace Ui {
class addBillet;
}

class addBillet : public QDialog
{
    Q_OBJECT

public:
    explicit addBillet(QWidget *parent = 0);
    QList<Operation> GetResultCollection();
    QString GetResultString();
    ~addBillet();

private slots:
    void on_buttonBox_accepted();
    void on_AddButton_clicked();
    void on_buttonBox_rejected();
    void on_discardLast_clicked();
    void on_discardAll_clicked();

private:
    Ui::addBillet *ui;
    QList<Operation> resultCollection_;
    QString resultString_;
};

#endif // ADDBILLET_H
