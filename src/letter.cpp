#include "letter.h"

letter::letter(){number=0;}
letter::letter(char nam, int num, int scr){number =num;name =nam;score =scr;ascii = nam;}
void letter::setVal(char nam, int num, int scr){number =num;name =nam;score =scr;ascii = nam;}
int letter::getASCII(){return ascii;}
void letter::convertBlankTo(char ch){name=ch;ascii=name;}
int letter::getNum(){return number;}
int letter::getScore(){return score;}
char letter::getName(){return name;}
bool letter::exists(){return number;}
void letter::kill(){number=0;}

letter::~letter(){
    //dtor
}
