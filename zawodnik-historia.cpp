#include "zawodnik-historia.h"
#include "ui_zawodnik-historia.h"
#include "zawodnik-meczszczegoly.h"
#include "QtDebug"

ZawodnikHistoria::ZawodnikHistoria(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZawodnikHistoria)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel();
    ui->tableView->setModel(qmodel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    wszystkieMecze = 0;
    refreshModel();
}

ZawodnikHistoria::~ZawodnikHistoria()
{
    delete qmodel;
    delete ui;
}

void ZawodnikHistoria::refreshModel(Zawodnik * zawodnik)
{
    this->zawodnik=zawodnik;
    numerkolejki  = ui->comboBox_kolejka->currentIndex()+1;

    QString sezon = ui->comboBox_sezon->currentText();
    QStringList sezonList = sezon.split(' ');
    QString rodzaj = sezonList.first();
    QString rok = sezonList.last();

    int rodzajInt;

    if(rodzaj=="Letni")
        rodzajInt=1;
    else if(rodzaj=="Zimowy")
        rodzajInt=2;
    else if(rodzaj=="Wakacyjny")
        rodzajInt=3;

    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen() && zawodnik!=NULL)
    {
        QString zapytanieIDKolejka = "SELECT k.IDKolejka, s.IDSezon  FROM sezon as s JOIN ligasezon as ls USING(IDSezon) JOIN kolejka as k ON (k.IDSezon = s.IDSezon) WHERE s.Rodzaj = " +QString::number(rodzajInt)+" AND YEAR(s.Data_rozpoczecia) = "+rok+" and k.Numer = "+QString::number(numerkolejki)+ " AND ls.IDLiga = " +QString::number(zawodnik->getIDLiga())+" ";

        //qDebug() << zapytanieIDKolejka;
        QSqlQuery qKolejka;
        qKolejka.exec(zapytanieIDKolejka);
        IDKolejka=0;
        IDSezon=0;

        if(qKolejka.size()!=0)
        {
            while(qKolejka.next())
            {
                IDKolejka=qKolejka.value(0).toInt();
                IDSezon=qKolejka.value(1).toInt();
            }
        }

        qDebug() << "KOLEJKA ID: " << IDKolejka;
        qDebug() << "SEZON ID: " << IDSezon;

        QString zapytanie =  "SELECT kolejka.Data_rozegrania AS 'Termin_meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' , CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Wygrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Przegrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikA1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikA2) WHERE kolejka.IDKolejka =" +QString::number(IDKolejka)+ " AND (mecz.IDZawodnikB1 = "+QString::number(zawodnik->getIDZawodnik())+ " OR mecz.IDZawodnikB2 = "+QString::number(zawodnik->getIDZawodnik())+")" +
                "UNION " +
                "SELECT kolejka.Data_rozegrania AS 'Termin_meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik', CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Przegrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Wygrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikB1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikB2) WHERE kolejka.IDKolejka="  +QString::number(IDKolejka)+ " AND (mecz.IDZawodnikA1  =  " +QString::number(zawodnik->getIDZawodnik())+  " OR mecz.IDZawodnikA2 = "+QString::number(zawodnik->getIDZawodnik())+")";
        qmodel->setQuery(zapytanie);
    }
    else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
}

void ZawodnikHistoria::on_comboBox_sezon_currentTextChanged(const QString &arg1)
{
    refreshModel(zawodnik);
    wszystkieMecze = 0;
}

void ZawodnikHistoria::on_comboBox_kolejka_currentTextChanged(const QString &arg1)
{
    refreshModel(zawodnik);
    wszystkieMecze = 0;
}

void ZawodnikHistoria::on_lineEdit_textChanged(const QString &arg1)
{
    QString filter = ui->lineEdit->text();
    QString zapytanie;

    if(wszystkieMecze == 0)
    {
        zapytanie =  " SELECT results.* FROM (SELECT kolejka.Data_rozegrania AS 'Termin_meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' , CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Wygrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Przegrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikA1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikA2) WHERE kolejka.IDKolejka =" +QString::number(IDKolejka)+ " AND (mecz.IDZawodnikB1 = "+QString::number(zawodnik->getIDZawodnik())+ " OR mecz.IDZawodnikB2 = "+QString::number(zawodnik->getIDZawodnik())+") AND ((YEAR(kolejka.Data_rozegrania) LIKE '" + filter+"%')  OR (kolejka.Data_rozegrania LIKE '" + filter+"%') OR (MONTH(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (DAY(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (mecz.Godzina LIKE '" + filter+"%') OR (kolejka.numer LIKE '" + filter+"%') OR (mecz.numer_kortu  LIKE '" + filter+"%') OR (uzytkownik.Imie LIKE '" + filter+"%') OR (uzytkownik.Nazwisko LIKE '" + filter+"%') OR (CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Wygrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Przegrana' ELSE 'Remis' END LIKE '" + filter+"%') )" +
            "UNION " +
            "SELECT kolejka.Data_rozegrania AS 'Termin_meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik', CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Przegrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Wygrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikB1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikB2) WHERE kolejka.IDKolejka="  +QString::number(IDKolejka)+ " AND (mecz.IDZawodnikA1  =  " +QString::number(zawodnik->getIDZawodnik())+  " OR mecz.IDZawodnikA2 = "+QString::number(zawodnik->getIDZawodnik())+") AND ((YEAR(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (kolejka.Data_rozegrania LIKE '" + filter+"%') OR (MONTH(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (DAY(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (mecz.Godzina LIKE '" + filter+"%') OR (kolejka.numer LIKE '" + filter+"%') OR (mecz.numer_kortu  LIKE '" + filter+"%') OR (uzytkownik.Imie LIKE '" + filter+"%') OR (uzytkownik.Nazwisko LIKE '" + filter+"%')  OR (CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Przegrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Wygrana' ELSE 'Remis' END LIKE '" + filter+"%') )) AS results ORDER BY results.Termin_meczu, results.Godzina ";
    }
    else
    {
        zapytanie =  " SELECT results.* FROM (SELECT kolejka.Data_rozegrania AS 'Termin_meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' , CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Wygrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Przegrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikA1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikA2) WHERE (mecz.IDZawodnikB1 = "+QString::number(zawodnik->getIDZawodnik())+ " OR mecz.IDZawodnikB2 = "+QString::number(zawodnik->getIDZawodnik())+") AND ((YEAR(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (MONTH(kolejka.Data_rozegrania) LIKE '" + filter+"%')   OR (kolejka.Data_rozegrania LIKE '" + filter+"%') OR (DAY(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (mecz.Godzina LIKE '" + filter+"%') OR (kolejka.numer LIKE '" + filter+"%') OR (mecz.numer_kortu  LIKE '" + filter+"%') OR (uzytkownik.Imie LIKE '" + filter+"%') OR (uzytkownik.Nazwisko LIKE '" + filter+"%') OR (CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Wygrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Przegrana' ELSE 'Remis' END LIKE '" + filter+"%') )" +
                "UNION " +
                "SELECT kolejka.Data_rozegrania AS 'Termin_meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik', CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Przegrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Wygrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikB1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikB2) WHERE (mecz.IDZawodnikA1  =  " +QString::number(zawodnik->getIDZawodnik())+  " OR mecz.IDZawodnikA2 = "+QString::number(zawodnik->getIDZawodnik())+") AND ((YEAR(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (MONTH(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (kolejka.Data_rozegrania LIKE '" + filter+"%') OR (DAY(kolejka.Data_rozegrania) LIKE '" + filter+"%') OR (mecz.Godzina LIKE '" + filter+"%') OR (kolejka.numer LIKE '" + filter+"%') OR (mecz.numer_kortu  LIKE '" + filter+"%') OR (uzytkownik.Imie LIKE '" + filter+"%') OR (uzytkownik.Nazwisko LIKE '" + filter+"%')  OR (CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Przegrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Wygrana' ELSE 'Remis' END LIKE '" + filter+"%') )) AS results ORDER BY results.Termin_meczu ";

    }
    qmodel->setQuery(zapytanie);
}

void ZawodnikHistoria::on_pushButton_wszystkie_mecze_clicked()
{
    QString zapytanie =  " SELECT results.* FROM (SELECT kolejka.Data_rozegrania AS 'Termin_meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' , CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Wygrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Przegrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikA1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikA2) WHERE (mecz.IDZawodnikB1 = "+QString::number(zawodnik->getIDZawodnik())+ " OR mecz.IDZawodnikB2 = "+QString::number(zawodnik->getIDZawodnik())+")" +
            "UNION " +
            "SELECT kolejka.Data_rozegrania AS 'Termin_meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik', CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Przegrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Wygrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikB1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikB2) WHERE (mecz.IDZawodnikA1  =  " +QString::number(zawodnik->getIDZawodnik())+  " OR mecz.IDZawodnikA2 = "+QString::number(zawodnik->getIDZawodnik())+")) AS results ORDER BY results.Termin_meczu ";

    qDebug() << zapytanie;
    qmodel->setQuery(zapytanie);
    wszystkieMecze = 1;
}

void ZawodnikHistoria::on_tableView_activated(const QModelIndex &index)
{

    on_pushButton_Szczegoly_clicked();


}

void ZawodnikHistoria::on_pushButton_Szczegoly_clicked()
{
    int id = -1;

    if(ui->tableView->selectionModel()->hasSelection())
    {
        QModelIndexList godzinaLista  = ui->tableView->selectionModel()->selectedRows(1);
        QModelIndexList dataLista  = ui->tableView->selectionModel()->selectedRows(0);
        QModelIndexList przeciwinikLista  = ui->tableView->selectionModel()->selectedRows(3);
        godzina = godzinaLista.at(0).data().toString();
        przeciwnik = przeciwinikLista.at(0).data().toString();
        data = dataLista.at(0).data().toString();

        QString zapytanie =  "SELECT mecz.IDMecz, kolejka.Data_rozegrania AS 'Termin meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik' , CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Wygrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Przegrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikA1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikA2) WHERE mecz.godzina = '"+godzina+"' AND (mecz.IDZawodnikA1 = '"+przeciwnik+"' OR mecz.IDZawodnikA2 = '"+przeciwnik+"') AND kolejka.Data_rozegrania = '" +data+ "' AND (mecz.IDZawodnikB1 = "+QString::number(zawodnik->getIDZawodnik())+ " OR mecz.IDZawodnikB2 = "+QString::number(zawodnik->getIDZawodnik())+")" +
                " UNION " +
                " SELECT mecz.IDMecz, kolejka.Data_rozegrania AS 'Termin meczu',mecz.Godzina AS 'Godzina', mecz.numer_kortu AS 'Numer kortu', Concat(uzytkownik.Imie,' ', uzytkownik.Nazwisko) AS 'Przeciwnik', CASE WHEN mecz.Set_1B > mecz.Set_1A AND mecz.Set_2B > mecz.Set_2A THEN 'Przegrana' WHEN mecz.Set_1B < mecz.Set_1A AND mecz.Set_2B < mecz.Set_2A THEN 'Wygrana' ELSE 'Remis' END as 'Rezultat' FROM kolejka JOIN mecz USING(IDKolejka) JOIN uzytkownik ON (uzytkownik.IDUzytkownik = mecz.IDZawodnikB1 OR uzytkownik.IDUzytkownik = mecz.IDZawodnikB2) WHERE mecz.godzina = '"+godzina+"' AND (mecz.IDZawodnikB1 = '"+przeciwnik+"' OR mecz.IDZawodnikB2 = '"+przeciwnik+"') AND kolejka.Data_rozegrania= '"  +data+ "' AND (mecz.IDZawodnikA1  =  " +QString::number(zawodnik->getIDZawodnik())+  " OR mecz.IDZawodnikA2 = "+QString::number(zawodnik->getIDZawodnik())+")";

        QSqlQuery qMecz;
        qMecz.exec(zapytanie);

        if(qMecz.size()!=0)
        {
            while(qMecz.next())
            {
                id=qMecz.value(0).toInt();
            }
        }
    }

    ZawodnikMecz *mecz = new ZawodnikMecz(id);
    mecz->show();
}
