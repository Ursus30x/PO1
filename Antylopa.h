#include "Zwierze.h"
#pragma once



class Antylopa : public Zwierze{
    enum description{
        SILA = 4,
        INICJATYWA = 4,
        IKONA = 'A',
        KOLOR = 6
    };
private:
    Organizm * getChild(const Coords2d pos) override;
    int randMove() override;
public:
    Antylopa(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
    void kolizja(Organizm* other) override;
};