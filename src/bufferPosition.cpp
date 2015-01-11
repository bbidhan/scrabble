#include "bufferPosition.h"

bufferPosition::bufferPosition()
{
    //ctor
}
void bufferPosition::addPosition(position pos){
    buffer.push_back(pos);
}

bufferPosition::~bufferPosition()
{
    //dtor
}
