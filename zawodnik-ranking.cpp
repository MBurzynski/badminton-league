#include "zawodnik-ranking.h"
#include "ui_zawodnik-ranking.h"
#include "QtDebug"

ZawodnikRanking::ZawodnikRanking(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZawodnikRanking)
{
    ui->setupUi(this);

    qmodel=new QSqlQueryModel();
    ui->tableView->setModel(qmodel);
    refreshModel();
}

ZawodnikRanking::~ZawodnikRanking()
{
    delete qmodel;
    delete ui;
}

void ZawodnikRanking::refreshModel()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen())
    {
        qmodel->setQuery("SELECT CONCAT(u.Imie, ' ',u.Nazwisko) AS Zawodnik, SUM((rs.Suma_punktow_sezon*l.Punkty_za_mecz/2)) AS Punkty FROM ranking_sezon as RS join liga AS l on (rs.IDLiga = l.IDLiga) join uzytkownik as u on(u.IDUzytkownik=rs.IDZawodnik) GROUP BY rs.IDZawodnik ORDER BY punkty DESC");//wyswietla ranking ogólny wszytkich zawodnikow (z jakiego są klubu, ile punktow )
    }
    else qDebug() <<"Nie udało się odświeżyć listy usług. Brak połączenia z bazą!";
}



void ZawodnikRanking::on_lineEdit_textChanged(const QString &arg1)
{
    QString filter = ui->lineEdit->text();

    QString zapytanie = "SELECT CONCAT(u.Imie, ' ',u.Nazwisko) AS Zawodnik, SUM((rs.Suma_punktow_sezon*l.Punkty_za_mecz/2)) AS Punkty FROM ranking_sezon as RS join liga AS l on (rs.IDLiga = l.IDLiga) join uzytkownik as u on(u.IDUzytkownik=rs.IDZawodnik) WHERE u.imie LIKE '"+ filter + "%' OR u.nazwisko LIKE '"+ filter + "%' OR CONCAT(u.imie, ' ',u.nazwisko) LIKE '"+ filter + "%' GROUP BY rs.IDZawodnik ORDER BY punkty DESC";

    qmodel->setQuery(zapytanie);
}
