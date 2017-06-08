#ifndef ZAWODNIKHISTORIA
#define ZAWODNIKHISTORIA

#include <QWidget>
#include <QtSql>
#include "zawodnik.h"

namespace Ui {
class ZawodnikHistoria;
}

class ZawodnikHistoria : public QWidget
{
    Q_OBJECT

public:
    explicit ZawodnikHistoria(QWidget *parent = 0);
    ~ZawodnikHistoria();
     void refreshModel(Zawodnik *zawodnik=NULL);


private slots:

    void on_comboBox_sezon_currentTextChanged(const QString &arg1);

    void on_comboBox_kolejka_currentTextChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_wszystkie_mecze_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_Szczegoly_clicked();

private:
    Ui::ZawodnikHistoria *ui;
    QSqlQueryModel *qmodel;
    Zawodnik * zawodnik;
    int numerkolejki;
    int IDKolejka;
    int IDSezon;
    QString godzina;
    QString data;
    QString przeciwnik;

    bool wszystkieMecze;
};

#endif // ZAWODNIKHISTORIA

