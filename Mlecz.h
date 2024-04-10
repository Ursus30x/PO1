#include "Roslina.h"

class Mlecz : public Roslina{
    enum description{
        SILA = 0,
        IKONA = 'M',
        KOLOR = 5
    };
private:
    Organizm * getChild(const Coords2d pos) override;
public:
    Mlecz(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
    void akcja() override;

};