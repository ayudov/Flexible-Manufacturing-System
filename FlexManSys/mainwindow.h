#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <Billet.h>
#include "addbillet.h"
#include "matrix.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addBillet_clicked();
    void on_removeBillet_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    addBillet *addbill_;
    Matrix *matrix_;
    QList<Billet> billetCollection_;
};

#endif // MAINWINDOW_H
