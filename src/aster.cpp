#include "aster.h"

aster::aster():harvey(){}
aster::aster(string nam,bool human):harvey(nam){
    if(!human){
    isAI=true;
    head = new node();
    ifstream myfile("sowpods.txt");
    string line="";
    int i =0;
    while (getline(myfile,line)){head->insert_word(line);i++;}
    myfile.close();
    cout<<i<<" words!"<<endl;
    //cout<<nodes<<" nodes"<<endl;
    }
}
int aster::aiProcessR(board &myBoard, bag &myBag){
    DrawEngine graphics;
    vector<position> bestBuffer;
    int bestScore = 0;
    vector<position> bestWordBuffer;
    bool error = true;
if(myBoard.getPlayCount()== 0){
        for(int t = 0;t<letters.size();t++){
                for(int v =0; v<8;v++){
                    vector<position> buffer;
                    vector<position> wordBuffer;
                        myBoard.setCurrentX(7);
                        myBoard.setCurrentY(7);
                        myBoard.setCurrentLetter(this->getLetters(t));
                        graphics.gotobxy(7,7);
                        //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
                        int jpt =this->getLetters(t).getASCII()+32;

                        //this->eraseLetter(t);
                        position tempPos = myBoard.getCurrentPos();
                        //buffer.push_back(tempPos);
                        string letters__ = getWordifiedRack();
                        letters__.erase(letters__.begin()+t);
                    vector<string> hookedWords = head->aiProcess(letters__,(char)((int)jpt),v);

                    //string word = hookedWords[0];

                    for(int y = 0;y<hookedWords.size();y++){
                        buffer.push_back(tempPos);
                         for(int r = 0;r<letters.size();r++){
                            if((letters[r].getASCII() + 32) == jpt){
                                this->eraseLetter(r);
                                break;
                            }
                         }
                        //cout<<hookedWords[y]<<endl;
                        string word = hookedWords[y];
                        //graphics.gotoxy(0,40);
                        //cout<<"                 "<<endl;
                        //cout<<"                 "<<endl;
                        //cout<<"                 "<<endl;
                        //graphics.gotoxy(0,40);
                        //cout<<word<<endl;
                        //cout<<getWordifiedRack()<<endl;

                        for(int q = 0;q<word.size();q++){
                            for(int r = 0;r<letters.size();r++){
                                if((char)(letters[r].getASCII() + 32) == word[q]
                                   && q !=v
                                   ){
                                    myBoard.setCurrentX(7-v+q);
                                    myBoard.setCurrentY(7);
                                    myBoard.setCurrentLetter(this->getLetters(r));
                                    graphics.gotobxy(7-v+q,7);
                                    //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
                                    //cout<<letters[r].getName();
                                    this->eraseLetter(r);
                                    buffer.push_back(myBoard.getCurrentPos());
                                    break;
                                }
                            }
                        }
                        //cout<<getWordifiedRack();
                        //cout<<endl;

                    if(buffer.size()>1){
                        error = myBoard.isValidBuffer(buffer);
                        if(!error)myBoard.updateBoard(buffer,wordBuffer);
                        this->clearLastRun();
                        if(myBoard.totalLastWords()>0 && !error){
                            //DICTIONARY CHECK HERE
                            for(int x = 0;x<myBoard.totalLastWords();x++){
                                if(this->head->search_word(myBoard.getLastWordLower(x))==0){
                                    error = true;
                                    break;
                                }
                                //this->addWord(myBoard.getLastWord(x));
                            }
                            if(!error){
                                //cout<<error;
                                if(myBoard.getLastScore()>bestScore){
                                    bestBuffer.clear();
                                    copy(buffer.begin(),buffer.end(),back_inserter(bestBuffer));
                                    bestScore = myBoard.getLastScore();
                                    //cout<<bestScore;
                                }

                            }

                        }
                    }
                    drawAllLettersFromBuffer(buffer);
                    buffer.clear();
                    wordBuffer.clear();
                }
                hookedWords.clear();
                }
                }


}else{
    for(int i =0; i<15;i++){
        for(int j =0; j<15;j++){
            if(myBoard.isSet(i,j)){
                for(int v =0; v<8;v++){
                if(!myBoard.isSet(i,j-1)){
                    vector<string> hookedWords = head->aiProcess(getWordifiedRack(),(char)((int)myBoard.getPosition(i,j).getLetter().getASCII()+32),v);
                    vector<position> buffer;
                    vector<position> wordBuffer;
                    //string word = hookedWords[0];

                    for(int y = 0;y<hookedWords.size();y++){
                        //cout<<hookedWords[y]<<endl;
                        string word = hookedWords[y];
                        for(int q = 0;q<word.size();q++){
                            for(int r = 0;r<letters.size();r++){
                                if((char)(letters[r].getASCII() + 32) == word[q]
                                   && q !=v
                                   && !myBoard.isSet(i,j-v+q)
                                   && j-v+q >=0
                                   && j-v+q <15
                                   ){
                                    myBoard.setCurrentX(i);
                                    myBoard.setCurrentY(j-v+q);
                                    myBoard.setCurrentLetter(this->getLetters(r));
                                    graphics.gotobxy(i,j-v+q);
                                    //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
                                    this->eraseLetter(r);
                                    buffer.push_back(myBoard.getCurrentPos());
                                    break;
                                }
                            }
                        }

                    if(buffer.size()>1){
                        error = myBoard.isValidBuffer(buffer);
                        if(!error)myBoard.updateBoard(buffer,wordBuffer);
                        this->clearLastRun();
                        if(myBoard.totalLastWords()>0 && !error){
                            //DICTIONARY CHECK HERE
                            for(int x = 0;x<myBoard.totalLastWords();x++){
                                if(this->head->search_word(myBoard.getLastWordLower(x))==0){
                                    error = true;
                                    break;
                                }
                                //this->addWord(myBoard.getLastWord(x));
                            }
                            if(!error){
                                if(myBoard.getLastScore()>bestScore){
                                    bestBuffer.clear();
                                    copy(buffer.begin(),buffer.end(),back_inserter(bestBuffer));
                                    bestScore = myBoard.getLastScore();
                                    //cout<<bestScore;
                                }

                            }

                        }
                    }
                    drawAllLettersFromBuffer(buffer);
                    buffer.clear();
                    wordBuffer.clear();
                }
                hookedWords.clear();
                }

            }
            }
        }
    }
    for(int i =0; i<15;i++){
        for(int j =0; j<15;j++){
            if(myBoard.isSet(i,j)){
                for(int v =0; v<8;v++){
                if(!myBoard.isSet(i-1,j)){
                    vector<string> hookedWords = head->aiProcess(getWordifiedRack(),(char)((int)myBoard.getPosition(i,j).getLetter().getASCII()+32),v);
                    vector<position> buffer;
                    vector<position> wordBuffer;
                    //string word = hookedWords[0];

                    for(int y = 0;y<hookedWords.size();y++){
                        //cout<<hookedWords[y]<<endl;
                        string word = hookedWords[y];
                        for(int q = 0;q<word.size();q++){
                            for(int r = 0;r<letters.size();r++){
                                if((char)(letters[r].getASCII() + 32) == word[q]
                                   && q !=v
                                   && !myBoard.isSet(i-v+q,j)
                                   && i-v+q >=0
                                   && i-v+q<15
                                   ){
                                    myBoard.setCurrentX(i-v+q);
                                    myBoard.setCurrentY(j);
                                    myBoard.setCurrentLetter(this->getLetters(r));
                                    graphics.gotobxy(i-v+q,j);
                                    //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
                                    this->eraseLetter(r);
                                    buffer.push_back(myBoard.getCurrentPos());
                                    break;
                                }
                            }
                        }

                    if(buffer.size()>1){
                        error = myBoard.isValidBuffer(buffer);
                        if(!error)myBoard.updateBoard(buffer,wordBuffer);
                        this->clearLastRun();
                        if(myBoard.totalLastWords()>0 && !error){
                            //DICTIONARY CHECK HERE
                            for(int x = 0;x<myBoard.totalLastWords();x++){
                                if(this->head->search_word(myBoard.getLastWordLower(x))==0){
                                    error = true;
                                    break;
                                }
                                //this->addWord(myBoard.getLastWord(x));
                            }
                            if(!error){
                                if(myBoard.getLastScore()>bestScore){
                                    bestBuffer.clear();
                                    copy(buffer.begin(),buffer.end(),back_inserter(bestBuffer));
                                    bestScore = myBoard.getLastScore();
                                }

                            }

                        }
                    }
                    drawAllLettersFromBuffer(buffer);
                    buffer.clear();
                    wordBuffer.clear();
                }
                hookedWords.clear();
                }

            }
            }
        }
    }

}

if(bestScore>0){
    this->clearLastRun();
    error = myBoard.isValidBuffer(bestBuffer);
    if(!error)myBoard.updateBoard(bestBuffer,bestWordBuffer);
    //cout<<bestScore;
    this->setLastScore(bestScore);
    for(int x = 0;x<myBoard.totalLastWords();x++){
        this->addWord(myBoard.getLastWord(x));
    }
    this->finalizeWords();
    for(int i = 0;i<bestBuffer.size();i++){
        myBoard.getPosition(bestBuffer[i]).setLetter(bestBuffer[i].getLetter());
        myBoard.getPosition(bestBuffer[i]).setAdder(1);
        myBoard.getPosition(bestBuffer[i]).setMultiplier(1);
        graphics.gotobxy(bestBuffer[i].getX(),bestBuffer[i].getY());
        cout<<bestBuffer[i].getLetter().getName();
        for(int q = 0;q<letters.size();q++){
                if(letters[q].getASCII() == bestBuffer[i].getLetter().getASCII()){
                    this->eraseLetter(q);
                    break;
                }
        }
         if(myBag.lettersLeft()>0){this->pullLetterFromBag(myBag);}
    }
    this->setTotalScore();
}

return bestScore;
}

aster::~aster()
{
    //dtor
}
