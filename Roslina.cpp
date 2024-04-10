#include "Roslina.h"



Roslina::Roslina(char ikona,int id,int wiek,int sila,int paraKolorow,Swiat* swiat,Coords2d pos)
: Organizm(ikona,id,wiek,sila,INICJIATYWA,paraKolorow,swiat,pos){}
    


void Roslina::createChild(const Coords2d pos){
    getSwiat()->getOrganizmy()->push_back(getChild(pos));
}


#define SPREADING_CHANCE (rand()%30)
#define WORLD_SIZE_Y getSwiat()->getSizeY()
#define WORLD_SIZE_X getSwiat()->getSizeX()
#define THIS_ORGANISM getIkona() + to_string(getId()) 
#define OTHER_ORGANISM other->getIkona() + to_string(other->getId())
void Roslina::akcja(){
    if(getWiek() < 2 || SPREADING_CHANCE != 0)return;
    string temp = "";
    std::vector <Coords2d> freePola = getFreeSquares();
    if(freePola.size() == 0){
        temp+= THIS_ORGANISM + " nie mogl sie zasiac pola przez brak miejsca";
    }
    else{
        int randomPole = (rand() % freePola.size());
        temp += THIS_ORGANISM + " zasial pole obok";
        createChild({freePola[randomPole].x,freePola[randomPole].y});
    }
    getSwiat()->addLog(temp);
}

void Roslina::kolizja(Organizm *other){
    string temp = "";
    if(getSila() >= other->getSila()){
        temp += THIS_ORGANISM + " zatrul " + OTHER_ORGANISM;
        getSwiat()->zabijOrganizm(other);
        getSwiat()->zabijOrganizm(this);
    }
    else{
        temp += OTHER_ORGANISM + " zjadl " + THIS_ORGANISM;
        getSwiat()->zabijOrganizm(this);
    }
    getSwiat()->addLog(temp);

}