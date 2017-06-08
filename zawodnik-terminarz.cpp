#include "zawodnik-terminarz.h"
#include "ui_zawodnik-terminarz.h"
#include "QtDebug"

ZawodnikTerminarz::ZawodnikTerminarz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZawodnikTerminarz)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel(this);
    ui->tableView->setModel(qmodel);
    refreshModel();
}

ZawodnikTerminarz::~ZawodnikTerminarz()
{
    delete qmodel;
    delete ui;
    delete zawodnik;
}

void ZawodnikTerminarz::refreshModel(Zawodnik *zawodnik)
{
    this->zawodnik = zawodnik;
    if(zawodnik!=NULL)
    {
        QSqlDatabase db = QSqlDatabase::database();
        if(db.isOpen())
        {
            zapytanie = "SELECT kolejka.Data_rozegrania AS 'Termin meczu',mecz.Godzina AS 'Godzina',kolejka.numer AS 'Numer kolejki', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikA1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikA2) WHERE kolejka.status = 0 AND (mecz.IDZawodnikB1 = "+QString::number(zawodnik->getIDZawodnik())+ " OR mecz.IDZawodnikB2 = "+QString::number(zawodnik->getIDZawodnik())+")" +
                    "UNION " +
                    "SELECT kolejka.Data_rozegrania AS 'Termin meczu',mecz.Godzina AS 'Godzina',kolejka.numer AS 'Numer kolejki', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikB1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikB2) WHERE kolejka.status = 0 AND (mecz.IDZawodnikA1  =  " +QString::number(zawodnik->getIDZawodnik())+  " OR mecz.IDZawodnikA2 = "+QString::number(zawodnik->getIDZawodnik())+")";
            qmodel->setQuery(zapytanie);// najbliższe mecze tego zawodnika, czy tak naprawde mecze z jego udziałem w najbliższej kolejce

        }
        else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
    }
}

//Wyszukiwanie
void ZawodnikTerminarz::on_lineEdit_textChanged(const QString &arg1)
{
    QString filter = ui->lineEdit->text();

    zapytanie = "SELECT kolejka.Data_rozegrania AS 'Termin meczu',mecz.Godzina AS 'Godzina',kolejka.numer AS 'Numer kolejki', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikA1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikA2) WHERE kolejka.status = 0 AND (mecz.IDZawodnikB1 = "+QString::number(zawodnik->getIDZawodnik())+ " OR mecz.IDZawodnikB2 = "+QString::number(zawodnik->getIDZawodnik())+") AND ((kolejka.Data_rozegrania LIKE '" + filter+"%') OR (mecz.Godzina LIKE '" + filter+"%') OR (kolejka.numer LIKE '" + filter+"%') OR (mecz.numer_kortu  LIKE '" + filter+"%') OR (uzytkownik.Imie LIKE '" + filter+"%') OR (uzytkownik.Nazwisko LIKE '" + filter+"%') )" +
            " UNION " +
            " SELECT kolejka.Data_rozegrania AS 'Termin meczu',mecz.Godzina AS 'Godzina',kolejka.numer AS 'Numer kolejki', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikB1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikB2) WHERE kolejka.status = 0 AND (mecz.IDZawodnikA1  =  " +QString::number(zawodnik->getIDZawodnik())+  " OR mecz.IDZawodnikA2 = "+QString::number(zawodnik->getIDZawodnik())+")AND ((kolejka.Data_rozegrania LIKE '" + filter+"%') OR (mecz.Godzina LIKE '" + filter+"%') OR (kolejka.numer LIKE '" + filter+"%') OR (mecz.numer_kortu  LIKE '" + filter+"%') OR (uzytkownik.Imie LIKE '" + filter+"%') OR (uzytkownik.Nazwisko LIKE '" + filter+"%') )";

    qmodel->setQuery(zapytanie);
}
