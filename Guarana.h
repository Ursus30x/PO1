#include "Roslina.h"

class Guarana : public Roslina{
    enum description{
        SILA = 0,
        IKONA = 'G',
        KOLOR = 4
    };
private:
    Organizm * getChild(const Coords2d pos) override;

public:
    Guarana(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
    void kolizja(Organizm * other) override;

};