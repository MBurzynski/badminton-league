#ifndef SEDZIATABELE
#define SEDZIATABELE

#include <QWidget>
#include <QtSql>

namespace Ui {
class SedziaTabele;
}

class SedziaTabele : public QWidget
{
    Q_OBJECT

public:
    explicit SedziaTabele(QWidget *parent = 0);
    ~SedziaTabele();

private:
    Ui::SedziaTabele *ui;
    QSqlQueryModel *qmodel;
    void refreshModel();
};

#endif // SEDZIATABELE

