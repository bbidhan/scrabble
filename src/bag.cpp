#include "bag.h"

int random (int low, int high) {
    if (low > high) return high;
    return low + (rand() % (high - low + 1));
}
void bag::reset(){
 allLetters.clear();
 letter A('A',9,1);allLetters.push_back(A);
 letter B('B',2,3);allLetters.push_back(B);
 letter C('C',2,3);allLetters.push_back(C);
 letter D('D',4,2);allLetters.push_back(D);
 letter E('E',12,1);allLetters.push_back(E);
 letter F('F',2,4);allLetters.push_back(F);
 letter G('G',3,2);allLetters.push_back(G);
 letter H('H',2,4);allLetters.push_back(H);
 letter I('I',9,1);allLetters.push_back(I);
 letter J('J',1,8);allLetters.push_back(J);
 letter K('K',1,5);allLetters.push_back(K);
 letter L('L',4,1);allLetters.push_back(L);
 letter M('M',2,3);allLetters.push_back(M);
 letter N('N',6,1);allLetters.push_back(N);
 letter O('O',8,1);allLetters.push_back(O);
 letter P('P',2,3);allLetters.push_back(P);
 letter Q('Q',1,10);allLetters.push_back(Q);
 letter R('R',6,1);allLetters.push_back(R);
 letter S('S',4,1);allLetters.push_back(S);
 letter T('T',6,1);allLetters.push_back(T);
 letter U('U',4,1);allLetters.push_back(U);
 letter V('V',2,4);allLetters.push_back(V);
 letter W('W',2,4);allLetters.push_back(W);
 letter X('X',1,8);allLetters.push_back(X);
 letter Y('Y',2,4);allLetters.push_back(Y);
 letter Z('Z',1,10);allLetters.push_back(Z);
letter _('_',2,0);allLetters.push_back(_);
 int x = allLetters.size();
 for(int i =0;i<x;i++){
   for(int j =0;j<allLetters[i].getNum()-1;j++){
       allLetters.push_back(allLetters[i]);
   }
 }
}
bag::bag(){
 letter A('A',9,1);allLetters.push_back(A);
 letter B('B',2,3);allLetters.push_back(B);
 letter C('C',2,3);allLetters.push_back(C);
 letter D('D',4,2);allLetters.push_back(D);
 letter E('E',12,1);allLetters.push_back(E);
 letter F('F',2,4);allLetters.push_back(F);
 letter G('G',3,2);allLetters.push_back(G);
 letter H('H',2,4);allLetters.push_back(H);
 letter I('I',9,1);allLetters.push_back(I);
 letter J('J',1,8);allLetters.push_back(J);
 letter K('K',1,5);allLetters.push_back(K);
 letter L('L',4,1);allLetters.push_back(L);
 letter M('M',2,3);allLetters.push_back(M);
 letter N('N',6,1);allLetters.push_back(N);
 letter O('O',8,1);allLetters.push_back(O);
 letter P('P',2,3);allLetters.push_back(P);
 letter Q('Q',1,10);allLetters.push_back(Q);
 letter R('R',6,1);allLetters.push_back(R);
 letter S('S',4,1);allLetters.push_back(S);
 letter T('T',6,1);allLetters.push_back(T);
 letter U('U',4,1);allLetters.push_back(U);
 letter V('V',2,4);allLetters.push_back(V);
 letter W('W',2,4);allLetters.push_back(W);
 letter X('X',1,8);allLetters.push_back(X);
 letter Y('Y',2,4);allLetters.push_back(Y);
 letter Z('Z',1,10);allLetters.push_back(Z);
 //letter _('_',2,0);allLetters.push_back(_);
 int x = allLetters.size();
 for(int i =0;i<x;i++){
   for(int j =0;j<allLetters[i].getNum()-1;j++){
       allLetters.push_back(allLetters[i]);
   }
 }
 }
 letter bag::pullRandomLetter(){
   unsigned int time_ui = ( time(NULL) );
   srand( time_ui );
   int rand = random(0,allLetters.size()-1);
   letter x = allLetters[rand];
   allLetters.erase(allLetters.begin()+rand);
   return x;
 }
 int bag::lettersLeft(){
   return allLetters.size();
 }
bag::~bag()
{
    //dtor
}
