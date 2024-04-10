#include "Roslina.h"

class BarszczSosnowskiego : public Roslina{
    enum description{
        SILA = 10,
        IKONA = 'B',
        KOLOR = 7
    };
private:
    Organizm * getChild(const Coords2d pos) override;

public:
    BarszczSosnowskiego(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
    void kolizja(Organizm *other) override;
};