#include "Roslina.h"

class Trawa : public Roslina{
    enum description{
        SILA = 0,
        IKONA = 'T',
        KOLOR = 2
    };
private:
    Organizm * getChild(const Coords2d pos) override;
public:
    Trawa(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
};