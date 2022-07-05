#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../drive-download-20220629T131206Z-001/singletonclient.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui_task = new FormTask;
    ui_auth = new authreg;
    QString tmp = "";
    connect(ui_auth, &authreg::return_auth, this, &MainWindow::set_log);
    //connect(singletonclient::getlnstance(),&singletonclient::message_from_server,this,on_messege_from_server);
    ui_auth->show();


}

MainWindow::~MainWindow()
{
    delete ui_task;
    delete ui_auth;
    delete ui;
}
void MainWindow::on_messege_from_server(QString msg){
    //написать парсинг сообщения от сервера
}

void MainWindow::on_Exit_clicked() //закрытие
{
    close();
}
void MainWindow::set_log(QString log) //закрытие
{
   ui->label->setText(log);
   show();
}


void MainWindow::on_actionExit_triggered()//закрытие
{
    on_Exit_clicked();
}


void MainWindow::on_Task1_clicked() //task1, сделать больше тасков
{
    ui_task->set_task(1);
    ui_task->show();
}
void MainWindow::on_actionTask_1_triggered()
{
    on_Task1_clicked();
}


void MainWindow::on_Stat_clicked() //статистику прикрутить от сервера
{
    QMessageBox msg_box_stat;
    msg_box_stat.setText("статистика \n task1 + stat1 +\n stat2: + stat2");
    msg_box_stat.exec();
}


void MainWindow::on_Task2_clicked()
{
    ui_task->set_task(2);
    ui_task->show();
}


void MainWindow::on_Task3_clicked()
{
    ui_task->set_task(3);
    ui_task->show();
}


void MainWindow::on_Task4_clicked()
{
    ui_task->set_task(4);
    ui_task->show();
}


void MainWindow::on_actionTask_2_triggered()
{
    on_Task2_clicked();
}


void MainWindow::on_actionTask_3_triggered()
{
    on_Task3_clicked();
}



void MainWindow::on_actionTask_4_triggered()
{
    on_Task4_clicked();
}

