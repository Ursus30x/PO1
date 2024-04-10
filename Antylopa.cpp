#include "Antylopa.h"

Antylopa::Antylopa(const Coords2d pos, Swiat* swiat,int id,int wiek) : Zwierze(IKONA,id,wiek,SILA,INICJATYWA,KOLOR,swiat,pos){}

#define RAND_FORMULA ((rand() % 5) - 2)
int Antylopa::randMove(){
    return RAND_FORMULA;
}

#define DICE rand() % 2
void Antylopa::kolizja(Organizm* other){
    if(DICE){
        setXMove(0);
        setYMove(0);
        while(findCollsion() != nullptr){
            setPozycja(getPoprzedniaPozycja());
            akcja();
        }
    }
    else{
        Zwierze::kolizja(other);
    }
}


Organizm* Antylopa::getChild(const Coords2d pos){return new Antylopa(pos,getSwiat());}