#include "WilczeJagody.h"
#include "Swiat.h"

WilczeJagody::WilczeJagody(const Coords2d pos, Swiat* swiat,int id,int wiek): Roslina(IKONA,id,wiek,SILA,KOLOR,swiat,pos){}

Organizm* WilczeJagody::getChild(const Coords2d pos){return new WilczeJagody(pos,getSwiat());}


#define THIS_ORGANISM getIkona() + to_string(getId()) 
#define OTHER_ORGANISM other->getIkona() + to_string(other->getId())
void WilczeJagody::kolizja(Organizm * other){
    string temp = "";
    temp += THIS_ORGANISM + " zatrul " + OTHER_ORGANISM;
    getSwiat()->zabijOrganizm(other);
    getSwiat()->zabijOrganizm(this);
    getSwiat()->addLog(temp);
}