#include <iostream>
#include <cstdio>
#include <fstream>
#include <time.h>
#include "ncurses++.h"
#include "Swiat.h"

using namespace std;

enum MenuOpts{
    newGame,
    loadGame,
    testGame,
    exitGame
};

#define MAIN_MENU_SIZE 3
#define MAIN_MENU_OPTIONS {"1.New simulation","2.Load simulation","3.Test simulation","4.Exit"}
#define MENU_X 40
#define MENU_Y 20

void gameInit(){
    Menu mainMenu("Main Menu",MAIN_MENU_OPTIONS,MENU_X,MENU_Y);
    Swiat *world;
    switch (mainMenu.runMenu())
    {
    case newGame:{
        string worldName = stringInput("World Name",MENU_X,MENU_Y);
        int sizeX = intInput("World X Size",MENU_X,MENU_Y);
        int sizeY = intInput("World Y Size",MENU_X,MENU_Y);

        world = new Swiat(worldName,sizeX,sizeY);
        world->dodajOrganizmy();
        break;
    }
    case loadGame:{
        string saveName = stringInput("Save Name",30,30);
        ifstream save("saves/" + saveName + ".sav");
        if(save.good()){
            world = new Swiat(save);
        }else{
            endwin();
            exit(1);
        }
        save.close();
        break;
    } 
    case testGame:{
        //string worldName = "testWorld";
        world = new Swiat("testWorld",20,20);
        world->testWorld();
        break;
    }
    case exitGame:
        return;
    default:
        break;
    }

    world->symuluj();
}

int main(){
    srand(time(NULL));
    initscr();
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,COLOR_GREEN);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    init_pair(4,COLOR_WHITE,COLOR_RED);
    init_pair(5,COLOR_RED,COLOR_YELLOW);
    init_pair(6,COLOR_BLUE,COLOR_RED);
    init_pair(7,COLOR_BLACK,COLOR_YELLOW);
    cbreak();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    noecho();

    //I need to do it in such a way so ncurses++ decstructors will 
    //call properly and wont make desctructors calls after endwin() function
    //since it breaks terminal i/o
    gameInit();

    endwin();
    return 0;
}