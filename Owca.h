#include "Zwierze.h"


class Owca : public Zwierze{
    enum description{
        SILA = 4,
        INICJATYWA = 4,
        IKONA = 'O',
        KOLOR = 1
    };
private:
    Organizm * getChild(const Coords2d pos) override;
public:
    Owca(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
};