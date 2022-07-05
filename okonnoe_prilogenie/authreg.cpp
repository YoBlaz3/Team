#include "authreg.h"
#include "ui_authreg.h"

authreg::authreg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authreg)
{
    ui->setupUi(this);
    ui->Mail->setVisible(false);
}

authreg::~authreg()
{
    delete ui;
}

void authreg::on_Register_clicked()
{
    ui->Mail->setVisible(true);
    ui->Register->setVisible(false);
}


void authreg::on_OK_clicked()
{
    QString log = ui->Login->text();
    QString pass = ui->Password->text();
    if(ui->Mail->isVisible())
    {
        QString mail = ui->Mail->text();
        functionsforclient::reg(log,pass,mail);

    }
    else {
        functionsforclient::auth(log,pass);

    }
    emit return_auth(log);
    hide();
}

