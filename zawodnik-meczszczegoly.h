#ifndef ZAWODNIKMECZSZCZEGOLY
#define ZAWODNIKMECZSZCZEGOLY

#include <QDialog>
#include <QtSql>

namespace Ui {
class ZawodnikMecz;
}

class ZawodnikMecz : public QDialog
{
    Q_OBJECT

public:
    explicit ZawodnikMecz(int mecz_id, QWidget *parent = 0);
    ~ZawodnikMecz();

private:
    Ui::ZawodnikMecz *ui;
    int mecz_id;
    int kolejka;
    int numerKortu;
    int IDA1;
    int IDA2;
    int IDB1;
    int IDB2;
    int set1A;
    int set1B;
    int set2A;
    int set2B;
    QString sezon;
    QString liga;
    QString godzina;
    QString dataRozegrania;
    QString graczA1;
    QString graczA2;
    QString graczB1;
    QString graczB2;

};

#endif // ZAWODNIKMECZSZCZEGOLY

