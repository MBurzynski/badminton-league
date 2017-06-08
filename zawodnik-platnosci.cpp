#include "zawodnik-platnosci.h"
#include "ui_zawodnik-platnosci.h"
#include "QtDebug"

ZawodnikPlatnosci::ZawodnikPlatnosci(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZawodnikPlatnosci)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel();
    ui->tableView->setModel(qmodel);
    refreshModel();
}

ZawodnikPlatnosci::~ZawodnikPlatnosci()
{
    delete qmodel;
    delete ui;
    delete zawodnik;
}

void ZawodnikPlatnosci::refreshModel(Zawodnik *zawodnik)
{
    this->zawodnik=zawodnik;
    if(zawodnik!=NULL)
    {
        QSqlDatabase db = QSqlDatabase::database();
        if(db.isOpen())
        {
            QString zapytanie = " SELECT CONCAT(sr.Nazwa, ' ',YEAR(s.Data_rozpoczecia) ) AS Sezon, pc.Wartosc AS 'Cena za sezon', IF(pz.Status=1, 'Tak', 'Nie') AS Zaplacone FROM platnosccena AS pc JOIN platnosczawodnik AS pz USING (IDPlatnoscCena) join sezon AS s on(pc.IDSezon=s.IDSezon) join sezonrodzaje AS sr ON(sr.IDSezonRodzaje=s.Rodzaj) WHERE pz.idzawodnik = " + QString::number(zawodnik->getIDZawodnik()) + " ORDER BY s.Data_rozpoczecia DESC";
            //qDebug()<< zapytanie;
            qmodel->setQuery(zapytanie);// wszystkie platnosci tego zawodnika (cena, zapłacone-tak/nie, za jaki sezon)
        }
        else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
    }
}


void ZawodnikPlatnosci::on_lineEdit_textChanged(const QString &arg1)
{
    QString filter = ui->lineEdit->text();
    QString zapytanie = " SELECT CONCAT(sr.Nazwa, ' ',YEAR(s.Data_rozpoczecia) ) AS Sezon, pc.Wartosc AS 'Cena za sezon', IF(pz.Status=1, 'Tak', 'Nie') AS Zaplacone"
            " FROM platnosccena AS pc "
            " JOIN platnosczawodnik AS pz USING (IDPlatnoscCena) "
            " join sezon AS s on(pc.IDSezon=s.IDSezon) "
            " join sezonrodzaje AS sr ON(sr.IDSezonRodzaje=s.Rodzaj) "
            " WHERE (s.Data_rozpoczecia LIKE '"+filter+"%' OR pc.Wartosc LIKE '"+filter+"%' OR CONCAT(sr.Nazwa, ' ',YEAR(s.Data_rozpoczecia)) LIKE '"+filter+"%' OR (IF(pz.Status=1, 'Tak', 'Nie') LIKE '"+filter+"%')) AND pz.idzawodnik = " + QString::number(zawodnik->getIDZawodnik());
            " ORDER BY s.Data_rozpoczecia";
    //qDebug()<< zapytanie;
    qmodel->setQuery(zapytanie);
}
