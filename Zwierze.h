#include "Organizm.h"
#include "Swiat.h"
#pragma once
class Zwierze : public Organizm{
    int xMove;
    int yMove;
    
protected:
    Zwierze(char ikona,int id,int wiek,int sila,int inicjatywa,int paraKolorow,Swiat* swiat,Coords2d pos);
    virtual Organizm * getChild(Coords2d pos) = 0;
    void createChild(const Coords2d pos);
    void setXMove(int move);
    void setYMove(int move);
    int getXMove();
    int getYMove();
    
    
public:
    void akcja() override;
    void kolizja(Organizm *other) override;
};