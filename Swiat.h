#include <iostream>
#include <vector>
#include <string>
#include "ncurses++.h"
#include "Organizm.h"
#pragma once

class Organizm;
class Czlowiek;

class Swiat{
    Window * worldWin;
    Window * infoWin;
    Window * logWin;
    
    std::string nazwa;
    int idCounter;
    int tura;
    int sizeX;
    int sizeY;
    std::vector <Organizm*> organizmy;
    std::vector <string> turnLog;
    Czlowiek* humanHandle;
    
private:
    void wykonajTure();
    void rysujSwiat()const;
    void dodajOrganizm(Organizm &nowyOrganizm);
    Organizm* getOrganizm(char ikona,Coords2d pozycja,int id = -1,int wiek = 0);
    static bool compareInicjatywa(Organizm *obj1,Organizm *obj2);
    void sortOrganizm();
    void printWorldInfo() const;
    void printWorldLog() const;
    void printWindows()const;
    void saveLogs() const;
    void createLogFile() const;
    void saveWorld() const;
    Organizm * getOrganizmFromFile(istringstream &ss);
public:
    Swiat(ifstream &save);
    Swiat(std::string nazwa,int sizeX, int sizeY);
    void dodajOrganizmy();
    void testWorld();
    void symuluj();
    void zabijOrganizm(Organizm* martwy);
    void addLog(string &log);
    void setIdCounter(const int counter);

    //getters
    std::string getName() const;
    int getSizeX() const;
    int getSizeY() const;
    int getIdCounter() const;
    int getTurn() const;
    std::vector <Organizm*>* getOrganizmy();



};