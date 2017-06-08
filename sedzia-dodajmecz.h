#ifndef SEDZIADODAJMECZ
#define SEDZIADODAJMECZ

#include <QDialog>

namespace Ui {
class SedziaNowyMecz;
}

class SedziaNowyMecz : public QDialog
{
    Q_OBJECT

public:
    explicit SedziaNowyMecz(QWidget *parent = 0);
    ~SedziaNowyMecz();

private slots:
    void on_checkBox_toggled(bool checked);

private:
    Ui::SedziaNowyMecz *ui;
    int liga_id;
    int kolejka_id;
};

#endif // SEDZIADODAJMECZ

