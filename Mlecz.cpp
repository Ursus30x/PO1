#include "Mlecz.h"
#include "Swiat.h"

Mlecz::Mlecz(const Coords2d pos, Swiat* swiat,int id,int wiek): Roslina(IKONA,id,wiek,SILA,KOLOR,swiat,pos){}

Organizm* Mlecz::getChild(const Coords2d pos){return new Mlecz(pos,getSwiat());}

void Mlecz::akcja(){
    for(int i = 0;i<3;i++){
        Roslina::akcja();
    }
}