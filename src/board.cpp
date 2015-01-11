#include "board.h"
struct byX{
    bool operator()(position const & a, position const & b) const{
        return a.x < b.x;
    }
};
struct byY{
    bool operator()(position const & a, position const & b) const{
        return a.y < b.y;
    }
};
board::board(){
    calcc=0;
        playcount=0;
        currentPos.setX(7);
        currentPos.setY(7);
        for(int i = 0;i<15;i++){
            for(int j = 0;j<15;j++){
                allPositions[i][j].setX(i);
                allPositions[i][j].setY(j);
            }
            for(int i=0;i<=2;i++){//*3
                setMult(i*7,0,3);
                setMult(i*7,7,3);
                setMult(i*7,14,3);
            }
            for(int i=1;i<=4;i++){//*2
                setMult(i,i,2);
                setMult(14-i,14-i,2);
                setMult(i,14-i,2);
                setMult(14-i,i,2);
            }
            for(int i=0;i<4;i++){//+2
                setAdd(1+i*4,1,3);
                setAdd(1+i*4,5,3);
                setAdd(1+i*4,9,3);
                setAdd(1+i*4,13,3);
            }
            setMult(7,7,2);
            setAdd(3,0,2);setAdd(11,0,2);setAdd(6,2,2);setAdd(8,2,2);
            setAdd(3,14,2);setAdd(11,14,2);setAdd(6,12,2);setAdd(8,12,2);
            setAdd(2,6,2);setAdd(6,6,2);setAdd(8,6,2);setAdd(12,6,2);
            setAdd(2,8,2);setAdd(6,8,2);setAdd(8,8,2);setAdd(12,8,2);
            setAdd(3,7,2);setAdd(11,7,2);
            setAdd(0,3,2);setAdd(7,3,2);setAdd(14,3,2);
            setAdd(0,11,2);setAdd(7,11,2);setAdd(14,11,2);
        }
    }
    void board::reset(){
        calcc=0;
        playcount=0;
        currentPos.setX(7);
        currentPos.setY(7);
        for(int i = 0;i<15;i++){
            for(int j = 0;j<15;j++){
                allPositions[i][j].setX(i);
                allPositions[i][j].setY(j);
            }
            for(int i=0;i<=2;i++){//*3
                setMult(i*7,0,3);
                setMult(i*7,7,3);
                setMult(i*7,14,3);
            }
            for(int i=1;i<=4;i++){//*2
                setMult(i,i,2);
                setMult(14-i,14-i,2);
                setMult(i,14-i,2);
                setMult(14-i,i,2);
            }
            for(int i=0;i<4;i++){//+2
                setAdd(1+i*4,1,3);
                setAdd(1+i*4,5,3);
                setAdd(1+i*4,9,3);
                setAdd(1+i*4,13,3);
            }
            setMult(7,7,2);
            setAdd(3,0,2);setAdd(11,0,2);setAdd(6,2,2);setAdd(8,2,2);
            setAdd(3,14,2);setAdd(11,14,2);setAdd(6,12,2);setAdd(8,12,2);
            setAdd(2,6,2);setAdd(6,6,2);setAdd(8,6,2);setAdd(12,6,2);
            setAdd(2,8,2);setAdd(6,8,2);setAdd(8,8,2);setAdd(12,8,2);
            setAdd(3,7,2);setAdd(11,7,2);
            setAdd(0,3,2);setAdd(7,3,2);setAdd(14,3,2);
            setAdd(0,11,2);setAdd(7,11,2);setAdd(14,11,2);
        }
    }
    void board::setMult(int x, int y, int mult){allPositions[x][y].setMultiplier(mult);}
    void board::setAdd(int x, int y, int add){
        if(allPositions[x][y].getMultiplier()==1){
         allPositions[x][y].setAdder(add);
        }
    }
    int board::getPlayCount(){return playcount;}
    void board::incPlaycount(){playcount++;}
    position& board::getPosition(position &pos){return allPositions[pos.getX()][pos.getY()];}
    position& board::getPosition(int i, int j){return allPositions[i][j];}
    position& board::getCurrentPos(){return currentPos;}
    int board::getCurrentMultiplier(){return getPosition(currentPos).getMultiplier();}
    int board::getMultiplier(position &pos){return getPosition(pos).getMultiplier();}
    int board::getMultiplier(int x, int y){return getPosition(x,y).getMultiplier();}
    int board::getCurrentAdder(){return getPosition(currentPos).getAdder();}
    int board::getAdder(position &pos){return getPosition(pos).getAdder();}
    int board::getAdder(int x, int y){return getPosition(x,y).getAdder();}
    int board::getCurrentX(){return currentPos.getX();}
    int board::getCurrentY(){return currentPos.getY();}
    void board::setCurrentPos(position& pos){currentPos=pos;}
    void board::setCurrentX(int a){currentPos.setX(a);}
    void board::setCurrentY(int a){currentPos.setY(a);}
    void board::setCurrentLetter(letter let){currentPos.setLetter(let);}
    letter board::getCurrentLetter(){return currentPos.getLetter();}
    bool board::isSet(int i, int j){return allPositions[i][j].getLetter().exists();}
    bool board::isSet(position &pos){return allPositions[pos.getX()][pos.getY()].getLetter().exists();}
    bool board::isCurrentSet(){return getCurrentLetter().exists();}
    bool board::isCurrentPermanentlySet(){return isSet(getPosition(currentPos));}
    void board::clearLastRun(){lastWords.clear();lastScore=0;}
    void board::addWord(string word){lastWords.push_back(word);}
    int board::totalLastWords(){return lastWords.size();}
    void board::updateBoard(vector<position> &buffer,vector<position> &wordBuffer){
        bool error = false;
        int posX,posY;
            //WORD FINDER
            if((rowwise || colwise)){
                    clearLastRun();

                if(rowwise){
                    processBufferRowwiseX(buffer,wordBuffer);
                        error = checkBufferByX(wordBuffer);
                        if(!error){processBufferAndCalculateScore(wordBuffer);}
                    if(!error){
                        posY=buffer[0].getY();
                        for(int j=0;j<buffer.size();j++){
                            wordBuffer.clear();

                            posX=buffer[j].getX();
                            wordBuffer.push_back(buffer[j]);
                            for(int i=posY-1;isSet(posX,i)&& i>=0;i--){
                                wordBuffer.push_back(getPosition(posX,i));
                            }
                            for(int i=posY+1;isSet(posX,i)&& i<=14;i++){
                                wordBuffer.push_back(getPosition(posX,i));
                            }
                            error = checkBufferByY(wordBuffer);
                            if(!error){processBufferAndCalculateScore(wordBuffer);}
                        }
                    }
                }
                else if(colwise){
                    processBufferRowwiseY(buffer,wordBuffer);
                            error = checkBufferByY(wordBuffer);
                            if(!error){processBufferAndCalculateScore(wordBuffer);}
                    if(!error){
                        posX=buffer[0].getX();
                        for(int j=0;j<buffer.size();j++){
                            wordBuffer.clear();

                            posY=buffer[j].getY();
                            wordBuffer.push_back(buffer[j]);
                            for(int i=posX-1;isSet(i,posY)&& i>=0;i--){
                                wordBuffer.push_back(getPosition(i,posY));
                            }
                            for(int i=posX+1;isSet(i,posY)&& i<=14;i++){
                                wordBuffer.push_back(getPosition(i,posY));
                            }
                            error = checkBufferByX(wordBuffer);
                            if(!error){processBufferAndCalculateScore(wordBuffer);}
                        }
                    }
                }
                if(buffer.size()==7){setLastScore(50);}       ///BINGO!!!!
            }
    }
    string board::getLastWord(int i){return lastWords[i];}
    string board::getLastWordLower(int i){
        string data = lastWords[i];
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        return data;
    }
    vector<string>& board::getWords(){
        return lastWords;
    }
    int board::getLastScore(){return lastScore;}
    void board::setLastScore(int scr){lastScore+=scr;}
    void board::processBufferRowwiseY(vector<position> &buffer,vector<position> &wordBuffer){
        wordBuffer.clear();
        sort(buffer.begin(), buffer.end(),byY());
        wordBuffer.reserve(buffer.size());
        copy(buffer.begin(),buffer.end(),back_inserter(wordBuffer));

         int posY=buffer[0].getY();
         int posX=buffer[0].getX();
         int i=posY;
         for(;isSet(posX,i-1)&& i>0;i--){}//{wordBuffer.push_back(getPosition(i,posY
         posY = buffer[buffer.size()-1].getY();
         int j = posY;
         for(;isSet(posX,j+1)&& j<14;j++){}//{wordBuffer.push_back(getPosition(i,posY));}
         for(int n=i;n<=j;n++){
            if(isSet(posX,n)){
                wordBuffer.push_back(getPosition(posX,n));
            }
         }
    }
    void board::processBufferRowwiseX(vector<position> &buffer,vector<position> &wordBuffer){
         wordBuffer.clear();
         sort(buffer.begin(), buffer.end(),byX());
         wordBuffer.reserve(buffer.size());
         copy(buffer.begin(),buffer.end(),back_inserter(wordBuffer));

         int posY=buffer[0].getY();
         int posX=buffer[0].getX();
         int i=posX;
         for(;isSet(i-1,posY)&& i>0;i--){}//{wordBuffer.push_back(getPosition(i,posY
         posX = buffer[buffer.size()-1].getX();
         int j = posX;
         for(;isSet(j+1,posY)&& j<14;j++){}//{wordBuffer.push_back(getPosition(i,posY));}
         for(int n=i;n<=j;n++){
            if(isSet(n,posY)){
                wordBuffer.push_back(getPosition(n,posY));
            }
         }

    }
    bool board::isValidBuffer(vector<position> &buffer){
        clearLastRun();
        rowwise = true;
        colwise = true;
        int posX=buffer[0].getX();
        int posY=buffer[0].getY();
        bool error =true;
        if(playcount==0){
            for(int i = 0;i<buffer.size();i++){
                int p =buffer[i].getX();
                int q =buffer[i].getY();
                if(p==7 and q==7){
                    error = false;
                }
                if(buffer[i].getX()==posX){posX=buffer[i].getX();}
                else{colwise=false;}
                if(buffer[i].getY()==posY){posY=buffer[i].getY();}
                else{rowwise=false;}
            }
        }else{
            for(int i = 0;i<buffer.size();i++){
                int p =buffer[i].getX();
                int q =buffer[i].getY();
                if(//IF BUFFER TOUCHES ONE OF EXISTING LETTERS IN BOARD
                    isSet(p>0?p-1:p,q) ||isSet(p<14?p+1:p,q) ||
                    isSet(p,q>0?q-1:q) ||isSet(p,q<14?q+1:q)
                ){error=false;}

                if(buffer[i].getX()==posX){posX=buffer[i].getX();}
                else{colwise=false;}
                if(buffer[i].getY()==posY){posY=buffer[i].getY();}
                else{rowwise=false;}
            }
        }
        return error;
    }
    void board::processBufferAndCalculateScore(vector<position> &wordBuffer){
        int wSize=wordBuffer.size();
        if(wSize>1){
            string temp="";
            int tempScore=0;
            int mult =1;
            for(int i=0;i<wSize;i++){
                temp += wordBuffer[i].getLetter().getName();
                tempScore+=(wordBuffer[i].getLetter().getScore())*(getPosition(wordBuffer[i].getX(),wordBuffer[i].getY()).getAdder());
                mult*=getPosition(wordBuffer[i].getX(),wordBuffer[i].getY()).getMultiplier();
            }
            setLastScore(tempScore*mult);
            addWord(temp);
        }
    }
    bool board::checkBufferByX(vector<position> &wordBuffer){
        int wSize=wordBuffer.size();
        if(wSize>1){
            sort(wordBuffer.begin(), wordBuffer.end(),byX());
            for(int i = 0;i<wSize-1;i++){
                if((wordBuffer[i+1].getX() - wordBuffer[i].getX()) !=1){
                    wordBuffer.clear();
                    return true;
                }
            }
        }return false;
    }
    bool board::checkBufferByY(vector<position> &wordBuffer){
        int wSize=wordBuffer.size();
        if(wSize>1){
            sort(wordBuffer.begin(), wordBuffer.end(),byY());
            for(int i = 0;i<wSize-1;i++){
                if((wordBuffer[i+1].getY() - wordBuffer[i].getY()) !=1){
                    wordBuffer.clear();
                    return true;
                }
            }
        }return false;
    }
board::~board()
{
    //dtor
}
