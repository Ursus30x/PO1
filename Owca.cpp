#include "Owca.h"

Owca::Owca(const Coords2d pos, Swiat* swiat,int id,int wiek) : Zwierze(IKONA,id,wiek,SILA,INICJATYWA,KOLOR,swiat,pos){}

Organizm* Owca::getChild(const Coords2d pos){return new Owca(pos,getSwiat());}