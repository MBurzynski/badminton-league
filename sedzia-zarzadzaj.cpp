#include "sedzia-zarzadzaj.h"
#include "ui_sedzia-zarzadzaj.h"

SedziaZarzadzaj::SedziaZarzadzaj(QWidget *parent):
    QDialog(parent),
    ui(new Ui::SedziaZarzadzaj)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->lineEdit->setDisabled(true);

}

SedziaZarzadzaj::~SedziaZarzadzaj()
{
    delete ui;
}

void SedziaZarzadzaj::on_buttonBox_accepted()
{

    this->close();
    //sprawdz id tej kolejki i jesli jest poprawene to..
    //otworz okno zarzadzania tą kolejką
}

void SedziaZarzadzaj::on_buttonBox_rejected()
{
    this->close();
}
