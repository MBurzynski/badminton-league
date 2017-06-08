#include "sedzia-sedziowanie.h"
#include "ui_sedzia-sedziowanie.h"
#include "sedzia-dodajmecz.h"
#include "sedzia-edytujmecz.h"
#include "QtDebug"

SedziaSedziowanie::SedziaSedziowanie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SedziaSedziowanie)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel();
    ui->tableView->setModel(qmodel);
    refreshModel();
}

SedziaSedziowanie::~SedziaSedziowanie()
{
    delete qmodel;
    delete ui;
}

void SedziaSedziowanie::refreshModel()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen())qmodel->setQuery("SELECT * FROM kolejka WHERE");// wybrac wszystkie mecze danej kolejki
    else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
}

//Dodaj mecz
void SedziaSedziowanie::on_pushButton_4_clicked()
{
    SedziaNowyMecz *nowymecz = new SedziaNowyMecz();
    nowymecz->show();
}

//Zarządzaj meczem - wpisz wynik
void SedziaSedziowanie::on_pushButton_5_clicked()
{
    int mecz_id = -1; // pobranie z zazanczonego meczu
    SedziaEdytujMecz *edytujmecz = new SedziaEdytujMecz(mecz_id);
    edytujmecz->show();
}
