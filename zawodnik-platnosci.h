#ifndef ZAWODNIKPLATNOSCI
#define ZAWODNIKPLATNOSCI

#include <QWidget>
#include <QtSql>
#include <zawodnik.h>

namespace Ui {
class ZawodnikPlatnosci;
}

class ZawodnikPlatnosci : public QWidget
{
    Q_OBJECT

public:
    explicit ZawodnikPlatnosci(QWidget *parent = 0);
    ~ZawodnikPlatnosci();
    void refreshModel(Zawodnik *zawodnik=NULL);


private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::ZawodnikPlatnosci *ui;
    QSqlQueryModel *qmodel;
    Zawodnik *zawodnik;
};


#endif // ZAWODNIKPLATNOSCI

