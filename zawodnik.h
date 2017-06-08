#ifndef ZAWODNIK_H
#define ZAWODNIK_H
#include <QString>

class Zawodnik
{
public:
    Zawodnik();
    Zawodnik(QString imie,QString nazwisko,QString login,QString email,int IDZawodnik);

    QString getImie() const;
    void setImie(const QString &value);

    QString getNazwisko() const;
    void setNazwisko(const QString &value);

    QString getLogin() const;
    void setLogin(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    int getIDZawodnik() const;
    void setIDZawodnik(int value);

    QString getKlub() const;
    void setKlub(const QString &value);

    QString getLigaPoziom() const;
    void setLigaPoziom(const QString &value);

    int getIDLiga() const;
    void setIDLiga(int value);

    int getPozycjaLiga() const;
    void setPozycjaLiga(int value);

    int getPunktyLiga() const;
    void setPunktyLiga(int value);

    int getWygrane() const;
    void setWygrane(int value);

    int getPrzegrane() const;
    void setPrzegrane(int value);

    int getRemisy() const;
    void setRemisy(int value);

    int getWygraneKolejki() const;
    void setWygraneKolejki(int value);

    int getIDKlub() const;
    void setIDKlub(int value);

    int getIDSezon() const;
    void setIDSezon(int value);

    int getPozycjaOgolny() const;
    void setPozycjaOgolny(int value);

    int getPunktyOgolny() const;
    void setPunktyOgolny(int value);

private:
    QString imie;
    QString nazwisko;
    QString login;
    QString email;
    QString klub;
    QString ligaPoziom;
    int IDZawodnik;
    int IDLiga;
    int IDKlub;
    int IDSezon;
    int pozycjaLiga;
    int pozycjaOgolny;
    int punktyLiga;
    int punktyOgolny;
    int wygrane;
    int przegrane;
    int remisy;
    int wygraneKolejki;
};

#endif // ZAWODNIK_H
