#ifndef BUFFERPOSITION_H
#define BUFFERPOSITION_H

#include<vector>
#include "position.h"
using namespace std;
class bufferPosition
{
    public:
        bufferPosition();
        vector<position> buffer;
        void addPosition(position pos);
        virtual ~bufferPosition();
    protected:
    private:

};

#endif // BUFFERPOSITION_H
