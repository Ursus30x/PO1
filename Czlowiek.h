#include "Zwierze.h"
#pragma once

class Czlowiek : public Zwierze{
    enum description{
        SILA = 5,
        INICJATYWA = 4,
        IKONA = 'C',
        KOLOR = 1
    };
private:
    bool uzyjUmiejetnosci;
    Organizm * getChild(const Coords2d pos) override;
    void specjalnaUmiejetnosc();
public:
    Czlowiek(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
    void updateMove(char key);
    void akcja() override;
    void aktywujUmiejetnosc();
    //void kolizja(Organizm *other) override;
};