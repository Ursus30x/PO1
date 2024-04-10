#include "Wilk.h"


Wilk::Wilk(const Coords2d pos, Swiat* swiat,int id,int wiek) : Zwierze(IKONA,id,wiek,SILA,INICJATYWA,KOLOR,swiat,pos){}


Organizm* Wilk::getChild(const Coords2d pos){return new Wilk(pos,getSwiat());}