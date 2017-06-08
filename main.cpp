#include "mainwindow-z.h"
#include "mainwindow-s.h"
#include <QApplication>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindowZ w1;
    w1.show();
    MainWindowS w2;
    //w2.show();

    return a.exec();
}
