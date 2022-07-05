#ifndef AUTHREG_H
#define AUTHREG_H

#include <QDebug>
#include <functionsforclient.h>
#include <QWidget>
#include <QString>
namespace Ui {
class authreg;
}

class authreg : public QWidget
{
    Q_OBJECT

public:
    explicit authreg(QWidget *parent = nullptr);
    ~authreg();

private slots:
    void on_Register_clicked();

    void on_OK_clicked();

signals:
    void return_auth(QString log);

private:
    Ui::authreg *ui;
};

#endif // AUTHREG_H
