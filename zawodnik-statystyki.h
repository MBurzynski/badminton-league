#ifndef ZAWODNIKSTATYSTYKI_H
#define ZAWODNIKSTATYSTYKI_H

#include <QWidget>
#include <QtSql>
#include <zawodnik.h>

namespace Ui {
class ZawodnikStatystyki;
}

class ZawodnikStatystyki : public QWidget
{
    Q_OBJECT

public:
    explicit ZawodnikStatystyki(QWidget *parent = 0);
    ~ZawodnikStatystyki();
    void refreshModel(Zawodnik *zawodnik=NULL);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::ZawodnikStatystyki *ui;
    QSqlQueryModel *qmodel;
    Zawodnik *zawodnik;
};


#endif // ZAWODNIKSTATYSTYKI_H
