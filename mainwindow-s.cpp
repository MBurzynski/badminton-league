#include "mainwindow-s.h"
#include "ui_mainwindow-s.h"
#include "QtDebug"

MainWindowS::MainWindowS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowS)
{
    /*
     //Nawiązanie połączenia z bazą
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("liga_badmintona");
    db.setUserName("admin");
    db.setPassword("admin");
*/

    //Próba otwarcia połączenia
    //if(!db.open()) qDebug() <<"Błąd połączenia z bazą";

    ui->setupUi(this);

}

MainWindowS::~MainWindowS()
{
    db.close();
    delete ui;
}


