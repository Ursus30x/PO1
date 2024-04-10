#include "Zwierze.h"

class Lis : public Zwierze{
    enum description{
        SILA = 3,
        INICJATYWA = 7,
        IKONA = 'L',
        KOLOR = 7
    };
private:
    Organizm * getChild(const Coords2d pos) override;
public:
    Lis(const Coords2d pos,Swiat* swiat,int id = AUTOID,int wiek = 0);
    void akcja() override;
};