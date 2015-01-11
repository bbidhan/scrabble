#include "DrawEngine.h"

void DrawEngine::gotoxy(int x,int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void DrawEngine::gotobxy(int x,int y){
    gotoxy(x*2+21,y+5);
}
void DrawEngine::setColor(int prop){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),prop);
}
void DrawEngine::printChar(int x, int y, string c){
    gotobxy(x,y);cout<<c;setColor(15);
}
void DrawEngine::printDouble(int x, int y){
    setColor(80);
    printChar(x,y,"*");
}
void DrawEngine::printTriple(int x, int y){
    setColor(64);
    printChar(x,y,"*");
}
void DrawEngine::printTwos(int x, int y){
    setColor(48);
    printChar(x,y,"+");
}
void DrawEngine::printThrees(int x, int y){
    setColor(16);
    printChar(x,y,"+");
}
void DrawEngine::prepBoard(board& myBoard){
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
DrawEngine::DrawEngine()
{
    //ctor
}

DrawEngine::~DrawEngine()
{
    //dtor
}
