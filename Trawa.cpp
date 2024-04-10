#include "Trawa.h"
#include "Swiat.h"

Trawa::Trawa(const Coords2d pos, Swiat* swiat,int id,int wiek): Roslina(IKONA,id,wiek,SILA,KOLOR,swiat,pos){}

Organizm* Trawa::getChild(const Coords2d pos){return new Trawa(pos,getSwiat());}