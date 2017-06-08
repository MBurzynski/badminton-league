#ifndef SEDZIASEDZIOWANIE
#define SEDZIASEDZIOWANIE

#include <QWidget>
#include <QtSql>

namespace Ui {
class SedziaSedziowanie;
}

class SedziaSedziowanie : public QWidget
{
    Q_OBJECT

public:
    explicit SedziaSedziowanie(QWidget *parent = 0);
    ~SedziaSedziowanie();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::SedziaSedziowanie *ui;
    QSqlQueryModel *qmodel;
    void refreshModel();
};

#endif // SEDZIASEDZIOWANIE

