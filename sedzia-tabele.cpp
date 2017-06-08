#include "sedzia-tabele.h"
#include "ui_sedzia-tabele.h"
#include "QtDebug"

SedziaTabele::SedziaTabele(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SedziaTabele)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel();
    ui->tableView->setModel(qmodel);
    refreshModel();
}

SedziaTabele::~SedziaTabele()
{
    delete qmodel;
    delete ui;
}

void SedziaTabele::refreshModel()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen())qmodel->setQuery("SELECT * FROM klub");// wybrac tabele ligową aktulnego sezonu wybranego klubu i poziomu ligi
    else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
}




