#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T18:03:02
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LigaBadmintona
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow-z.cpp \
    zawodnik-tabela.cpp \
    zawodnik-terminarz.cpp \
    zawodnik-platnosci.cpp \
    zawodnik-ranking.cpp \
    zawodnik-historia.cpp \
    sedzia-tabele.cpp \
    mainwindow-s.cpp \
    sedzia-sedziowanie.cpp \
    sedzia-dodajmecz.cpp \
    sedzia-edytujmecz.cpp \
    sedzia-terminarz.cpp \
    zawodnik-meczszczegoly.cpp \
    zawodnik.cpp \
    zawodnik-statystyki.cpp

HEADERS  +=\
    mainwindow-z.h \
    zawodnik-tabela.h \
    zawodnik-terminarz.h \
    zawodnik-platnosci.h \
    zawodnik-ranking.h \
    zawodnik-historia.h \
    sedzia-tabele.h \
    mainwindow-s.h \
    sedzia-sedziowanie.h \
    sedzia-dodajmecz.h \
    sedzia-edytujmecz.h \
    sedzia-terminarz.h \
    zawodnik-meczszczegoly.h \
    zawodnik.h \
    zawodnik-statystyki.h

FORMS    +=\
    mainwindow-z.ui \
    mainwindow-s.ui \
    zawodnik-tabela.ui \
    zawodnik-terminarz.ui \
    zawodnik-platnosci.ui \
    zawodnik-ranking.ui \
    zawodnik-historia.ui \
    sedzia-tabele.ui \
    sedzia-sedziowanie.ui \
    sedzia-dodajmecz.ui \
    sedzia-edytujmecz.ui \
    sedzia-terminarz.ui \
    zawodnik-meczszczegoly.ui \
    zawodnik-statystyki.ui
