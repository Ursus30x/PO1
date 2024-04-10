#include "ncurses++.h"


#define AUTOID -1


#pragma once
class Swiat;
struct Coords2d{
    int x;
    int y;

    bool equals(Coords2d rhs){
        if(x == rhs.x && y == rhs.y)return true;
        else return false;
    }

    Coords2d& operator =(const Coords2d &other){
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    
};


class Organizm{
    static int idCounter;
    int id;
    int wiek;
    int sila;
    int inicjatywa;
    int paraKolorow;
    char ikona;
    Swiat* swiat;
    Coords2d pozycja;
    Coords2d poprzedniaPozycja;
protected:
    Organizm(char ikona,int id,int wiek,int sila,int inicjatywa,int paraKolorow,Swiat* swiat,Coords2d pos);
    virtual int randMove();
    virtual void createChild(const Coords2d pos) = 0;
    bool inWorldBounds(const Coords2d pos);
    
public:
    void rysuj(Window * worldWin);
    virtual void akcja() = 0;
    virtual void kolizja(Organizm* other) = 0;
    Organizm* findCollsion();
    Organizm* findCollsion(Coords2d pos);
    std::vector <Coords2d> getFreeSquares();

    //Getters
    int getId() const;
    int getWiek() const;
    int getSila() const;
    int getInicjatywa() const;
    char getIkona() const;
    Swiat* getSwiat() const;
    Coords2d getPozycja() const;
    Coords2d getPoprzedniaPozycja() const;

    //Setters
    void setPozycja(const Coords2d pozycja);
    void setPorzedniaPozycja(const Coords2d pozycja);
    void setWiek(const int wiek);
    void setSila(const int sila);

    virtual ~Organizm();
};