#ifndef SEDZIAEDYTUJMECZ
#define SEDZIAEDYTUJMECZ

#include <QDialog>

namespace Ui {
class SedziaEdytujMecz;
}

class SedziaEdytujMecz : public QDialog
{
    Q_OBJECT

public:
    explicit SedziaEdytujMecz(int mecz_id, QWidget *parent = 0);
    ~SedziaEdytujMecz();

private slots:
    void on_debel_checkBox_toggled(bool checked);

private:
    Ui::SedziaEdytujMecz *ui;
    int mecz_id;
};

#endif // SEDZIAEDYTUJMECZ

