#include "BarszczSosnowskiego.h"
#include "Swiat.h"



BarszczSosnowskiego::BarszczSosnowskiego(const Coords2d pos, Swiat* swiat,int id,int wiek): Roslina(IKONA,id,wiek,SILA,KOLOR,swiat,pos){}

Organizm* BarszczSosnowskiego::getChild(const Coords2d pos){return new BarszczSosnowskiego(pos,getSwiat());}


#define THIS_ORGANISM getIkona() + to_string(getId()) 
#define OTHER_ORGANISM other->getIkona() + to_string(other->getId())
void BarszczSosnowskiego::kolizja(Organizm * other){
    string temp = "";
    temp += THIS_ORGANISM + " zatrul " + OTHER_ORGANISM;
    getSwiat()->zabijOrganizm(other);
    getSwiat()->zabijOrganizm(this);
    getSwiat()->addLog(temp);
}