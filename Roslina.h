#include "Organizm.h"
#include "Swiat.h"
#pragma once

#define INICJIATYWA 0

class Roslina : public Organizm{
protected:
    Roslina(char ikona,int id,int wiek,int sila,int paraKolorow,Swiat* swiat,Coords2d pos);
    virtual Organizm * getChild(const Coords2d pos) = 0;
    void createChild(const Coords2d pos);

public:
    void akcja() override;
    void kolizja(Organizm *other) override;
};