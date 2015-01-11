#include "position.h"

        position::position(){multiplier=1;adder=1;}
        position::position(int X, int Y,int mult=1,int add=1){x=X;y=Y;multiplier=mult;adder=add;}

        letter& position::getLetter(){return myLetter;}
        char position::getLowerLetter(){return (int)myLetter.getASCII() + 32;}
        void position::setLetter(letter l){myLetter=l;}
        int position::getMultiplier(){return multiplier;}
        void position::setMultiplier(int a){multiplier=a;}
        int position::getAdder(){return adder;}
        void position::setAdder(int a){adder=a;}
        int position::getX(){return x;}
        void position::setX(int a){x=a;}
        int position::getY(){return y;}
        void position::setY(int a){y=a;}

position::~position()
{
    //dtor
}
