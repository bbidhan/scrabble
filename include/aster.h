#ifndef ASTER_H
#define ASTER_H

#include <fstream>
#include "player.h"
#include "harvey.h"
#include "board.h"
#include "node.h"
#include "drawEngine.h"

class aster : public harvey
{
    public:
        aster();
        aster(string nam,bool human=true);
        int aiProcessR(board &myBoard, bag &myBag);
        virtual ~aster();
    protected:
    private:
};

#endif // ASTER_H
