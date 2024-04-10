#include "Roslina.h"

class WilczeJagody : public Roslina{
    enum description{
        SILA = 99,
        IKONA = 'J',
        KOLOR = 6
    };
private:
    Organizm * getChild(const Coords2d pos) override;
public:
    WilczeJagody(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
    void kolizja(Organizm *other) override;
};