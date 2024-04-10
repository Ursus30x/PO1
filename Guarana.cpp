#include "Guarana.h"
#include "Swiat.h"



Guarana::Guarana(const Coords2d pos, Swiat* swiat,int id,int wiek): Roslina(IKONA,id,wiek,SILA,KOLOR,swiat,pos){}

Organizm* Guarana::getChild(const Coords2d pos){return new Guarana(pos,getSwiat());}


#define THIS_ORGANISM getIkona() + to_string(getId()) 
#define OTHER_ORGANISM other->getIkona() + to_string(other->getId())
void Guarana::kolizja(Organizm * other){
    string temp = "";
    if(getSila() >= other->getSila()){
        temp += THIS_ORGANISM + " zatrul " + OTHER_ORGANISM;
        getSwiat()->zabijOrganizm(other);
        getSwiat()->zabijOrganizm(this);
    }
    else{
        other->setSila(other->getSila()+3);
        temp += OTHER_ORGANISM + " zjadl " + THIS_ORGANISM + " i zmenil sile na " + to_string(other->getSila());
        getSwiat()->zabijOrganizm(this);
    }
    getSwiat()->addLog(temp);

}