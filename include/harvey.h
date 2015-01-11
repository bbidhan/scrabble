#ifndef HARVEY_H
#define HARVEY_H

#include <fstream>
#include "player.h"
#include "board.h"
#include "node.h"
#include "drawEngine.h"

#include "conio.h"
class lastPatt{
public:
    lastPatt(string a,int b,int c){
    lastPattern=a;
    totlastScorePatt=b;
    totlastRep=c;
    }
    string lastPattern;
    int totlastScorePatt;
    int totlastRep;
};
class bufferd_score{
public:
    bufferd_score(int scr,vector<position> buff_):score(scr),buff(buff_){};
    int score;
    vector<position> buff;
};
class harvey : public player{
private:

public:
    node* head;
    vector<node*> finals;
    //vector<node*> finals_parents;
    harvey();
    harvey(string nam,bool human=true);
    int aiProcess(board &myBoard, bag &myBag,bool,int);
    int minimaxBoardProcess(board tempBoard, bag tempBag,vector< bufferd_score >& buff_scores);
    int evaluateRack(int);
    void playAnchored(board &myBoard, bag &myBag,int i_,int j_,vector<position>& bestBuffer,int& bestScore,bool error,bool,int& totMoves,vector< bufferd_score >& buff_scores);
    void addBufferToList(vector< bufferd_score >& buff_scores,int& myScoreCF,vector<position>& buffer);
    bool identicalNodes(node*,node*);
    bool processDuplicateNode(node* delNode,node* pointParentToNode);

    vector<lastPatt> patts;

    virtual ~harvey();
    protected:
    private:
};

#endif // HARVEY_H
