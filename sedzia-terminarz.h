#ifndef SEDZIATERMINARZ
#define SEDZIATERMINARZ

#include <QWidget>
#include <QtSql>

namespace Ui {
class SedziaTerminarz;
}

class SedziaTerminarz : public QWidget
{
    Q_OBJECT

public:
    explicit SedziaTerminarz(QWidget *parent = 0);
    ~SedziaTerminarz();

private:
    Ui::SedziaTerminarz *ui;
    QSqlQueryModel *qmodel;
    void refreshModel();
};

#endif // SEDZIATERMINARZ

