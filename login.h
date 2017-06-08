#ifndef LOGIN
#define LOGIN

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
/*
private slots:
    void on_pushButton_zawodnik_clicked();

    void on_pushButton_sedzia_clicked();

    void on_pushButton_menadzer_clicked(); */

private:
    Ui::Login *ui;
};

#endif // LOGIN

