#include "functionsforclient.h"

functionsforclient::functionsforclient()
{

}

void functionsforclient::auth(QString log, QString pass)
{
    QString res = "auth&"+log+"&"+pass;
     qDebug()<<res;
     singletonclient::getlnstance();
     singletonclient::serv(res);
}

void functionsforclient::reg(QString log, QString pass, QString mail)
{
    QString res = "reg&"+log+"&"+pass+"&"+mail;
     qDebug()<<res;
     singletonclient::getlnstance();
     singletonclient::serv(res);// отправка на сервер

}

void functionsforclient::updstat(/*QString log,*/ int task_number, QString upd)
{
    QString res = "updstat&"+QString::number(task_number)+"&"+upd;
    qDebug()<<res;

    //QString res = "updstat&"+/*log*/+"&"+QString::number(task_number)+"&";
   // if(ans)
       //res+='+';
  //  else
     //   res+='-';
  //  qDebug()<<res;
}

QString functionsforclient::generate_text_task (int task_number, QString input)
{
return "task " + QString::number(task_number)+" " + input;
}

QString functionsforclient::generate_rand_input(){
    return "DDD";
}

QString functionsforclient::solve_task(int task_number, QString input)
{
    return "upd"+QString::number(task_number);
}

bool functionsforclient::check_solution(QString answer,QString input, int task_number)
{
 bool res = (answer ==functionsforclient::solve_task(task_number,input));
QString tmp = "";
if (res)
    tmp = "+";
else
    tmp = "-";
 updstat(task_number, tmp);
        return res;

}
