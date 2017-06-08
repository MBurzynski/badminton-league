#include "mainwindow-z.h"
#include "ui_mainwindow-z.h"
#include "QtDebug"

MainWindowZ::MainWindowZ(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowZ)
{

    //Nawiązanie połączenia z bazą
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("ligabadmintona1");
    db.setUserName("root");
    db.setPassword("");

    //Próba otwarcia połączenia
    if(!db.open())
        qDebug() <<"Błąd połączenia z bazą";
    else
        qDebug()<<"Połączono się z bazą";

    ui->setupUi(this);

    QSqlQuery qZawodnicy;
    qZawodnicy.exec("SELECT u.Imie, u.Nazwisko, u.Email, u.Login FROM `uzytkownik` AS u JOIN uzytkowniktypy AS t ON(t.IDUzytkownik_typy=u.Typ) WHERE t.Nazwa LIKE ('Zawodnik')");


    if(qZawodnicy.size()!=0)
    {
        while(qZawodnicy.next())
        {
            imie=qZawodnicy.value("imie").toString().toUtf8().constData();

            nazwisko=qZawodnicy.value("nazwisko").toString().toUtf8().constData();

            imie_nazwisko=imie+" "+nazwisko;
            zawodnicy.append(imie_nazwisko);
            zawodnicy_imie_nazwisko.append(imie_nazwisko);

            email=qZawodnicy.value("email").toString().toUtf8().constData();
            zawodnicy.append(email);
            zawodnicy_email.append(email);

            login=qZawodnicy.value("login").toString().toUtf8().constData();
            zawodnicy.append(login);
            zawodnicy_login.append(login);
        }
    }

    completer = new QCompleter(zawodnicy,this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_Zawodnik->setCompleter(completer);

    ui->lineEdit_imie->setDisabled(true);
    ui->lineEdit_nazwisko->setDisabled(true);
    ui->lineEdit_klub->setDisabled(true);
    ui->lineEdit_kolejki->setDisabled(true);
    ui->lineEdit_liga->setDisabled(true);
    ui->lineEdit_liga_pozycja->setDisabled(true);
    ui->lineEdit_liga_punkty->setDisabled(true);
    ui->lineEdit_ranking_pozycja->setDisabled(true);
    ui->lineEdit_ranking_punkty->setDisabled(true);
    ui->lineEdit_mecze_przegrane->setDisabled(true);
    ui->lineEdit_mecze_wygrane->setDisabled(true);
    ui->lineEdit_mecze_rozegrane->setDisabled(true);
    ui->lineEdit_mecze_zremisowane->setDisabled(true);

//   //kod przykładowy
//    ui->lineEdit_imie->setText("Jan");
//    ui->lineEdit_nazwisko->setText("Kowalski");
//    ui->lineEdit_klub->setText("Iskra Mokotow");
//    ui->lineEdit_kolejki->setText("2");
//    ui->lineEdit_liga->setText("B");
//    ui->lineEdit_liga_pozycja->setText("3");
//    ui->lineEdit_liga_punkty->setText("27");
//    ui->lineEdit_ranking_pozycja->setText("197");
//    ui->lineEdit_ranking_punkty->setText("60");
//    ui->lineEdit_mecze_przegrane->setText("9");
//    ui->lineEdit_mecze_wygrane->setText("9");
//    ui->lineEdit_mecze_rozegrane->setText("28");
//    ui->lineEdit_mecze_zremisowane->setText("10");

}

MainWindowZ::~MainWindowZ()
{
    db.close();
    delete ui;
    if (zawodnik!=NULL)
        delete zawodnik;
    if (completer!=NULL)
        delete completer;
}


void MainWindowZ::on_pushButton_2_clicked()
{

}

void MainWindowZ::on_lineEdit_Zawodnik_returnPressed()
{
    QString wyszukanyZawodnik = ui->lineEdit_Zawodnik->text();
    qDebug()<<wyszukanyZawodnik;

    QSqlQuery qZawodnik;
    QString imieTmp;
    QString nazwiskoTmp, emailTmp, loginTmp;
    int IDZawodnikTmp;

    if (zawodnicy_imie_nazwisko.contains(wyszukanyZawodnik))
    {
        QStringList imieNazwiskoTmp = wyszukanyZawodnik.split(' ');
        imieTmp = imieNazwiskoTmp.first();
        nazwiskoTmp = imieNazwiskoTmp.last();
        qZawodnik.prepare("SELECT * FROM uzytkownik WHERE imie=:imie AND nazwisko=:nazwisko");
        qZawodnik.bindValue(":imie",imieTmp);
        qZawodnik.bindValue(":nazwisko",nazwiskoTmp);

        if(qZawodnik.exec()&&qZawodnik.size()!=0)
        {
            while(qZawodnik.next())
            {
                emailTmp=qZawodnik.value("email").toString().toUtf8().constData();
                loginTmp=qZawodnik.value("login").toString().toUtf8().constData();
                IDZawodnikTmp=qZawodnik.value("IDUzytkownik").toInt();

                zawodnik = new Zawodnik(imieTmp,nazwiskoTmp,loginTmp,emailTmp,IDZawodnikTmp);
                qDebug()<<imieTmp<<nazwiskoTmp<<emailTmp<<loginTmp<<IDZawodnikTmp;

            }
        }
        else
        {
            qDebug()<<"Nie udało się wyszukać zawodnika";
        }



    }
    else if(zawodnicy_email.contains(wyszukanyZawodnik))
    {
        emailTmp=wyszukanyZawodnik;
        qZawodnik.prepare("SELECT * FROM uzytkownik WHERE email=:email");
        qZawodnik.bindValue(":email",emailTmp);

        if(qZawodnik.exec()&&qZawodnik.size()!=0)
        {
            while(qZawodnik.next())
            {
                imieTmp=qZawodnik.value("imie").toString().toUtf8().constData();
                nazwiskoTmp=qZawodnik.value("nazwisko").toString().toUtf8().constData();
                loginTmp=qZawodnik.value("login").toString().toUtf8().constData();
                IDZawodnikTmp=qZawodnik.value("IDUzytkownik").toInt();

                zawodnik = new Zawodnik(imieTmp,nazwiskoTmp,loginTmp,emailTmp,IDZawodnikTmp);
                qDebug()<<imieTmp<<nazwiskoTmp<<emailTmp<<loginTmp<<IDZawodnikTmp;

            }
        }
        else
        {
            qDebug()<<"Nie udało się wyszukać zawodnika";
        }


    }
    else if(zawodnicy_login.contains(wyszukanyZawodnik))
    {
        loginTmp=wyszukanyZawodnik;
        qZawodnik.prepare("SELECT * FROM uzytkownik WHERE login=:login");
        qZawodnik.bindValue(":login",loginTmp);

        if(qZawodnik.exec()&&qZawodnik.size()!=0)
        {
            while(qZawodnik.next())
            {
                imieTmp=qZawodnik.value("imie").toString().toUtf8().constData();
                nazwiskoTmp=qZawodnik.value("nazwisko").toString().toUtf8().constData();
                emailTmp=qZawodnik.value("email").toString().toUtf8().constData();
                IDZawodnikTmp=qZawodnik.value("IDUzytkownik").toInt();

                zawodnik = new Zawodnik(imieTmp,nazwiskoTmp,loginTmp,emailTmp,IDZawodnikTmp);
                qDebug()<<imieTmp<<nazwiskoTmp<<emailTmp<<loginTmp<<IDZawodnikTmp;

            }
        }
        else
        {
            qDebug()<<"Nie udało się wyszukać zawodnika";
        }

    }

    QSqlQuery qProfil;
    qProfil.prepare("SELECT u.*,k.Nazwa,k.IDKlub,l.Poziom_trudnosci, l.IDLiga  FROM uzytkownik AS u JOIN zawodnikliga AS zl ON(u.IDUzytkownik=zl.IDZawodnik) JOIN liga as l USING(IDLiga) JOIN klub as k USING(IDKlub) WHERE u.IDUzytkownik = :IDZawodnika");
    qProfil.bindValue(":IDZawodnika",zawodnik->getIDZawodnik());

    QString klub,ligaPoziom;
    int IDLiga, IDKlub;
    if(qProfil.exec()&&qProfil.size()!=0)
    {
        while(qProfil.next())
        {
            klub=qProfil.value("nazwa").toString().toUtf8().constData();
            ligaPoziom=qProfil.value("Poziom_trudnosci").toString().toUtf8().constData();
            IDLiga=qProfil.value("IDLiga").toInt();
            IDKlub=qProfil.value("IDKlub").toInt();


            zawodnik->setKlub(klub);
            zawodnik->setIDLiga(IDLiga);
            zawodnik->setIDKlub(IDKlub);
            zawodnik->setLigaPoziom(ligaPoziom);
            qDebug()<<imieTmp<<nazwiskoTmp<<emailTmp<<loginTmp<<IDZawodnikTmp<<klub<<ligaPoziom;

        }
    }
    else
    {
        qDebug()<<"Nie udało się wyszukać zawodnika";
    }

    QSqlQuery qSezon;
    QString zapytanieSezon = "SELECT ls.IDSezon FROM ligasezon AS ls join sezon as s USING (IDSezon) where CURRENT_DATE>s.Data_rozpoczecia AND CURRENT_DATE < s.Data_zakonczenia AND ls.IDLiga= " + QString::number(zawodnik->getIDLiga());

    if(qSezon.exec(zapytanieSezon)&&qSezon.size()!=0)
    {
        while(qSezon.next())
        {
            int sezon =qSezon.value("IDSezon").toInt();
            zawodnik->setIDSezon(sezon);
        }
    }


    QSqlQuery qRankingLiga;
    QString zapytanie = " SELECT @rank := @rank + 1 AS Pozycja, r.IDZawodnik, r.Suma_punktow_sezon"
                        " FROM ranking_sezon AS r JOIN (SELECT @rank := 0) AS t"
                        " WHERE r.IDSezon =" + QString::number(zawodnik->getIDSezon());
    int ranking;
    int punkty;


    qDebug() << zapytanie;

    if(qRankingLiga.exec(zapytanie)&&qRankingLiga.size()!=0)
    {
        while(qRankingLiga.next())
        {
            int idZaw = qRankingLiga.value("IDZawodnik").toInt();
            if(idZaw  == zawodnik->getIDZawodnik())
            {
                ranking=qRankingLiga.value("Pozycja").toInt();
                punkty=qRankingLiga.value("Suma_punktow_sezon").toInt();
                zawodnik->setPunktyLiga(punkty);
                zawodnik->setPozycjaLiga(ranking);
            }
            qDebug()<<ranking<<punkty;
        }
    }
    else
    {
        qDebug()<<"Nie udało się ustalić pozycji zawodnika";
    }


    QSqlQuery qRankingOgolny;
    zapytanie.clear();
    zapytanie = " SELECT @rank := @rank + 1 AS Pozycja, r.Zawodnik, r.Punkty"
                        " FROM (SELECT u.IDUzytkownik AS Zawodnik, SUM((rs.Suma_punktow_sezon*l.Punkty_za_mecz/2)) AS Punkty FROM ranking_sezon as RS join liga AS l on (rs.IDLiga = l.IDLiga) join uzytkownik as u on(u.IDUzytkownik=rs.IDZawodnik) GROUP BY rs.IDZawodnik ORDER BY punkty DESC) AS r JOIN (SELECT @rank := 0) AS t";
    int rankingOgolny;
    int punktyOgolny;


    qDebug() << zapytanie;

    if(qRankingOgolny.exec(zapytanie)&&qRankingOgolny.size()!=0)
    {
        while(qRankingOgolny.next())
        {
            int idZaw = qRankingOgolny.value("Zawodnik").toInt();
            if(idZaw  == zawodnik->getIDZawodnik())
            {
                rankingOgolny=qRankingOgolny.value("Pozycja").toInt();
                punktyOgolny=qRankingOgolny.value("Punkty").toInt();
                zawodnik->setPunktyOgolny(punktyOgolny);
                zawodnik->setPozycjaOgolny(rankingOgolny);
            }
            qDebug()<<ranking<<punkty;
        }
    }
    else
    {
        qDebug()<<"Nie udało się ustalić pozycji zawodnika";
    }

    QSqlQuery qStatystyki;
    qStatystyki.prepare("SELECT COUNT(*) AS Liczba_wygranych FROM mecz WHERE Set_1A>Set_1B AND Set_2A>Set_2B AND (IDZawodnikA1 = :IDZawodnik OR IDZawodnikA2 = :IDZawodnik)");
    qStatystyki.bindValue(":IDZawodnik",zawodnik->getIDZawodnik());

    int wygraneA;

    if(qStatystyki.exec()&&qStatystyki.size()!=0)
    {
        while(qStatystyki.next())
        {
            wygraneA=qStatystyki.value("Liczba_wygranych").toInt();
        }
    }
    else
    {
        qDebug()<<"Nie można obliczyć wygranych A";
    }

    qStatystyki.clear();
    qStatystyki.prepare("SELECT COUNT(*) AS Liczba_wygranych FROM mecz WHERE Set_1B>Set_1A AND Set_2B>Set_2A AND (IDZawodnikB1 = :IDZawodnik OR IDZawodnikB2 = :IDZawodnik)");
    qStatystyki.bindValue(":IDZawodnik",zawodnik->getIDZawodnik());

    int wygraneB;

    if(qStatystyki.exec()&&qStatystyki.size()!=0)
    {
        while(qStatystyki.next())
        {
            wygraneB=qStatystyki.value("Liczba_wygranych").toInt();
        }
    }
    else
    {
        qDebug()<<"Nie można obliczyć wygranych B";
    }

    int wygrane = wygraneA + wygraneB;
    zawodnik->setWygrane(wygrane);

    qStatystyki.clear();
    qStatystyki.prepare("SELECT COUNT(*) AS Liczba_przegranych FROM mecz WHERE Set_1A<Set_1B AND Set_2A<Set_2B AND (IDZawodnikA1 = :IDZawodnik OR IDZawodnikA2 = :IDZawodnik)");
    qStatystyki.bindValue(":IDZawodnik",zawodnik->getIDZawodnik());

    int przegraneA;

    if(qStatystyki.exec()&&qStatystyki.size()!=0)
    {
        while(qStatystyki.next())
        {
            przegraneA=qStatystyki.value("Liczba_przegranych").toInt();
        }
    }
    else
    {
        qDebug()<<"Nie można obliczyć wygranych A";
    }

    qStatystyki.clear();
    qStatystyki.prepare("SELECT COUNT(*) AS Liczba_przegranych FROM mecz WHERE Set_1B<Set_1A AND Set_2B<Set_2A AND (IDZawodnikB1 = :IDZawodnik OR IDZawodnikB2 = :IDZawodnik)");
    qStatystyki.bindValue(":IDZawodnik",zawodnik->getIDZawodnik());

    int przegraneB;

    if(qStatystyki.exec()&&qStatystyki.size()!=0)
    {
        while(qStatystyki.next())
        {
            przegraneB=qStatystyki.value("Liczba_przegranych").toInt();
        }
    }
    else
    {
        qDebug()<<"Nie można obliczyć wygranych B";
    }

    int przegrane = przegraneA + przegraneB;
    zawodnik->setPrzegrane(przegrane);

    qStatystyki.clear();
    qStatystyki.prepare("SELECT COUNT(*) AS Liczba_remisow FROM mecz WHERE ((Set_1A<Set_1B AND Set_2A>Set_2B) OR (Set_1A>Set_1B AND Set_2A<Set_2B)) AND (IDZawodnikA1 = :IDZawodnik OR IDZawodnikA2 = :IDZawodnik OR IDZawodnikB1 = :IDZawodnik OR IDZawodnikB2 = :IDZawodnik)");
    qStatystyki.bindValue(":IDZawodnik",zawodnik->getIDZawodnik());

    int remisy;

    if(qStatystyki.exec()&&qStatystyki.size()!=0)
    {
        while(qStatystyki.next())
        {
            remisy=qStatystyki.value("Liczba_remisow").toInt();
        }
    }
    else
    {
        qDebug()<<"Nie można obliczyć wygranych A";
    }


    zawodnik->setRemisy(remisy);

    int rozegrane_mecze = wygrane+przegrane+remisy;

    qStatystyki.clear();
    qStatystyki.prepare("SELECT COUNT(*) AS Wygrane_kolejki FROM (SELECT *, MAX(suma_punktow) FROM `suma_punktow` GROUP BY IDKolejka) as k WHERE IDZawodnik = :IDZawodnik");
    qStatystyki.bindValue(":IDZawodnik",zawodnik->getIDZawodnik());

    int wygraneKolejki;

    if(qStatystyki.exec()&&qStatystyki.size()!=0)
    {
        while(qStatystyki.next())
        {
            wygraneKolejki=qStatystyki.value("Wygrane_kolejki").toInt();
        }
    }
    else
    {
        qDebug()<<"Nie można obliczyć wygranych kolejek";
    }

    zawodnik->setWygraneKolejki(wygraneKolejki);


    ui->lineEdit_imie->setText(zawodnik->getImie());
    ui->lineEdit_nazwisko->setText(zawodnik->getNazwisko());
    ui->lineEdit_klub->setText(zawodnik->getKlub());
    ui->lineEdit_kolejki->setText(QString::number(zawodnik->getWygraneKolejki()));
    ui->lineEdit_liga->setText(zawodnik->getLigaPoziom());
    ui->lineEdit_liga_pozycja->setText(QString::number(zawodnik->getPozycjaLiga()));
    ui->lineEdit_liga_punkty->setText(QString::number(zawodnik->getPunktyLiga()));
    ui->lineEdit_ranking_pozycja->setText(QString::number(zawodnik->getPozycjaOgolny()));
    ui->lineEdit_ranking_punkty->setText(QString::number(zawodnik->getPunktyOgolny()));
    ui->lineEdit_mecze_wygrane->setText(QString::number(zawodnik->getWygrane()));
    ui->lineEdit_mecze_przegrane->setText(QString::number(zawodnik->getPrzegrane()));
    ui->lineEdit_mecze_rozegrane->setText(QString::number(rozegrane_mecze));
    ui->lineEdit_mecze_zremisowane->setText(QString::number(zawodnik->getRemisy()));

    on_tabWidget_tabBarClicked(0);

}

void MainWindowZ::on_tabWidget_tabBarClicked(int index)
{
    ui->widget_terminarz->refreshModel(zawodnik);
    ui->widget_platnosci->refreshModel(zawodnik);
    ui->widget_tabela->refreshModel(zawodnik);
    ui->widget_historia->refreshModel(zawodnik);
    ui->widget_statystyki->refreshModel(zawodnik);
}
