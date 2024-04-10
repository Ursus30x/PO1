//This is just a ncurses wrapper made for OOP

#include <ncurses.h>
#include <string>
#include <initializer_list>
#include <vector>

#pragma once

using namespace std;

class Window{
    WINDOW * window;
    int x;
    int y;
public:
    Window(const int x,const int y);
    Window(const int x,const int y,const int offsetx,const int offsety);
    void refresh();
    void clear();
    void createBorder();
    void oattron(const int atrribiute);
    void oattroff(const int atrribiute);
    void omove(const int x,const int y);
    void omvprint(const int x,const int y,const string &str);
    void omvprint(const int x,const int y,const char * str);
    void omvprint(const int x,const int y,const char c);

    //kinda crude but thats the best i can do to convert this from c to c++
    //i wanted to do this with stdarg.h but it would be an overkill for this project
    //so i will make it by with diffrent methods for diffrent data types
    void omvscanw(const int x,const int y,string &str);
    void omvscanw(const int x,const int y,char *&str);
    void omvscanw(const int x,const int y,int &integer);
    ~Window();

};

class Menu{
    string title;
    int option;
    int menuSize;
    string* options;
    Window * window;

private:
    void drawMenu();
    void moveHighlight();
    int getKey();

public:
    Menu(const char * title, const int menuSize, const string options[],const int x,const int y);
    Menu(const char * title, initializer_list <string> options,const int x,const int y);
    int runMenu();
    ~Menu();
    
};

class InfoPrompt{
    string title;
    int linesAmount;
    string *lines;
    Window * window;
    
public:
    InfoPrompt(const char* title,const int linesAmount,const string lines[],const int x,const int y,const int offsetx,const int offsety);
    InfoPrompt(const char* title,initializer_list <string> lines,const int x,const int y,const int offsetx,const int offsety);
    InfoPrompt(const char* title,vector <string> lines,const int x,const int y,const int offsetx,const int offsety);

    void changeLine(string newLine,int index);
    void changeLines(string newLines[]);
    void changeLines(initializer_list <string> newLines);
    void showPrompt();
    ~InfoPrompt();

};

string stringInput(string title,int x,int y);
int intInput(string title,int x,int y);
