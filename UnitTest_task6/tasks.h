#ifndef TASKS_H
#define TASKS_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class Tasks;
}

class Tasks : public QWidget
{
    Q_OBJECT

public:
    explicit Tasks(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~Tasks();
    void setSolution(QString solution);

private slots:
    void on_task1_clicked();
    void on_task2_clicked();
    void on_task3_clicked();
    void on_task4_clicked();

private:
    Ui::Tasks *ui;
    MainWindow *mainWindow;
};

#endif // TASKS_H
