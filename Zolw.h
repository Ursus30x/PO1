#include "Zwierze.h"
#pragma once


class Zolw : public Zwierze{
    enum description{
        SILA = 2,
        INICJATYWA = 1,
        IKONA = 'Z',
        KOLOR = 2
    };
private:
    Organizm * getChild(const Coords2d pos) override;
public:
    Zolw(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
    void akcja() override;
    void kolizja(Organizm* other) override;
};