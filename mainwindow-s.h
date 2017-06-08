#ifndef MAINWINDOWS
#define MAINWINDOWS

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class MainWindowS;
}

class MainWindowS : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowS(QWidget *parent = 0);
    ~MainWindowS();
    QSqlDatabase db;
private:
    Ui::MainWindowS *ui;
};

#endif // MAINWINDOWS

