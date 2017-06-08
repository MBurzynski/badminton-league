#ifndef SEDZIAZARZADZAJ
#define SEDZIAZARZADZAJ

#include <QDialog>

namespace Ui {
class SedziaZarzadzaj;
}

class SedziaZarzadzaj : public QDialog
{
    Q_OBJECT

public:
    explicit SedziaZarzadzaj(QWidget *parent = 0);
    ~SedziaZarzadzaj();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SedziaZarzadzaj *ui;
};

#endif // SEDZIAZARZADZAJ

