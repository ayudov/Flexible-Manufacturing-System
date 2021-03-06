#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMap>
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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addBillet_clicked();
    void on_removeBillet_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    addBillet *addbill_;
    Matrix *matrix_;
    QMap<int,QList<Billet>> groups_;
    QList<Billet> billetCollection_;
    void makeGraphs();
};

#endif // MAINWINDOW_H
