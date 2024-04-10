#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "ncurses++.h"
#include "Swiat.h"
#include "Czlowiek.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

#define ARROW_UP 65
#define ARROW_DOWN 66
#define ARROW_RIGHT 67
#define ARROW_LEFT 68
#define ENTER 13

#define BORDER_MARGIN 2
#define INFO_WINDOW_Y 4
#define SIDE_PANE_SIZE 60

Swiat::Swiat(std::string nazwa,int sizeX, int sizeY){
    this->nazwa = nazwa;
    this->sizeX = sizeX;
    this->sizeY = sizeY;

    this->worldWin = new Window(sizeX + BORDER_MARGIN,sizeY + BORDER_MARGIN);
    this->infoWin = new Window(SIDE_PANE_SIZE,INFO_WINDOW_Y,sizeX+BORDER_MARGIN,0);
    this->logWin = new Window(SIDE_PANE_SIZE,sizeY+BORDER_MARGIN-INFO_WINDOW_Y,sizeX+BORDER_MARGIN,INFO_WINDOW_Y);

    this->tura = 0;
    this->humanHandle = nullptr;
    createLogFile();
}

#define ORGANISM_LIST {"C - Czlowiek","     ---Zwierzeta---     ","1. W - Wilk","2. O - Owca","3. L - Lis","4. Z - Zolw","5. A - Antylopa","     ----Rosliny----    ","1. T - Trawa","2. M - Mlecz","3. G - Guarana","4. J - Wilcze Jagody","5. B - Barszcz Sosnowskiego"}
#define ORGANISM_INPUT_INFO {"Write END on New Organism prompt to finish adding creatures"}

void Swiat::dodajOrganizmy(){
    InfoPrompt organismInfo("Organisms",ORGANISM_LIST,30,20,50,0);
    InfoPrompt userInfo("Info",ORGANISM_INPUT_INFO,80,6,0,20);
    string ikona = "";
    int x = 0,y = 0;
    bool czlowiekPresent = false;

    organismInfo.showPrompt();
    userInfo.showPrompt();
    while(true){
        ikona = stringInput("New Organism",50,10);
        if(ikona == "END")break;

        x = intInput("X Position",50,10);
        y = intInput("Y Position",50,10);

        if(ikona[0] == 'C'){
            if(czlowiekPresent)continue;
            czlowiekPresent = true;
        }

        organizmy.push_back(getOrganizm(ikona[0],{x,y}));
    }
}

#define RANDO (rand() % 20)
void Swiat::testWorld(){
    humanHandle = new Czlowiek({10,10},this);
    organizmy.push_back(humanHandle);
    organizmy.push_back(new Antylopa({RANDO,RANDO},this));
    organizmy.push_back(new Antylopa({RANDO,RANDO},this));

    organizmy.push_back(new Zolw({RANDO,RANDO},this));
    organizmy.push_back(new Zolw({RANDO,RANDO},this));

    organizmy.push_back(new Owca({RANDO,RANDO},this));
    organizmy.push_back(new Owca({RANDO,RANDO},this));

    organizmy.push_back(new Wilk({RANDO,RANDO},this));
    organizmy.push_back(new Wilk({RANDO,RANDO},this)); 

    organizmy.push_back(new Trawa({RANDO,RANDO},this));

    organizmy.push_back(new Mlecz({RANDO,RANDO},this));

    organizmy.push_back(new Guarana({RANDO,RANDO},this));
    
}

bool Swiat::compareInicjatywa(Organizm *obj1,Organizm *obj2){
    if(obj1->getInicjatywa() == obj2->getInicjatywa())return (obj1->getWiek() > obj2->getWiek());
    return (obj1->getInicjatywa() > obj2->getInicjatywa());
}

void Swiat::sortOrganizm(){
    sort(organizmy.begin(),organizmy.end(),compareInicjatywa);
}

Organizm* Swiat::getOrganizm(char ikona,Coords2d pozycja,int id,int wiek){
    switch(ikona){
        case 'C':
            humanHandle = new Czlowiek(pozycja,this,id,wiek);
            return humanHandle;
        case 'W':
            return new Wilk(pozycja,this,id,wiek);
        case 'O':
            return new Owca(pozycja,this,id,wiek);
        case 'L':
            return new Lis(pozycja,this,id,wiek);
        case 'Z':
            return new Zolw(pozycja,this,id,wiek);
        case 'A':
            return new Antylopa(pozycja,this,id,wiek);
        case 'T':
            return new Trawa(pozycja,this,id,wiek);
        case 'M':
            return new Mlecz(pozycja,this,id,wiek);
        case 'G':
            return new Guarana(pozycja,this,id,wiek);
        case 'J':
            return new WilczeJagody(pozycja,this,id,wiek);
        case 'B':
            return new BarszczSosnowskiego(pozycja,this,id,wiek);
        default:
            break;
    }

    return nullptr;
}

void Swiat::rysujSwiat() const{
    worldWin->clear();
    worldWin->createBorder();
    for(int i = 0;i<organizmy.size();i++){
        organizmy[i]->rysuj(worldWin);
    }

    worldWin->refresh();
}

void Swiat::wykonajTure(){
    for(int i = 0;i<organizmy.size();i++){
        Organizm* other = nullptr;
        organizmy[i]->akcja();
        organizmy[i]->setWiek(organizmy[i]->getWiek()+1);
        other = organizmy[i]->findCollsion();
        if(other !=  nullptr)other->kolizja(organizmy[i]);
    }
}

void Swiat::printWorldInfo() const{
    string turnCounter = "Turn: " + to_string(tura);
    string organismCounter = "Organisms: " + to_string(organizmy.size());

    infoWin->clear();
    infoWin->createBorder();
    infoWin->omvprint(2,1,turnCounter);
    infoWin->omvprint(2,2,organismCounter);
    infoWin->refresh();
}

#define PAGE_SIZE (sizeY-INFO_WINDOW_Y)

int page = 0;//change it later to class in ncurses++
void Swiat::printWorldLog() const{
    logWin->clear();
    logWin->createBorder();

    logWin->omvprint(2,0,"Log Page: " + to_string(page) + "  Log Entries: " + to_string(turnLog.size()));
    for(int i = 0;i+(page*PAGE_SIZE)<turnLog.size() && i < PAGE_SIZE;i++){
        logWin->omvprint(2,1+i,turnLog[i+(PAGE_SIZE*page)]);
    }

    logWin->refresh();
}

void Swiat::printWindows()const{
    rysujSwiat();
    printWorldInfo();
    printWorldLog();
}


void Swiat::symuluj(){
    curs_set(0);
    char key = 0;

    while(key != 'q'){
        sortOrganizm();
        if(ARROW_UP <= key && key <= ARROW_LEFT){
            if(humanHandle != nullptr)humanHandle->updateMove(key);
        }
        else if(key == ENTER){
            turnLog.clear();
            page = 0;
            wykonajTure();

            tura++;
        }
        else if(key == 's'){
            if(humanHandle != nullptr)humanHandle->aktywujUmiejetnosc();
        }
        else if(key == '[' && page > 0){
            page--;
        }
        else if(key == ']' && page < turnLog.size()/PAGE_SIZE){
            page++;
        }
        saveLogs();
        saveWorld();
        printWindows();
        key = getchar();
    }
}

void Swiat::zabijOrganizm(Organizm *martwy){
    if(martwy == nullptr)return;
    if(martwy == humanHandle)humanHandle = nullptr;
    int i;
    for(i = 0;i<organizmy.size();i++){
        if(organizmy[i]==martwy)break;
    }
    organizmy.erase(organizmy.begin()+i);
    
}

std::vector <Organizm*>* Swiat::getOrganizmy() {return &organizmy;}
std::string Swiat::getName() const {return nazwa;}
int Swiat::getSizeX() const {return sizeX;}
int Swiat::getSizeY() const {return sizeY;}
int Swiat::getTurn() const {return tura;}



void Swiat::addLog(string &log){
    turnLog.push_back(log);
}

void Swiat::saveLogs() const{
    ofstream logs;
    logs.open("saves/" + nazwa + ".log",ios::app);
    logs << "Tura: " << tura << " Wydarzenia: " << turnLog.size() << endl;
    for(int i = 0;i<turnLog.size();i++){
        logs << turnLog[i] << endl;
    }
    logs << "-------------------"<< endl;
    logs.close();
}

void Swiat::createLogFile() const{
    ofstream logs("saves/" + nazwa + ".log");
    logs << "-----LOG START-----\n";
    logs.close();
}

void Swiat::saveWorld() const{
    ofstream save("saves/" +  nazwa + ".sav");
    save    << nazwa << " " << tura << " " << idCounter << " "
            << sizeX << " " << sizeY << endl;
    for(Organizm * org : organizmy){
        save    << org->getIkona()<< " " << org->getId() << " " 
                << org->getWiek() << " "  << org->getSila() << " "
                << org->getPozycja().x << " " << org->getPozycja().y << " " 
                << endl;
    }
    save.close();
}

Swiat::Swiat(ifstream &save){
    string str;
    getline(save,str);
    istringstream ss(str);
    ss >> this->nazwa >> this->tura >> this->idCounter >> this->sizeX >> this->sizeY;
    this->worldWin = new Window(sizeX + BORDER_MARGIN,sizeY + BORDER_MARGIN);
    this->infoWin = new Window(SIDE_PANE_SIZE,INFO_WINDOW_Y,sizeX+BORDER_MARGIN,0);
    this->logWin = new Window(SIDE_PANE_SIZE,sizeY+BORDER_MARGIN-INFO_WINDOW_Y,sizeX+BORDER_MARGIN,INFO_WINDOW_Y);
    this->humanHandle = nullptr;
    

    //chcialem to zrobic !save.eof() ale wtedy crashuje na ostatnim organizmie
    while(getline(save,str)){
        istringstream ss(str);
        organizmy.push_back(getOrganizmFromFile(ss));
    }
}

Organizm* Swiat::getOrganizmFromFile(istringstream &ss){
    char ikona;
    int id,wiek,sila;
    Coords2d pozycja;

    ss  >> ikona >> id >> wiek >> sila 
        >> pozycja.x >> pozycja.y ;

    Organizm * handle = getOrganizm(ikona,pozycja,id,wiek);
    handle->setSila(sila);
    return handle;
}

int Swiat::getIdCounter()const{
    return idCounter;
}

void Swiat::setIdCounter(const int counter){
    idCounter = counter;
}