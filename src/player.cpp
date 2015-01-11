#include "player.h"

    player::player(){lastScore=0;totalScore=0;lastWords.reserve(0);words.reserve(0);letters.reserve(7);isAI=false;turns=0;}
    player::player(string nam){isAI=false;lastScore=0;totalScore=0;lastWords.reserve(0);words.reserve(0);letters.reserve(7);name=nam;}
    int player::getAvgScore(){return getTotalScore()/turns;}
    int player::getLastScore(){return lastScore;}
    int player::getTotalScore(){return totalScore;}
    void player::setLastScore(int scr){lastScore=scr;}
    void player::setTotalScore(){totalScore+=lastScore;}
    vector<letter> player::getLetters(){return letters;}
    int player::totalLetters(){return letters.size();}
    letter& player::getLetters(int i){return letters[i];}
    int player::totalLastWords(){return lastWords.size();}
    string player::getWordifiedRack(){
        string data="";
        for(int i =0; i<letters.size();i++){
            if(getLetters(i).getASCII()==95){
                 getLetters(i).convertBlankTo('S');
            }
            data.push_back(letters[i].getName());
        }
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        sort( data.begin(), data.end() );
        return data;
    }
    string player::getWord(int i){return words[i];}
    string player::getLastWord(int i){return lastWords[i];}
    string player::getLastWordLower(int i){
        string data = lastWords[i];
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        return data;
    }
    int player::totalWords(){return words.size();}
    void player::pullLetterFromBag(bag &mybag){letters.push_back(mybag.pullRandomLetter());}
    void player::addWord(string word){lastWords.push_back(word);}
    void player::finalizeWords(){copy(lastWords.begin(),lastWords.end(),back_inserter(words));turns++;}
    void player::clearLastRun(){lastWords.clear();lastScore=0;}
    void player::eraseLetter(int i){letters.erase(letters.begin()+i);}
    void player::drawLetterFromBuffer(vector<position> &buffer){letters.push_back(buffer[buffer.size()-1].getLetter());buffer.pop_back();}
    void player::drawAllLettersFromBuffer(vector<position> &buffer){
        int i = buffer.size()-1;
        for(;i>=0;i--){
            letters.push_back(buffer[i].getLetter());
            buffer.pop_back();
        }
    }
    void player::setName(string nam){name=nam;}
    void player::refresh(){lastScore=0;lastWords.clear();}
    int player::endGame(){
        int temp=0;
        for(int i =0; i<letters.size();i++){
            temp += getLetters(i).getScore();
        }
        totalScore-=temp;
        return temp;
    }
    string player::getName(){return name;}

player::~player()
{
    //dtor
}
