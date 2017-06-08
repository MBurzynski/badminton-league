#include "sedzia-edytujmecz.h"
#include "ui_sedzia-edytujmecz.h"

SedziaEdytujMecz::SedziaEdytujMecz(int mecz_id, QWidget *parent):
    QDialog(parent),
    ui(new Ui::SedziaEdytujMecz)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->comboBox_4->setDisabled(true);
    ui->comboBox_5->setDisabled(true);
    mecz_id = -1; // pobierz z selected item
}

SedziaEdytujMecz::~SedziaEdytujMecz()
{
    delete ui;
}

void SedziaEdytujMecz::on_debel_checkBox_toggled(bool checked)
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
