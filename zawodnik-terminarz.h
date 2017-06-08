#ifndef ZAWODNIKTERMINARZ
#define ZAWODNIKTERMINARZ

#include <QWidget>
#include <QtSql>
#include <zawodnik.h>

namespace Ui {
class ZawodnikTerminarz;
}

class ZawodnikTerminarz : public QWidget
{
    Q_OBJECT

public:
    explicit ZawodnikTerminarz(QWidget *parent = 0);
    ~ZawodnikTerminarz();
    void refreshModel(Zawodnik *zawodnik=NULL);
    void filter();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::ZawodnikTerminarz *ui;
    QSqlQueryModel *qmodel;
    Zawodnik *zawodnik;
    QString zapytanie;
};

#endif // ZAWODNIKTERMINARZ

