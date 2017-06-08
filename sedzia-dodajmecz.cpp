#include "sedzia-dodajmecz.h"
#include "ui_sedzia-dodajmecz.h"

SedziaNowyMecz::SedziaNowyMecz(QWidget *parent):
    QDialog(parent),
    ui(new Ui::SedziaNowyMecz)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->comboBox_4->setDisabled(true);
    ui->comboBox_5->setDisabled(true);
}

SedziaNowyMecz::~SedziaNowyMecz()
{
    delete ui;
}


void SedziaNowyMecz::on_checkBox_toggled(bool checked)
{
    if(checked==true)
    {
        ui->comboBox_4->setDisabled(false);
        ui->comboBox_5->setDisabled(false);
    }
    if(checked==false)
    {
        ui->comboBox_4->setDisabled(true);
        ui->comboBox_5->setDisabled(true);
    }
}
