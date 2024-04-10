#include "Zolw.h"

Zolw::Zolw(const Coords2d pos, Swiat* swiat,int id,int wiek) : Zwierze(IKONA,id,wiek,SILA,INICJATYWA,KOLOR,swiat,pos){}

#define DICE (rand() % 4)
void Zolw::akcja(){
    if(DICE == 0){
        Zwierze::akcja();
    }
}

#define THIS_ORGANISM getIkona() + to_string(getId())
#define OTHER_ORGANISM other->getIkona() + to_string(other->getId())
void Zolw::kolizja(Organizm* other){
    string temp = "";
    if(getIkona() == other->getIkona()){
        temp +=  THIS_ORGANISM + " rozmnozyl sie z " + OTHER_ORGANISM;
        getSwiat()->addLog(temp);
       //rozmnoz();
        setPozycja({getPozycja().x-getXMove(),getPozycja().y-getYMove()});
    }
    else if(getSila() > 5){
        temp += THIS_ORGANISM + " zabil " + OTHER_ORGANISM;
        getSwiat()->addLog(temp);
        getSwiat()->zabijOrganizm(other);
    }
    else{
        temp += OTHER_ORGANISM + " uciekl od " + THIS_ORGANISM;
        setPozycja(getPoprzedniaPozycja());
    }   
}

Organizm* Zolw::getChild(const Coords2d pos){return new Zolw(pos,getSwiat());}