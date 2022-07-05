#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
public:
    Task(QString number);
    QString resolve();
private:
    QString number;
    QString getTask1();
    QString getTask2();
    QString getTask3();
    QString getTask4();
};

#endif // TASK_H
