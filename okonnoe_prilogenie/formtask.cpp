#include "formtask.h"
#include "ui_formtask.h"

FormTask::FormTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTask)
{
    ui->setupUi(this);
}

FormTask::~FormTask()
{
    delete ui;
}

void FormTask::on_Send_clicked()
{
    functionsforclient::check_solution(ui->Answer->text(), input_for_task, task_number);
    ui->Answer->setText("");
    hide();
}
void FormTask::set_task(int n)
{
    task_number = n;
    QString input = functionsforclient::generate_rand_input();

    ui->task->setText(functionsforclient::generate_text_task(task_number, input));


}
