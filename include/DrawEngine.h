#ifndef DRAWENGINE_H
#define DRAWENGINE_H

#include<windows.h>
#include "board.h"


using namespace std;
class DrawEngine{
public:
    DrawEngine();
    void gotoxy(int x,int y);
    void gotobxy(int x,int y);
    void setColor(int prop);
    void printChar(int x, int y, string c);
    void printDouble(int x, int y);
    void printTriple(int x, int y);
    void printTwos(int x, int y);
    void printThrees(int x, int y);
    void prepBoard(board& myBoard);
    virtual ~DrawEngine();
protected:
private:
};

#endif // DRAWENGINE_H
