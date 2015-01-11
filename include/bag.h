#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include "letter.h"

using namespace std;
class bag
{
    public:
        virtual ~bag();
        bag();
        letter pullRandomLetter();
        void reset();
        int lettersLeft();

    protected:
    private:
        vector<letter> allLetters;
};

#endif // BAG_H
