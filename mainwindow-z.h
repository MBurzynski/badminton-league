#ifndef MAINWINDOWZ
#define MAINWINDOWZ

#include <QMainWindow>
#include <QtSql>
#include <QCompleter>
#include <QDirModel>
#include <zawodnik.h>

namespace Ui {
class MainWindowZ;
}

class MainWindowZ : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowZ(QWidget *parent = 0);
    ~MainWindowZ();
    QSqlDatabase db;
private slots:
    void on_pushButton_2_clicked();

    void on_lineEdit_Zawodnik_returnPressed();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindowZ *ui;
    QCompleter *completer;
    Zawodnik *zawodnik;
    QString imie, nazwisko,imie_nazwisko, email, login;
    QStringList zawodnicy, zawodnicy_imie_nazwisko,zawodnicy_email,zawodnicy_login;
};

#endif // MAINWINDOWZ

