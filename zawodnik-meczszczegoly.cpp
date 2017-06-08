#include "zawodnik-meczszczegoly.h"
#include "ui_zawodnik-meczszczegoly.h"


ZawodnikMecz::ZawodnikMecz(int mecz_id, QWidget *parent):
    QDialog(parent),
    ui(new Ui::ZawodnikMecz)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->debel_checkBox->setDisabled(true);

    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    ui->lineEdit_6->setDisabled(true);
    ui->lineEdit_7->setDisabled(true);
    ui->lineEdit_8->setDisabled(true);
    ui->lineEdit_9->setDisabled(true);
    ui->lineEdit_10->setDisabled(true);
    ui->lineEdit_11->setDisabled(true);
    ui->lineEdit_12->setDisabled(true);
    ui->lineEdit_13->setDisabled(true);
    ui->lineEdit_14->setDisabled(true);
    ui->lineEdit_15->setDisabled(true);

    //kod testowy
    ui->lineEdit->setText("Jan Kowalski");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("Tomasz Nowak");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("2");
    ui->lineEdit_6->setText("13:30");
    ui->lineEdit_7->setText("21");
    ui->lineEdit_8->setText("23");
    ui->lineEdit_9->setText("16");
    ui->lineEdit_10->setText("21");
    ui->lineEdit_11->setText("16/17 zima");
    ui->lineEdit_12->setText("2");
    ui->lineEdit_13->setText("A");
    ui->lineEdit_14->setText("7.01.17");
    ui->lineEdit_15->setText("Wygrana A");



    QString zapytanie = " SELECT mecz.*, kolejka.Data_rozegrania, kolejka.Numer, CASE liga.Poziom_trudnosci WHEN 1 THEN 'A' WHEN 2 THEN 'B' WHEN 3 THEN 'C' END AS 'Poziom_trudnosci' , CONCAT(CASE sezon.rodzaj WHEN 1 THEN 'Letni' WHEN 2 THEN 'Zimowy' WHEN 3 THEN 'Wakacyjny' END , ' ',YEAR(sezon.Data_rozpoczecia)) AS Sezon_rok FROM mecz join kolejka USING(IDkolejka) join sezon using(idsezon) join ligasezon USING (IDSezon) join liga USING (idliga) WHERE mecz.IDMecz = "+ QString::number(mecz_id);
    QSqlQuery qMecz;
    qMecz.exec(zapytanie);

    IDA1 = 0;
    IDA2 = 0;
    IDB1 = 0;
    IDB2 = 0;

    if(qMecz.size()!=0)
    {
        while(qMecz.next())
        {
            dataRozegrania = qMecz.value("Data_rozegrania").toString().toUtf8().constData();
            kolejka = qMecz.value("Numer").toInt();
            numerKortu = qMecz.value("Numer_kortu").toInt();
            IDA1 = qMecz.value("IDZawodnikA1").toInt();
            IDA2 = qMecz.value("IDZawodnikA2").toInt();
            IDB1 = qMecz.value("IDZawodnikB1").toInt();
            IDB2 = qMecz.value("IDZawodnikB2").toInt();
            set1A = qMecz.value("Set_1A").toInt();
            set1B = qMecz.value("Set_1B").toInt();
            set2A = qMecz.value("Set_2A").toInt();
            set2B = qMecz.value("Set_2B").toInt();
            sezon = qMecz.value("Sezon_rok").toString().toUtf8().constData();
            liga = qMecz.value("Poziom_trudnosci").toString().toUtf8().constData();
            godzina = qMecz.value("Godzina").toString().toUtf8().constData();
        }
    }

    zapytanie.clear();
    zapytanie = "select CONCAT(u.imie, ' ', u.nazwisko) AS Zawodnik from uzytkownik AS u where u.IDUzytkownik = " + QString::number(IDA1);
    QSqlQuery qZawodnik;
    qZawodnik.exec(zapytanie);

    graczA1 = "";
    if(qZawodnik.size()!=0)
    {
        while(qZawodnik.next())
        {
            graczA1 = qZawodnik.value("Zawodnik").toString().toUtf8().constData();
        }
    }

    zapytanie.clear();
    zapytanie = "select CONCAT(u.imie, ' ', u.nazwisko) AS Zawodnik from uzytkownik AS u where u.IDUzytkownik = " + QString::number(IDA2);
    qZawodnik.clear();
    qZawodnik.exec(zapytanie);
    graczA2 = "";
    if(qZawodnik.size()!=0)
    {
        while(qZawodnik.next())
        {
            graczA2 = qZawodnik.value("Zawodnik").toString().toUtf8().constData();
        }
    }
    graczB1 = "";
    zapytanie.clear();
    zapytanie = "select CONCAT(u.imie, ' ', u.nazwisko) AS Zawodnik from uzytkownik AS u where u.IDUzytkownik = " + QString::number(IDB1);
    qZawodnik.clear();
    qZawodnik.exec(zapytanie);

    if(qZawodnik.size()!=0)
    {
        while(qZawodnik.next())
        {
            graczB1 = qZawodnik.value("Zawodnik").toString().toUtf8().constData();
        }
    }
    graczB2 = "";
    zapytanie.clear();
    zapytanie = "select CONCAT(u.imie, ' ', u.nazwisko) AS Zawodnik from uzytkownik AS u where u.IDUzytkownik = " + QString::number(IDB2);
    qZawodnik.clear();
    qZawodnik.exec(zapytanie);

    if(qZawodnik.size()!=0)
    {
        while(qZawodnik.next())
        {
            graczB2 = qZawodnik.value("Zawodnik").toString().toUtf8().constData();
        }
    }

    ui->lineEdit->setText(graczA1);
    ui->lineEdit_2->setText(graczA2);
    ui->lineEdit_3->setText(graczB1);
    ui->lineEdit_4->setText(graczB2);
    ui->lineEdit_5->setText(QString::number(numerKortu));
    ui->lineEdit_6->setText(godzina);
    ui->lineEdit_7->setText(QString::number(set1A));
    ui->lineEdit_8->setText(QString::number(set2A));
    ui->lineEdit_9->setText(QString::number(set1B));
    ui->lineEdit_10->setText(QString::number(set2B));
    ui->lineEdit_11->setText(sezon);
    ui->lineEdit_12->setText(QString::number(kolejka));
    ui->lineEdit_13->setText(liga);
    ui->lineEdit_14->setText(dataRozegrania);

    if(set1A>set1B && set2A>set2B)
        ui->lineEdit_15->setText("Wygrana A");
    else if(set1A<set1B && set2A<set2B)
        ui->lineEdit_15->setText("Wygrana B");
    else
        ui->lineEdit_15->setText("Remis");


    if(IDA1!=0 &&IDB1!=0 &&IDA2!=0 &&IDB2!=0)
    {
        ui->debel_checkBox->setChecked(1);
    }

}

ZawodnikMecz::~ZawodnikMecz()
{
    delete ui;
}


