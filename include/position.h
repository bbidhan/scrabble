#ifndef POSITION_H
#define POSITION_H

#include "letter.h"

class position
{
    public:
        int x,y;
        position();
        position(int X, int Y,int mult,int add);

        letter& getLetter();
        char getLowerLetter();
        void setLetter(letter l);
        int getMultiplier();
        void setMultiplier(int a);
        int getAdder();
        void setAdder(int a);
        int getX();
        void setX(int a);
        int getY();
        void setY(int a);
        virtual ~position();
    protected:
    private:
        letter myLetter;
        int multiplier;
        int adder;
};

#endif // POSITION_H
