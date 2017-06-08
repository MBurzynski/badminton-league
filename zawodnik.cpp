#include "zawodnik.h"

Zawodnik::Zawodnik()
{

}

Zawodnik::Zawodnik(QString imie, QString nazwisko, QString login, QString email, int IDZawodnik)
{
    this->imie=imie;
    this->nazwisko=nazwisko;
    this->login=login;
    this->email=email;
    this->IDZawodnik=IDZawodnik;
}

QString Zawodnik::getImie() const
{
    return imie;
}

void Zawodnik::setImie(const QString &value)
{
    imie = value;
}

QString Zawodnik::getNazwisko() const
{
    return nazwisko;
}

void Zawodnik::setNazwisko(const QString &value)
{
    nazwisko = value;
}

QString Zawodnik::getLogin() const
{
    return login;
}

void Zawodnik::setLogin(const QString &value)
{
    login = value;
}

QString Zawodnik::getEmail() const
{
    return email;
}

void Zawodnik::setEmail(const QString &value)
{
    email = value;
}

int Zawodnik::getIDZawodnik() const
{
    return IDZawodnik;
}

void Zawodnik::setIDZawodnik(int value)
{
    IDZawodnik = value;
}

QString Zawodnik::getKlub() const
{
    return klub;
}

void Zawodnik::setKlub(const QString &value)
{
    klub = value;
}

QString Zawodnik::getLigaPoziom() const
{
    return ligaPoziom;
}

void Zawodnik::setLigaPoziom(const QString &value)
{
    ligaPoziom = value;
}

int Zawodnik::getIDLiga() const
{
    return IDLiga;
}

void Zawodnik::setIDLiga(int value)
{
    IDLiga = value;
}

int Zawodnik::getPozycjaLiga() const
{
    return pozycjaLiga;
}

void Zawodnik::setPozycjaLiga(int value)
{
    pozycjaLiga = value;
}

int Zawodnik::getPunktyLiga() const
{
    return punktyLiga;
}

void Zawodnik::setPunktyLiga(int value)
{
    punktyLiga = value;
}

int Zawodnik::getWygrane() const
{
    return wygrane;
}

void Zawodnik::setWygrane(int value)
{
    wygrane = value;
}

int Zawodnik::getPrzegrane() const
{
    return przegrane;
}

void Zawodnik::setPrzegrane(int value)
{
    przegrane = value;
}

int Zawodnik::getRemisy() const
{
    return remisy;
}

void Zawodnik::setRemisy(int value)
{
    remisy = value;
}

int Zawodnik::getWygraneKolejki() const
{
    return wygraneKolejki;
}

void Zawodnik::setWygraneKolejki(int value)
{
    wygraneKolejki = value;
}

int Zawodnik::getIDKlub() const
{
    return IDKlub;
}

void Zawodnik::setIDKlub(int value)
{
    IDKlub = value;
}

int Zawodnik::getIDSezon() const
{
    return IDSezon;
}

void Zawodnik::setIDSezon(int value)
{
    IDSezon = value;
}

int Zawodnik::getPozycjaOgolny() const
{
    return pozycjaOgolny;
}

void Zawodnik::setPozycjaOgolny(int value)
{
    pozycjaOgolny = value;
}

int Zawodnik::getPunktyOgolny() const
{
    return punktyOgolny;
}

void Zawodnik::setPunktyOgolny(int value)
{
    punktyOgolny = value;
}

