#include "zawodnik-tabela.h"
#include "ui_zawodnik-tabela.h"
#include "QtDebug"

ZawodnikTabela::ZawodnikTabela(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZawodnikTabela)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel();
    ui->tableView->setModel(qmodel);
    refreshModel(NULL);
}

ZawodnikTabela::~ZawodnikTabela()
{
    delete qmodel;
    delete ui;
}

void ZawodnikTabela::refreshModel(Zawodnik *zawodnik)
{
    this->zawodnik=zawodnik;
    ligaPoziomString = ui->comboBoxPoziom->currentText();

    if(ligaPoziomString=="A")
        ligaPoziom = 1;
    else if(ligaPoziomString=="B")
        ligaPoziom=2;
    else if(ligaPoziomString=="C")
        ligaPoziom=3;

    QString sezon = ui->comboBoxSezon->currentText();
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

        QString zapytanieIDLiga = "SELECT l.idliga, s.IDSezon FROM liga as l join ligasezon as ls USING(IDLiga) join sezon as s USING(idsezon) where s.Rodzaj = "+QString::number(rodzajInt)+" AND l.IDKlub="+QString::number(zawodnik->getIDKlub())+" AND YEAR(s.Data_rozpoczecia) = "+rok+" and l.Poziom_trudnosci=" + QString::number(ligaPoziom) +"";

        QSqlQuery qLiga;
        qLiga.exec(zapytanieIDLiga);
        int IDLiga=0;
        int IDSezon=0;


        if(qLiga.size()!=0)
        {
            while(qLiga.next())
            {
                IDLiga=qLiga.value("IDLiga").toInt();
                IDSezon=qLiga.value("IDSezon").toInt();
            }
        }

        QString zapytanie = "SELECT u.Imie,u.Nazwisko, r.suma_punktow_sezon AS Punkty, w.Wygrane, rem.Remisy, p.Przegrane"
                " FROM ranking_sezon AS r "
                " left join uzytkownik as u on(u.IDUzytkownik=r.IDZawodnik) "
                " left join przegrane_sezon_calosc as p on(u.IDUzytkownik=p.IDZawodnik AND  p.IDSezon= r.IDSezon)"
                " left join wygrane_sezon_calosc as w on(u.IDUzytkownik=w.IDZawodnik AND  w.IDSezon= r.IDSezon)"
                " left join remisy_sezon_calosc as rem on(u.IDUzytkownik=rem.IDZawodnik AND rem.IDSezon= r.IDSezon)"
                " WHERE r.IDLiga=" +QString::number(IDLiga)+" AND r.IDSezon= "+QString::number(IDSezon)+" ORDER BY punkty DESC ";
        qmodel->setQuery(zapytanie);//w zależności od wybranej ligi (A,B,C) wyświetla tabele w klubie zawodnika

    }
    else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
}




void ZawodnikTabela::on_comboBoxPoziom_currentTextChanged(const QString &arg1)
{
    refreshModel(zawodnik);
}

void ZawodnikTabela::on_comboBoxSezon_currentTextChanged(const QString &arg1)
{
    refreshModel(zawodnik);
}
