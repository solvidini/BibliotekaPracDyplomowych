#pragma once
#ifndef PRACA_H
#define PRACA_H
#include <string>
#include <iostream>

using namespace std;

class Praca
{
    private:
        size_t id;
        string typPracy;
        string tytul;
        string nazwiskoAutora;
        string imionaAutora;
        size_t rok;
        string nazwiskoPromotora;
        string imionaPromotora;
        string slowaKluczowe;
        string streszczenie;
    public:
        Praca();
        Praca(size_t ID, string TYP, string TYTUL, string NAZWISKO_A, string IMIONA_A, size_t ROK, string NAZWISKO_P, string IMIONA_P, string SLOWA, string STRESZCZENIE) :
             id(ID),
             typPracy(TYP),
             tytul(TYTUL),
             nazwiskoAutora(NAZWISKO_A),
             imionaAutora(IMIONA_A),
             rok(ROK),
             nazwiskoPromotora(NAZWISKO_P),
             imionaPromotora(IMIONA_P),
             slowaKluczowe(SLOWA),
             streszczenie(STRESZCZENIE)
             {};

        virtual ~Praca();

        virtual void addData();

        virtual void wyswietlSkrocony();

        virtual void wyswietlPelny();

        virtual size_t getId() { return id; }

        virtual string getTypPracy() { return typPracy; }

        virtual string getSlowaKluczowe(){ return slowaKluczowe; }

        virtual string getNazwiskoPromotora(){ return nazwiskoPromotora; }

        virtual string getImionaPromotora(){ return imionaPromotora; }

        virtual string getNazwiskoAutora() { return nazwiskoAutora; }

        virtual string getTytul() { return tytul; }

        virtual string getStreszczenie() { return streszczenie; }

        virtual size_t getRok() { return rok; }

        virtual void edit();
};

#endif // PRACA_H
