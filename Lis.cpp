#include "Lis.h"

Lis::Lis(const Coords2d pos, Swiat* swiat,int id,int wiek) : Zwierze(IKONA,id,wiek,SILA,INICJATYWA,KOLOR,swiat,pos){}

void Lis::akcja(){
    Organizm * collison;

    setXMove(0);
    setYMove(0);
    do{
        setPozycja(getPoprzedniaPozycja());
        Zwierze::akcja();
        collison = findCollsion();
        if(collison == nullptr)break;
    }while(collison->getSila() > getSila());
}

Organizm* Lis::getChild(const Coords2d pos){return new Lis(pos,getSwiat());}