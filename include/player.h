#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "bag.h"

class player{
public:
    player();
    player(string nam);
    int getAvgScore();
    int getLastScore();
    int getTotalScore();
    void setLastScore(int scr);
    void setTotalScore();
    vector<letter> getLetters();
    int totalLetters();
    letter& getLetters(int i);
    int totalLastWords();
    string getWord(int i);
    string getLastWord(int i);
    string getLastWordLower(int i);
    int totalWords();
    string getWordifiedRack();
    void pullLetterFromBag(bag &mybag);
    void addWord(string word);
    void finalizeWords();
    void clearLastRun();
    void eraseLetter(int i);
    void drawLetterFromBuffer(vector<position> &buffer);
    void drawAllLettersFromBuffer(vector<position> &buffer);
    void setName(string nam);
    void refresh();
    int endGame();
    string getName();
    virtual ~player();
    bool isAI;
    protected:
    int turns;
    int lastScore;
    int totalScore;
    string name;
    vector<string> lastWords;
    vector<string> words;
    vector<letter> letters;
private:


};

#endif // PLAYER_H
