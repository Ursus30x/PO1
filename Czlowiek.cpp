#include "Swiat.h"
#include "Zwierze.h"
#include "Czlowiek.h"


#define ARROW_UP 65
#define ARROW_DOWN 66
#define ARROW_RIGHT 67
#define ARROW_LEFT 68




Czlowiek::Czlowiek(const Coords2d pos, Swiat* swiat,int id,int wiek) : Zwierze(IKONA,id,wiek,SILA,INICJATYWA,KOLOR,swiat,pos){
    setXMove(0);
    setYMove(0);
    uzyjUmiejetnosci = false;
}

#define WORLD_SIZE_Y getSwiat()->getSizeY()
#define WORLD_SIZE_X getSwiat()->getSizeX()

void Czlowiek::updateMove(char key){
    switch(key){
        case ARROW_UP:
            if(getYMove() > -1 && getPozycja().y > 0 )setYMove(getYMove()-1);
            break;
        case ARROW_DOWN:
            if(getYMove() < 1 && getPozycja().y+1 < WORLD_SIZE_Y )setYMove(getYMove()+1);
            break;
        case ARROW_RIGHT:
            if(getYMove() < 1 && getPozycja().x +1 < WORLD_SIZE_X)setXMove(getXMove()+1);
            break;
        case ARROW_LEFT:
            if(getYMove() > -1 && getPozycja().x  > 0)setXMove(getXMove()-1);
            break;
        default:
            break;
    }
}

void Czlowiek::akcja(){
    setPozycja({getPozycja().x +getXMove(),getPozycja().y+getYMove()});
    setXMove(0);
    setYMove(0);
    if(uzyjUmiejetnosci)specjalnaUmiejetnosc();
}

Organizm* Czlowiek::getChild(const Coords2d pos){return new Czlowiek(pos,getSwiat());}

void Czlowiek::specjalnaUmiejetnosc(){
    for(int x = -1;x<=1;x++){
        for(int y = -1;y<=1;y++){
            Coords2d pos = {getPozycja().x + x,getPozycja().y + y};
            Organizm * other = findCollsion(pos);
            if(other != nullptr && !(x == 0 && y == 0)){
                string log = "";
                log += other->getIkona() + to_string(other->getId()) + " zostaje spalony calopaleniem";
                getSwiat()->zabijOrganizm(other);
                getSwiat()->addLog(log);
            }
        }
    }
    uzyjUmiejetnosci = false;
}

void Czlowiek::aktywujUmiejetnosc(){
    uzyjUmiejetnosci = true;
}