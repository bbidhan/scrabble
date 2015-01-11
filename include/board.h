#ifndef BOARD_H
#define BOARD_H

#include "player.h"

class board{
public:
    board();
    void setMult(int x, int y, int mult);
    void setAdd(int x, int y, int add);
    position& getPosition(position &pos);
    position& getPosition(int i, int j);
    position& getCurrentPos();
    int getCurrentMultiplier();
    int getMultiplier(position &pos);
    int getMultiplier(int x, int y);
    int getCurrentAdder();
    int getAdder(position &pos);
    int getAdder(int x, int y);
    int getCurrentX();
    int getCurrentY();
    void setCurrentPos(position& pos);
    void setCurrentX(int a);
    void setCurrentY(int a);
    void setCurrentLetter(letter let);
    letter getCurrentLetter();
    bool isSet(int i, int j);
    bool isSet(position &pos);
    bool isCurrentSet();
    bool isCurrentPermanentlySet();
    void clearLastRun();
    void updateBoard(vector<position> &buffer,vector<position> &wordBuffer);
    void processBufferRowwiseX(vector<position> &buffer,vector<position> &wordBuffer);
    void processBufferRowwiseY(vector<position> &buffer,vector<position> &wordBuffer);
    bool isValidBuffer(vector<position> &buffer);
    void processBufferAndCalculateScore(vector<position> &wordBuffer);
    bool checkBufferByX(vector<position> &wordBuffer);
    bool checkBufferByY(vector<position> &wordBuffer);
    int totalLastWords();
    string getLastWord(int i);
    string getLastWordLower(int i);
    void addWord(string word);
    vector<string>& getWords();
    int getLastScore();
    void setLastScore(int scr);
    void incPlaycount();
    int getPlayCount();
    void reset();
    virtual ~board();
    bool rowwise;
    bool colwise;
    int calcc;
    protected:
private:
    int lastScore;
    vector<string> lastWords;
    position currentPos;
    position allPositions[15][15];
    int playcount;
};

#endif // BOARD_H
