#include "Zwierze.h"

class Wilk : public Zwierze{
    enum description{
        SILA = 9,
        INICJATYWA = 5,
        IKONA = 'W',
        KOLOR = 3
    };
private:
    Organizm * getChild(const Coords2d pos) override;
public:
    Wilk(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
};