#pragma once
#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H
#include "Praca.h"

using namespace std;

class Biblioteka
{
    private:
        Praca * prace;
        size_t ilePrac;

    public:
        Biblioteka() : ilePrac(0) {
            prace = new Praca[1000];
        }

        virtual ~Biblioteka();

        virtual void loadFromFile();

        virtual void addByUser();

        virtual void add(Praca * p);

        virtual void wyswietlSkrocony();

        virtual void wyswietlPelny();

        virtual void editData();

        virtual void wyswietlZPodzialem();

        virtual void wyswietlNajczestszeSlowo();

        virtual void wyswietlWedlugPromotorow();

        virtual void wyszukajNaPodstawie();

};

#endif // BIBLIOTEKA_H
