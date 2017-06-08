#include "zawodnik-statystyki.h"
#include "ui_zawodnik-statystyki.h"
#include "QtDebug"

ZawodnikStatystyki::ZawodnikStatystyki(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZawodnikStatystyki)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel();
    ui->tableView->setModel(qmodel);
    refreshModel();
}

ZawodnikStatystyki::~ZawodnikStatystyki()
{
    delete qmodel;
    delete ui;
    delete zawodnik;
}

void ZawodnikStatystyki::refreshModel(Zawodnik *zawodnik)
{
    this->zawodnik=zawodnik;
    if(zawodnik!=NULL)
    {
        QSqlDatabase db = QSqlDatabase::database();
        if(db.isOpen())
        {
            QString zapytanie = " SELECT sezon.Data_rozpoczecia AS 'Początek sezonu', sezon.Data_zakonczenia AS 'Koniec sezonu', wygrane_sezon_calosc.Wygrane, remisy_sezon_calosc.Remisy, przegrane_sezon_calosc.Przegrane FROM sezon JOIN wygrane_sezon_calosc ON (sezon.IDSezon = wygrane_sezon_calosc.IDSezon) JOIN remisy_sezon_calosc ON (sezon.IDSezon = remisy_sezon_calosc.IDSezon) JOIN przegrane_sezon_calosc ON (sezon.IDSezon = przegrane_sezon_calosc.IDSezon) WHERE wygrane_sezon_calosc.IDZawodnik = "+ QString::number(zawodnik->getIDZawodnik())+" AND remisy_sezon_calosc.IDZawodnik = "+QString::number(zawodnik->getIDZawodnik())+" AND przegrane_sezon_calosc.IDZawodnik = " + QString::number(zawodnik->getIDZawodnik())+ " ORDER BY sezon.Data_rozpoczecia DESC";
            //qDebug()<< zapytanie;
            qmodel->setQuery(zapytanie);
        }
        else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
    }
}

void ZawodnikStatystyki::on_lineEdit_textChanged(const QString &arg1)
{
    QString filter = ui->lineEdit->text();
    QString zapytanie = " SELECT sezon.Data_rozpoczecia AS 'Początek sezonu', sezon.Data_zakonczenia AS 'Koniec sezonu', wygrane_sezon_calosc.Wygrane, remisy_sezon_calosc.Remisy, przegrane_sezon_calosc.Przegrane FROM sezon JOIN wygrane_sezon_calosc ON (sezon.IDSezon = wygrane_sezon_calosc.IDSezon) JOIN remisy_sezon_calosc ON (sezon.IDSezon = remisy_sezon_calosc.IDSezon) JOIN przegrane_sezon_calosc ON (sezon.IDSezon = przegrane_sezon_calosc.IDSezon) WHERE ((sezon.Data_rozpoczecia LIKE '" + filter+"%') OR (sezon.Data_zakonczenia LIKE '" + filter+"%') OR (wygrane_sezon_calosc.Wygrane LIKE '" + filter+"%') OR (remisy_sezon_calosc.Remisy LIKE '" + filter+"%') OR (przegrane_sezon_calosc.Przegrane LIKE '" + filter+"%')) AND wygrane_sezon_calosc.IDZawodnik = "+ QString::number(zawodnik->getIDZawodnik())+" AND remisy_sezon_calosc.IDZawodnik = "+QString::number(zawodnik->getIDZawodnik())+" AND przegrane_sezon_calosc.IDZawodnik = " + QString::number(zawodnik->getIDZawodnik())+ " ORDER BY sezon.Data_rozpoczecia DESC";
    qDebug()<< zapytanie;
    qmodel->setQuery(zapytanie);
}
