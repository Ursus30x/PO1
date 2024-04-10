#include "Organizm.h"
#include "Swiat.h"
#include <cstdlib>
#include <vector>

Organizm::Organizm(char ikona,int id,int wiek,int sila,int inicjatywa,int paraKolorow,Swiat* swiat,Coords2d pos){
    this->ikona = ikona;
    this->wiek = wiek;
    this->sila = sila;
    this->inicjatywa = inicjatywa;
    this->paraKolorow = paraKolorow;
    this->swiat = swiat;
    this->pozycja = pos;
    this->poprzedniaPozycja = pos;

    //deafult value for id
    if(id == AUTOID){
        this->id = swiat->getIdCounter();
        swiat->setIdCounter(this->id+1);
    }
    else{
        this->id = id;
    }
}
    


void Organizm::rysuj(Window *worldWin){
    worldWin->oattron(COLOR_PAIR(paraKolorow));
    worldWin->omvprint(pozycja.x+1,pozycja.y+1,ikona);
    worldWin->oattroff(COLOR_PAIR(paraKolorow));
}

#define RAND_FORMULA ((rand() % 3) - 1)
int Organizm::randMove(){
    return RAND_FORMULA;
}

Organizm* Organizm::findCollsion(){
    std::vector <Organizm*>* handle = swiat->getOrganizmy();
    for(int i = 0;i<handle->size();i++){
        if((*handle)[i]->getPozycja().equals(getPozycja())
        && (*handle)[i] != this){
            return (*handle)[i];
        }
    }
    return nullptr;
}

Organizm* Organizm::findCollsion(const Coords2d pos){
    std::vector <Organizm*>* handle = swiat->getOrganizmy();
    for(int i = 0;i<handle->size();i++){
        if((*handle)[i]->getPozycja().equals(pos)){
            return (*handle)[i];
        }
    }
    return nullptr;
}

std::vector <Coords2d> Organizm::getFreeSquares(){
    std::vector <Coords2d> freePola;
    for(int x = -1;x<=1;x++){
        for(int y = -1;y<=1;y++){
            Coords2d pos = {getPozycja().x + x, getPozycja().y + y};
            if(inWorldBounds(pos) 
            && findCollsion(pos) == nullptr 
            && !(getPoprzedniaPozycja().equals(pos))
            )
            freePola.push_back(pos);
        }
    }
    return freePola;
}

bool Organizm::inWorldBounds(const Coords2d pos){
    if(0 <= pos.x && pos.x < getSwiat()->getSizeX() 
    && 0 <= pos.y && pos.y < getSwiat()->getSizeY())return true;
    else return false;
}

int Organizm::getId() const{
    return id;
}

int Organizm::getWiek() const{
    return wiek;
}
int Organizm::getSila() const{
    return sila;
}

int Organizm::getInicjatywa() const{
    return inicjatywa;
}

char Organizm::getIkona() const{
    return ikona;
}

Swiat* Organizm::getSwiat() const{
    return swiat;
}

Coords2d Organizm::getPozycja() const{
    return pozycja;
}

void Organizm::setPozycja(const Coords2d pozycja){
    this->pozycja = pozycja;
}

Coords2d Organizm::getPoprzedniaPozycja() const{
    return poprzedniaPozycja;
}

void Organizm::setPorzedniaPozycja(const Coords2d pozycja){
    this->poprzedniaPozycja = pozycja;
}

void Organizm::setWiek(const int wiek){
    this->wiek = wiek;
}

void Organizm::setSila(const int sila){
    this->sila = sila;
}

Organizm::~Organizm(){}