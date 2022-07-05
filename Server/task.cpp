#include "task.h"

Task::Task(QString number)
{
    this->number = number;
}

QString Task::resolve()
{
    if (number == "1") {
        return getTask1();
    } else if (number == "2") {
        return getTask2();
    } else if (number == "3") {
        return getTask3();
    } else if (number == "4") {
        return getTask4();
    } else {
        return "Задача не найдена!";
    }
}

QString Task::getTask1()
{
    return "Решение первой задачи";
}

QString Task::getTask2()
{
    return "Решение второй задачи";
}

QString Task::getTask3()
{
    return "Решение третьей задачи";
}

QString Task::getTask4()
{
    return "Решение четвертой задачи";
}
