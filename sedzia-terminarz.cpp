#include "sedzia-terminarz.h"
#include "ui_sedzia-terminarz.h"
#include "QtDebug"

SedziaTerminarz::SedziaTerminarz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SedziaTerminarz)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel();
    ui->tableView->setModel(qmodel);
    refreshModel();
}

SedziaTerminarz::~SedziaTerminarz()
{
    delete qmodel;
    delete ui;
}

void SedziaTerminarz::refreshModel()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen())qmodel->setQuery("SELECT * FROM klub");// wszytkie mecze którymi zarządza ten sędzia, w kolejności daty
    else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
}




