#ifndef FUNCTIONSFORCLIENT_H
#define FUNCTIONSFORCLIENT_H

#include <QString>
#include <QDebug>
#include <formtask.h>
#include "../drive-download-20220629T131206Z-001/singletonclient.h"

class functionsforclient
{
public:
    functionsforclient();
    static void auth(QString log, QString pass);
    static void reg(QString log, QString pass, QString mail);
    static void updstat (int task_number, QString upd);

    static QString generate_text_task(int task_number, QString input);
    static QString generate_rand_input();
    static QString solve_task(int task_number, QString input);
    static bool check_solution(QString answer,QString input, int task_number);
};

#endif // FUNCTIONSFORCLIENT_H
