#include <vector>
#include <typeinfo>
#include "Zwierze.h"
#include "Swiat.h"

Zwierze::Zwierze(char ikona,int id,int wiek,int sila,int inicjatywa,int paraKolorow,Swiat* swiat,Coords2d pos)
: Organizm(ikona,id,wiek,sila,inicjatywa,paraKolorow,swiat,pos){}
    

void Zwierze::setXMove(int move){xMove = move;}
void Zwierze::setYMove(int move){yMove = move;}
int Zwierze::getXMove(){return xMove;}
int Zwierze::getYMove(){return yMove;}

#define WORLD_SIZE_Y getSwiat()->getSizeY()
#define WORLD_SIZE_X getSwiat()->getSizeX()
void Zwierze::akcja(){
    xMove = randMove();
    yMove = randMove();

    while(getPozycja().x + xMove < 0 
    || getPozycja().x + xMove >= WORLD_SIZE_X){
        xMove = randMove();
    }
    while(getPozycja().y + yMove < 0 
    || getPozycja().y + yMove >= WORLD_SIZE_Y){
        yMove = randMove();
    }

    setPorzedniaPozycja(getPozycja());
    setPozycja({getPozycja().x+xMove,getPozycja().y+yMove});
}

//todo
//organism can go out of bounds when spawning
//fix it lol

#define NOT_MOVING (x == 0 && y == 0)
#define OUT_OF_BOUNDS_X (getPozycjaX()+x > 0 && getPozycjaX()+x < getSwiat()->getSizeX())
#define OUT_OF_BOUNDS_Y (getPozycjaY()+y > 0 && getPozycjaY()+y < getSwiat()->getSizeY())
#define OUT_OF_BOUNDS (OUT_OF_BOUNDS_X && OUT_OF_BOUNDS_Y)

void Zwierze::createChild(const Coords2d pos){
    getSwiat()->getOrganizmy()->push_back(getChild(pos));
}

#define THIS_ORGANISM getIkona() + to_string(getId())
#define OTHER_ORGANISM other->getIkona() + to_string(other->getId())
#define MATURE_AGE 18
void Zwierze::kolizja(Organizm *other){
    string temp = "";
    if(typeid(*this) == typeid(*other)){
        std::vector <Coords2d> freePola = other->getFreeSquares();
        if(this->getWiek() < MATURE_AGE && other->getWiek() < MATURE_AGE){
            temp +=  THIS_ORGANISM + " i " + OTHER_ORGANISM + " sa zbyt mlode by sie rozmnozyc";
        }
        else if(freePola.size() == 0){
            temp +=  THIS_ORGANISM + " i " + OTHER_ORGANISM + " nie maja miejsca by sie rozmnozyc";
        }
        else{
            int randomPole = (rand() % freePola.size());
            temp +=  THIS_ORGANISM + " rozmnozyl sie z " + OTHER_ORGANISM;
            createChild({freePola[randomPole].x,freePola[randomPole].y});
        }

        other->setPozycja(other->getPoprzedniaPozycja());
    }
    else if(getSila() >= other->getSila()){
        temp += THIS_ORGANISM + " zabil " + OTHER_ORGANISM;
        getSwiat()->zabijOrganizm(other);
    }
    else{
        temp += OTHER_ORGANISM + " zabil " + THIS_ORGANISM;
        getSwiat()->zabijOrganizm(this);
    }
    getSwiat()->addLog(temp);
    
}