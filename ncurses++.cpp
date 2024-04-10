#include "ncurses++.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

#define ARROW_UP 65
#define ARROW_DOWN 66
#define ENTER 13

Window::Window(const int x,const int y){
    this->x = x;
    this->y = y;
    this->window = newwin(y,x,0,0);
}

Window::Window(const int x,const int y,const int offsetx,const int offsety){
    this->x = x;
    this->y = y;
    this->window = newwin(y,x,offsety,offsetx);
}

void Window::refresh(){
    wrefresh(window);
}

void Window::clear(){
    wclear(window);
}

void Window::createBorder(){
    box(window,0,0);
}

void Window::oattron(const int atrribiute){
    wattron(window,atrribiute);
}

void Window::oattroff(const int atrribiute){
    wattroff(window,atrribiute);
}

void Window::omove(const int x,const int y){
    wmove(window,y,x);
}

void Window::omvprint(const int x,const int y,const string &str){
    mvwprintw(window,y,x,"%s",str.c_str());
}


void Window::omvprint(const int x,const int y,const char * str){
    mvwprintw(window,y,x,"%s",str);
}

void Window::omvprint(const int x,const int y,const char c){
    mvwprintw(window,y,x,"%c",c);
}

void Window::omvscanw(const int x,const int y,string &str){
    char buffer[200];
    mvwscanw(window,y,x,"%s",buffer);
    str = buffer;
}

void Window::omvscanw(const int x,const int y,char *&str){
    char buffer[200];
    mvwscanw(window,y,x,"%s",buffer);
    strcpy(str,buffer);
}

void Window::omvscanw(const int x,const int y,int &integer){
    mvwscanw(window,y,x,"%d",&integer);
}

Window::~Window(){
    delwin(window);
}

Menu::Menu(const char * title,const int menuSize,const string options[],const int x,const int y){
    this->title = title;
    this->menuSize = menuSize;
    this->option = 0;
    this->options = new string[menuSize];
    for(int i = 0;i<menuSize;i++){
        this->options[i] = options[i];
    }
    this->window = new Window(x,y);
}

Menu::Menu(const char * title,initializer_list <string> options,const int x,const int y){
    this->title = title;
    this->menuSize = options.size();
    this->option = 0;
    this->options = new string[menuSize];
    int i = 0;
    for(string option : options){
        this->options[i] = option;
        i++;
    }
    this->window = new Window(x,y);
}



#define MARGIN_X 2
#define MARGIN_Y 2
void Menu::drawMenu(){
    window->createBorder();
    window->omvprint(MARGIN_X,0,title);
    window->omvprint(MARGIN_X,menuSize+4,"press ENTER to select option");
    for(int i = 0;i<menuSize;i++){
        if(i==option) window->oattron(A_REVERSE);
        window->omvprint(MARGIN_X,MARGIN_Y+i,options[i]);
        window->omove(MARGIN_X,MARGIN_Y+option);
        window->oattroff(A_REVERSE);
    }
    
    window->refresh();
}

int Menu::getKey(){
    int key = getchar();

    if(key == ARROW_UP){
        if(option>0)option--;
    }
    else if(key == ARROW_DOWN){
        if(option<menuSize-1)option++;
    }

    return key;
}

int Menu::runMenu(){
    do{
        drawMenu();
    }while(getKey() != ENTER);

    window->clear();
    window->refresh();
    return option;
}

Menu::~Menu(){
    window->clear();
    window->refresh();
    delete window;
    delete[] options;

}

InfoPrompt::InfoPrompt(const char* title,const int linesAmount, const string lines[],const int x,const int y,const int offsetx,const int offsety){
    this->title = title;
    this->linesAmount = linesAmount;
    this->lines = new string[linesAmount];
    for(int i = 0;i<linesAmount;i++){
        this->lines[i] = lines[i];
    }
    this->window = new Window(x,y,offsetx,offsety);
}

InfoPrompt::InfoPrompt(const char* title,initializer_list <string> lines,const int x,const int y,const int offsetx,const int offsety){
    this->title = title;
    this->linesAmount = lines.size();
    this->lines = new string[linesAmount];
    int i = 0;
    for(string line : lines){
        this->lines[i] = line;
        i++;
    }
    this->window = new Window(x,y,offsetx,offsety);
}

InfoPrompt::InfoPrompt(const char* title,vector <string> lines,const int x,const int y,const int offsetx,const int offsety){
    this->title = title;
    this->linesAmount = lines.size();
    this->lines = new string[linesAmount];
    int i = 0;
    for(string line : lines){
        this->lines[i] = line;
        i++;
    }
    this->window = new Window(x,y,offsetx,offsety);
}

void InfoPrompt::showPrompt(){
    window->createBorder();
    window->omvprint(2,0,title);
    for(int i = 0;i<linesAmount;i++){
        window->omvprint(2,2+i,lines[i]);
    }
    window->refresh();
}

InfoPrompt::~InfoPrompt(){
    window->clear();
    window->refresh();
    delete window;
    delete[] lines;
}

string stringInput(string title,int x,int y){
    string ret;
    Window inputWin(x,y);
    inputWin.createBorder();
    inputWin.omvprint(MARGIN_X,0,"Input");
    inputWin.omvprint(MARGIN_X,MARGIN_Y,title + ": ");
    inputWin.refresh();

    echo();
    inputWin.omvscanw(title.length()+MARGIN_X+2,MARGIN_Y,ret);
    noecho();

    inputWin.clear();
    inputWin.refresh();
    return ret;
}

int intInput(string title,int x,int y){
    int ret;
    Window inputWin(x,y);
    inputWin.createBorder();
    inputWin.omvprint(MARGIN_X,0,"Input");
    inputWin.omvprint(MARGIN_X,MARGIN_Y,title + ": ");
    inputWin.refresh();

    echo();
    inputWin.omvscanw(title.length()+MARGIN_X+2,MARGIN_Y,ret);
    noecho();

    inputWin.clear();
    inputWin.refresh();
    return ret;
}