#ifndef ZAWODNIKRANKING
#define ZAWODNIKRANKING

#include <QWidget>
#include <QtSql>
#include <zawodnik.h>

namespace Ui {
class ZawodnikRanking;
}

class ZawodnikRanking : public QWidget
{
    Q_OBJECT

public:
    explicit ZawodnikRanking(QWidget *parent = 0);
    ~ZawodnikRanking();
    void refreshModel();


private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::ZawodnikRanking *ui;
    QSqlQueryModel *qmodel;
};


#endif // ZAWODNIKRANKING

