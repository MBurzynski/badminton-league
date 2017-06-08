#ifndef ZAWODNIKTABELA
#define ZAWODNIKTABELA

#include <QWidget>
#include <QtSql>
#include <zawodnik.h>

namespace Ui {
class ZawodnikTabela;
}

class ZawodnikTabela : public QWidget
{
    Q_OBJECT

public:
    explicit ZawodnikTabela(QWidget *parent = 0);
    ~ZawodnikTabela();
    void refreshModel(Zawodnik *zawodnik);


private slots:
    void on_comboBoxPoziom_currentTextChanged(const QString &arg1);

    void on_comboBoxSezon_currentTextChanged(const QString &arg1);

private:
    Ui::ZawodnikTabela *ui;
    QSqlQueryModel *qmodel;
    Zawodnik *zawodnik;
    QString ligaPoziomString;
    int ligaPoziom;
};

#endif // ZAWODNIKTABELA

