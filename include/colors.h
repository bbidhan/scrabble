#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include "windows.h"
#include "position.h"
#include "board.h"
using namespace std;
void gotoxy(int x,int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void gotobxy(int x,int y){
    gotoxy(x*2+21,y+5);
}
void setColor(int prop){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),prop);
}
void printChar(int x, int y, string c){
    gotobxy(x,y);cout<<c;setColor(15);
}
void printDouble(int x, int y){
    setColor(80);
    printChar(x,y,"*");
}
void printTriple(int x, int y){
    setColor(64);
    printChar(x,y,"*");
}
void printTwos(int x, int y){
    setColor(48);
    printChar(x,y,"+");
}
void printThrees(int x, int y){
    setColor(16);
    printChar(x,y,"+");
}

struct byX{
    bool operator()(position const & a, position const & b) const{
        return a.x < b.x;
    }
};
struct byY{
    bool operator()(position const & a, position const & b) const{
        return a.y < b.y;
    }
};
void prepBoard(board& myBoard){
    setColor(15);
    gotoxy(21,4);
    for(int i = 1;i<=15;i++){
        cout<<". ";
    }
    for(int i = 1;i<=15;i++){
        gotoxy(20,4+i);
        cout<<".";
    }
    for(int i = 1;i<=15;i++){
        gotoxy(20+15*2,4+i);
        cout<<".";
    }
    gotoxy(21,4+16);
    for(int i = 1;i<=15;i++){
        cout<<". ";
    }
    for(int i =0;i<15;i++){
        for(int j =0;j<15;j++){
        if(!myBoard.getPosition(i,j).getLetter().exists()){
            if(myBoard.getPosition(i,j).getMultiplier()==3){printTriple(i,j);}
            if(myBoard.getPosition(i,j).getMultiplier()==2){printDouble(i,j);}
            if(myBoard.getPosition(i,j).getAdder()==3){printThrees(i,j);}
            if(myBoard.getPosition(i,j).getAdder()==2){printTwos(i,j);}
        }
        }
    }
    setColor(15);
}

#endif
