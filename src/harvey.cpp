#include "harvey.h"

harvey::harvey():player() {}
harvey::harvey(string nam,bool human):player(nam) {
    if(!human) {
        isAI=true;
        //finals.reserve(26);
        for(int i =0; i<26; i++) {
            finals.push_back(new node((char)(int('a') + i),true));
        }
        head = new node();
        ifstream myfile("sowpods.txt");
        string previous="";
        string current="";
        int i =0;
        int j=0;
        int k=0;
        while (getline(myfile,current)//&& i<70
              ) {
            bool final_is_leaf = false;
            //cout<<previous<<"\t\t"<<current<<endl;

            for(int p =0; p<previous.size(); p++) {
                if(previous[p]!=current[p]) {
                    final_is_leaf=true;
                    j++;
                    p=987;
                }
            }

             head->insert_word(previous,final_is_leaf,this->finals) ;
            i++;
            previous=current;
        }
        head->insert_word(previous,true,this->finals);
        myfile.close();
        cout<<i<<" words!"<<endl;
        cout<<k<<" nodes!"<<endl;
        cout<<j<<" leaves!"<<endl;
        /*vector<string> patterns = head->aiProcess("daersadc","ad",2);
        for(int as=0;as<patterns.size();as++){
            cout<<patterns[as]<<endl;
        }
        getch();
        getch();
        getch();
        getch();*/
    }
}
bool harvey::identicalNodes(node* node1,node* node2) {
    //cout<<""<<node1->key;
    //cout<<" "<<node2->child.size();
    if(node1->key==node2->key) {
        if(node1->child.size()==node2->child.size()) {
            for(int i=0; i<node1->child.size(); i++) {
                if(node1->child[i]->key!=node2->child[i]->key) {
                    return false;
                } else {
                    return identicalNodes(node1->child[i],node2->child[i]);
                }
            }
            //return true;
        }
    }
    return false;
}
bool harvey::processDuplicateNode(node* delNode,node* pointParentToNode) {
    //delNode->parent->child.push_back(pointParentToNode);
    for(int i =0; i<delNode->parent->child.size(); i++) {
        if(delNode->parent->child[i]->key==pointParentToNode->key) {
            delNode->parent->child[i] = pointParentToNode;;
            break;
        }
    }
    //delete delNode;
}
void harvey::addBufferToList(vector< bufferd_score >& buff_scores,int& myScoreCF,vector<position>& buffer){
    bool error=false;
    for(int j=0;j<buff_scores.size();j++){
        if(buff_scores[j].score == myScoreCF &&
                   buff_scores[j].buff.size()==buffer.size()){
            for(int i=0;i<buff_scores[j].buff.size();i++){
                if(buff_scores[j].buff[i].getLetter().getName()==buffer[i].getLetter().getName()&&
                    buff_scores[j].buff[i].getX()==buffer[i].getX() &&
                    buff_scores[j].buff[i].getY()==buffer[i].getY()
                   ){error=true;/*STOP INSERTION*/}else{error=false;break;}
            }
            if(error){break;}
        }else{error=false;/*START INSERTION*/}
    }
    if(!error){
    if(buff_scores.size()>=50 && myScoreCF>buff_scores[49].score){
        int buff_count=0;
        for(;buff_count<50;buff_count++){
            if(myScoreCF>buff_scores[buff_count].score){
                buff_scores.insert(buff_scores.begin()+buff_count,bufferd_score(myScoreCF,buffer));
                break;
            }
        }
    }
    if(buff_scores.size()<50&& buff_scores.size()>1){
        int buff_count=0;
        bool insert_at_last = true;
        for(;buff_count<buff_scores.size();buff_count++){
            if(myScoreCF>=buff_scores[buff_count].score){
                buff_scores.insert(buff_scores.begin()+buff_count,bufferd_score(myScoreCF,buffer));
                insert_at_last=false;
                break;
            }
        }
        if(insert_at_last)buff_scores.push_back(bufferd_score(myScoreCF,buffer));
    }
    if(buff_scores.size()==1){
        if(buff_scores[0].score>=myScoreCF){
            buff_scores.insert(buff_scores.begin()+1,bufferd_score(myScoreCF,buffer));
        }else{buff_scores.insert(buff_scores.begin(),bufferd_score(myScoreCF,buffer));}
    }
    if(buff_scores.size()==0){
        buff_scores.insert(buff_scores.begin(),bufferd_score(myScoreCF,buffer));
    }
    }
}
int harvey::minimaxBoardProcess(board tempBoard, bag tempBag,vector< bufferd_score >& buff_scores){
    vector<position> bestWordBuffer;
    DrawEngine graphics;
    graphics.gotoxy(0,15);
    int loop = buff_scores.size()<3?buff_scores.size():3;
    for(int cnter=0;cnter<loop;cnter++){
                        cout<<endl<<buff_scores[cnter].score;
                        for(int cnters=12340;cnters<buff_scores[cnter].buff.size();cnters++){
                            cout<<" "<<buff_scores[cnter].buff[cnters].getLetter().getName();
                            cout<<" "<<buff_scores[cnter].buff[cnters].getX();
                            cout<<" "<<buff_scores[cnter].buff[cnters].getY();
                        }
    }
    for(int ct=0;ct<loop;ct++){
            bool error = tempBoard.isValidBuffer(buff_scores[ct].buff);
            if(!error)tempBoard.updateBoard(buff_scores[ct].buff,bestWordBuffer);

            for(int i = 0; i<buff_scores[ct].buff.size(); i++) {
                tempBoard.getPosition(buff_scores[ct].buff[i]).setLetter(buff_scores[ct].buff[i].getLetter());
                tempBoard.getPosition(buff_scores[ct].buff[i]).setAdder(1);
                tempBoard.getPosition(buff_scores[ct].buff[i]).setMultiplier(1);
            }
            buff_scores[ct].score -= this->aiProcess(tempBoard,tempBag,false,ct);
        }
}
int harvey::aiProcess(board &myBoard, bag &myBag,bool minimax,int countID) {
    vector<letter> temp_letters;
    copy(letters.begin(),letters.end(),back_inserter(temp_letters));
    if(!minimax){
        letters.clear();
         letter D('D',4,2);letters.push_back(D);
         letter A('A',9,1);letters.push_back(A);
         letter N('N',6,1);letters.push_back(N);
         letter G('G',3,2);letters.push_back(G);
         letter E('E',12,1);letters.push_back(E);
         letter R('R',6,1);letters.push_back(R);
         letter S('S',4,1);letters.push_back(S);
    }
    vector< bufferd_score > buff_scores;
    int totMoves=0;
    DrawEngine graphics;
    vector<position> bestBuffer;
    int bestScore = 0;
    vector<position> bestWordBuffer;
    bool error = true;
    if(myBoard.getPlayCount()== 0) {
        for(int t = 0; t<letters.size(); t++) {
            for(int v =0; v<8; v++) {
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

                for(int y = 0; y<hookedWords.size(); y++) {
                    buffer.push_back(tempPos);
                    for(int r = 0; r<letters.size(); r++) {
                        if((letters[r].getASCII() + 32) == jpt) {
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

                    for(int q = 0; q<word.size(); q++) {
                        for(int r = 0; r<letters.size(); r++) {
                            if((char)(letters[r].getASCII() + 32) == word[q]
                                    && q !=v
                              ) {
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

                    if(buffer.size()>1) {
                        error = myBoard.isValidBuffer(buffer);
                        if(!error)myBoard.updateBoard(buffer,wordBuffer);
                        this->clearLastRun();
                        if(myBoard.totalLastWords()>0 && !error) {
                            //DICTIONARY CHECK HERE
                            for(int x = 0; x<myBoard.totalLastWords(); x++) {
                                if(this->head->search_word(myBoard.getLastWordLower(x))==0) {
                                    error = true;
                                    break;
                                }
                                //this->addWord(myBoard.getLastWord(x));
                            }
                            if(!error) {
                                //cout<<error;
                                if(myBoard.getLastScore()>bestScore) {
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


    } else {

        for(int i =0; i<15; i++) {//PLAY HOOKS
            for(int j =0; j<15; j++) {
                if(myBoard.isSet(i,j)) {
                    for(int v =0; v<8; v++) {
                        if(!myBoard.isSet(i,j-1)) {
                            vector<string> hookedWords = head->aiProcess(getWordifiedRack(),(char)((int)myBoard.getPosition(i,j).getLetter().getASCII()+32),v);
                            myBoard.calcc+= hookedWords.size();
                            vector<position> buffer;
                            vector<position> wordBuffer;
                            //string word = hookedWords[0];

                            for(int y = 0; y<hookedWords.size(); y++) {
                                //cout<<hookedWords[y]<<endl;
                                string word = hookedWords[y];
                                for(int q = 0; q<word.size(); q++) {
                                    for(int r = 0; r<letters.size(); r++) {
                                        if((char)(letters[r].getASCII() + 32) == word[q]
                                                && q !=v
                                                && !myBoard.isSet(i,j-v+q)
                                                && j-v+q >=0
                                                && j-v+q <15
                                          ) {
                                            myBoard.setCurrentX(i);
                                            myBoard.setCurrentY(j-v+q);
                                            myBoard.setCurrentLetter(this->getLetters(r));
                                            //graphics.gotobxy(i,j-v+q);
                                            //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
                                            this->eraseLetter(r);
                                            buffer.push_back(myBoard.getCurrentPos());
                                            break;
                                        }
                                    }
                                }

                                if(buffer.size()>1) {
                                    error = myBoard.isValidBuffer(buffer);
                                    if(!error)myBoard.updateBoard(buffer,wordBuffer);
                                    this->clearLastRun();
                                    if(myBoard.totalLastWords()>0 && !error) {
                                        //DICTIONARY CHECK HERE
                                        for(int x = 0; x<myBoard.totalLastWords(); x++) {
                                            if(this->head->search_word(myBoard.getLastWordLower(x))==0) {
                                                error = true;
                                                break;
                                            }
                                            //this->addWord(myBoard.getLastWord(x));
                                        }
                                        if(!error) {
                                            int myScoreCF = evaluateRack(myBoard.getLastScore());
                                            totMoves++;
                                            addBufferToList(buff_scores,myScoreCF,buffer);


                                            if(myScoreCF>bestScore) {
                                                bestBuffer.clear();
                                                copy(buffer.begin(),buffer.end(),back_inserter(bestBuffer));
                                                bestScore = myScoreCF;
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
        for(int i =0; i<15; i++) {
            for(int j =0; j<15; j++) {
                if(myBoard.isSet(i,j)) {
                    for(int v =0; v<8; v++) {
                        if(!myBoard.isSet(i-1,j)) {
                            vector<string> hookedWords = head->aiProcess(getWordifiedRack(),(char)((int)myBoard.getPosition(i,j).getLetter().getASCII()+32),v);
                            myBoard.calcc+= hookedWords.size();
                            vector<position> buffer;
                            vector<position> wordBuffer;
                            //string word = hookedWords[0];

                            for(int y = 0; y<hookedWords.size(); y++) {
                                //cout<<hookedWords[y]<<endl;
                                string word = hookedWords[y];
                                for(int q = 0; q<word.size(); q++) {
                                    for(int r = 0; r<letters.size(); r++) {
                                        if((char)(letters[r].getASCII() + 32) == word[q]
                                                && q !=v
                                                && !myBoard.isSet(i-v+q,j)
                                                && i-v+q >=0
                                                && i-v+q<15
                                          ) {
                                            myBoard.setCurrentX(i-v+q);
                                            myBoard.setCurrentY(j);
                                            myBoard.setCurrentLetter(this->getLetters(r));
                                            //graphics.gotobxy(i-v+q,j);
                                            //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
                                            this->eraseLetter(r);
                                            buffer.push_back(myBoard.getCurrentPos());
                                            break;
                                        }
                                    }
                                }

                                if(buffer.size()>1) {
                                    error = myBoard.isValidBuffer(buffer);
                                    if(!error)myBoard.updateBoard(buffer,wordBuffer);
                                    this->clearLastRun();
                                    if(myBoard.totalLastWords()>0 && !error) {
                                        //DICTIONARY CHECK HERE
                                        for(int x = 0; x<myBoard.totalLastWords(); x++) {
                                            if(this->head->search_word(myBoard.getLastWordLower(x))==0) {
                                                error = true;
                                                break;
                                            }
                                            //this->addWord(myBoard.getLastWord(x));
                                        }
                                        if(!error) {
                                            int myScoreCF = evaluateRack(myBoard.getLastScore());
                                            totMoves++;
                                            addBufferToList(buff_scores,myScoreCF,buffer);
                                            if(myScoreCF>bestScore) {
                                                bestBuffer.clear();
                                                copy(buffer.begin(),buffer.end(),back_inserter(bestBuffer));
                                                bestScore = myScoreCF;
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


        for(int i =0; i<15; i++) {//PLAY BY MATCHING PATTERN
            for(int j =0; j<15; j++) {
                if(myBoard.isSet(i,j) && (!myBoard.isSet(i-1,j) || i==0)) {
                    vector<string> patterns;
                    patterns.clear();
                    string pattern="";
                    pattern+=myBoard.getPosition(i,j).getLowerLetter();
                    int cnt =0;
                    //int currCnt =0;
                    for(int x_ =i+1; x_<15&& cnt<8; x_++) {
                        if(!myBoard.isSet(x_,j)) {
                            pattern+="_";
                            cnt++;
                        } else {
                            //currCnt++;
                            //if(currCnt>cnt){
                            pattern+=myBoard.getPosition(x_,j).getLowerLetter();
                            for(int x__ =x_+1; x__<15; x__++,x_++) {
                                if(myBoard.isSet(x__,j)) {
                                    pattern+=myBoard.getPosition(x__,j).getLowerLetter();
                                    //cnt++;
                                } else {
                                    x_++;
                                    break;
                                }
                            }
                            patterns.push_back(pattern);
                            pattern+="_";
                            cnt++;
                            //}
                        }
                    }
                    for(int as=0; as<patterns.size(); as++) {
                        //cout<<"\t"<<patterns[as]<<"                  "<<getWordifiedRack()<<endl;
                        int v= 0;
                        string pat_=patterns[as];
                        for(int it=0; it<patterns[as].size(); it++) {
                            if(pat_[it]=='_') {
                                v++;
                            }
                        }
                        v=letters.size()-v;
                        for(int it=1; it<=v; it++) {
                            pat_=patterns[as];
                            vector<string> hookedWords = head->aiProcess(getWordifiedRack(),patterns[as],it);
                            myBoard.calcc+= hookedWords.size();
                            vector<position> buffer;
                            vector<position> wordBuffer;
                            string pat__="";
                            for(int qw=0; qw<it; qw++) {
                                pat__+="_";
                            }
                            pat_=pat__+pat_;
                            //string word = hookedWords[0];
                            //cout<<hookedWords.size()<<endl;
                            for(int y = 0; y<hookedWords.size(); y++) {
                                //cout<<hookedWords[y]<<endl;
                                string word = hookedWords[y];
                                for(int q = 0; q<word.size()&&word!=pat_; q++) {
                                    for(int r = 0; r<letters.size(); r++) {
                                        //cout<<(char)(letters[r].getASCII() + 32)<<"\t"<<word[q]<<"\t"<<pat_[q+it]<<"\t"<<j-it+q<<endl;
                                        if((char)(letters[r].getASCII() + 32) == word[q]
                                                && (pat_[q] =='_' || q>=pat_.size() )
                                                //&& !myBoard.isSet(i-it+q,j)
                                                && i-it+q >=0
                                                && i-it+q <15
                                          ) {
                                            myBoard.setCurrentX(i-it+q);
                                            myBoard.setCurrentY(j);
                                            myBoard.setCurrentLetter(this->getLetters(r));
                                            //cout<<myBoard.getCurrentLetter().getName()<<endl;
                                            //graphics.gotobxy(i,j-v+q);
                                            //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
                                            this->eraseLetter(r);
                                            buffer.push_back(myBoard.getCurrentPos());
                                            break;
                                        }
                                    }
                                }

                                if(buffer.size()>=1) {
                                    error = myBoard.isValidBuffer(buffer);
                                    //cout<<error;
                                    if(!error)
                                        myBoard.updateBoard(buffer,wordBuffer);
                                    //cout<<myBoard.getLastWordLower(0)<<endl;
                                    this->clearLastRun();
                                    //cout<<myBoard.totalLastWords();
                                    if(myBoard.totalLastWords()>0 && !error
                                      ) {
                                        //DICTIONARY CHECK HERE
                                        //cout<<"\t"<<patterns[as]<<"                  "<<endl;
                                        error=0;
                                        for(int x = 0; x<myBoard.totalLastWords(); x++) {
                                            //cout<<myBoard.getLastWordLower(x)<<endl;
                                            //cout<<"\t"<<patterns[as]<<"                  "<<endl;
                                            if(this->head->search_word(myBoard.getLastWordLower(x))==0) {
                                                error = true;
                                                break;
                                            }
                                            //this->addWord(myBoard.getLastWord(x));
                                        }
                                        if(!error) {
                                            int myScoreCF = evaluateRack(myBoard.getLastScore());
                                            totMoves++;
                                            addBufferToList(buff_scores,myScoreCF,buffer);

                                            if(myScoreCF>bestScore) {
                                                bestBuffer.clear();
                                                copy(buffer.begin(),buffer.end(),back_inserter(bestBuffer));
                                                bestScore = myScoreCF;
                                                //cout<<"\t"<<patterns[as]<<"                  "<<endl;
                                                for(int x = 0; x<myBoard.totalLastWords(); x++) {
                                                    //cout<<myBoard.getLastWordLower(x)<<"                  "<<endl;
                                                }
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
            }}
        for(int i =0; i<15; i++) {
            for(int j =0; j<15; j++) {
                if(myBoard.isSet(i,j) && (!myBoard.isSet(i,j-1) || j==0)) {
                    vector<string> patterns;
                    patterns.clear();
                    string pattern="";
                    pattern+=myBoard.getPosition(i,j).getLowerLetter();
                    int cnt =0;
                    //int currCnt =0;
                    for(int x_ =j+1; x_<15&& cnt<8; x_++) {
                        if(!myBoard.isSet(i,x_)) {
                            pattern+="_";
                            cnt++;
                        } else {
                            //currCnt++;
                            //if(currCnt>cnt){
                            pattern+=myBoard.getPosition(i,x_).getLowerLetter();
                            for(int x__ =x_+1; x__<15; x__++,x_++) {
                                if(myBoard.isSet(i,x__)) {
                                    pattern+=myBoard.getPosition(i,x__).getLowerLetter();
                                    //cnt++;
                                } else {
                                    x_++;
                                    break;
                                }
                            }
                            patterns.push_back(pattern);
                            pattern+="_";
                            cnt++;
                            //}
                        }
                    }
                    for(int as=0; as<patterns.size(); as++) {
                        //cout<<"\t"<<patterns[as]<<"                  "<<getWordifiedRack()<<endl;
                        int v= 0;
                        string pat_=patterns[as];
                        for(int it=0; it<patterns[as].size(); it++) {
                            if(pat_[it]=='_') {
                                v++;
                            }
                        }
                        v=letters.size()-v;
                        for(int it=1; it<=v; it++) {
                            pat_=patterns[as];
                            vector<string> hookedWords = head->aiProcess(getWordifiedRack(),patterns[as],it);
                            myBoard.calcc+= hookedWords.size();
                            vector<position> buffer;
                            vector<position> wordBuffer;
                            string pat__="";
                            for(int i=0; i<it; i++) {
                                pat__+="_";
                            }
                            pat_=pat__+pat_;
                            //string word = hookedWords[0];
                            //cout<<hookedWords.size()<<endl;
                            for(int y = 0; y<hookedWords.size(); y++) {
                                //cout<<hookedWords[y]<<endl;
                                string word = hookedWords[y];
                                for(int q = 0; q<word.size()&&word!=pat_; q++) {
                                    for(int r = 0; r<letters.size(); r++) {
                                        //cout<<(char)(letters[r].getASCII() + 32)<<"\t"<<word[q]<<"\t"<<pat_[q+it]<<"\t"<<j-it+q<<endl;
                                        if((char)(letters[r].getASCII() + 32) == word[q]
                                                && (pat_[q] =='_' || q>=pat_.size() )
                                                //&& !myBoard.isSet(i-it+q,j)
                                                && j-it+q >=0
                                                && j-it+q <15
                                          ) {
                                            myBoard.setCurrentX(i);
                                            myBoard.setCurrentY(j-it+q);
                                            myBoard.setCurrentLetter(this->getLetters(r));
                                            //cout<<myBoard.getCurrentLetter().getName()<<endl;
                                            //graphics.gotobxy(i,j-v+q);
                                            //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
                                            this->eraseLetter(r);
                                            buffer.push_back(myBoard.getCurrentPos());
                                            break;
                                        }
                                    }
                                }

                                if(buffer.size()>=1) {
                                    error = myBoard.isValidBuffer(buffer);
                                    //cout<<error;
                                    if(!error)
                                        myBoard.updateBoard(buffer,wordBuffer);
                                    //cout<<myBoard.getLastWordLower(0)<<endl;
                                    this->clearLastRun();
                                    //cout<<myBoard.totalLastWords();
                                    if(myBoard.totalLastWords()>0 && !error
                                      ) {
                                        //DICTIONARY CHECK HERE
                                        //cout<<"\t"<<patterns[as]<<"                  "<<endl;
                                        error=0;
                                        for(int x = 0; x<myBoard.totalLastWords(); x++) {
                                            //cout<<myBoard.getLastWordLower(x)<<endl;
                                            //cout<<"\t"<<patterns[as]<<"                  "<<endl;
                                            if(this->head->search_word(myBoard.getLastWordLower(x))==0) {
                                                error = true;
                                                break;
                                            }
                                            //this->addWord(myBoard.getLastWord(x));
                                        }
                                        if(!error) {
                                            int myScoreCF = evaluateRack(myBoard.getLastScore());
                                            totMoves++;
                                            addBufferToList(buff_scores,myScoreCF,buffer);

                                            if(myScoreCF>bestScore) {
                                                bestBuffer.clear();
                                                copy(buffer.begin(),buffer.end(),back_inserter(bestBuffer));
                                                bestScore = myScoreCF;
                                                //cout<<"\t"<<patterns[as]<<"                  "<<endl;
                                                for(int x = 0; x<myBoard.totalLastWords(); x++) {
                                                    //cout<<myBoard.getLastWordLower(x)<<"                  "<<endl;
                                                }
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
            }}

        for(int i =0; i<15; i++) {//PLAY PARALLELS
            for(int j =0; j<15; j++) {
                if(myBoard.isSet(i,j)) {
                    playAnchored(myBoard,myBag,i,j-1,bestBuffer,bestScore,error,false,totMoves,buff_scores);
                    playAnchored(myBoard,myBag,i,j+1,bestBuffer,bestScore,error,false,totMoves,buff_scores);
                    playAnchored(myBoard,myBag,i-1,j,bestBuffer,bestScore,error,true,totMoves,buff_scores);
                    playAnchored(myBoard,myBag,i+1,j,bestBuffer,bestScore,error,true,totMoves,buff_scores);
                }
            }
        }


    }
    if(minimax){
        if(myBoard.getPlayCount()!= 0 && getName()=="HARVEY"){
            this->minimaxBoardProcess(myBoard,myBag,buff_scores);
            int tempScr=-1000;
            int id=0;
            for(int ct=0;ct<3;ct++){
                if(buff_scores[ct].score>tempScr){
                    id=ct;
                    tempScr=buff_scores[ct].score;
                }
            }
            bestBuffer.clear();
            copy(buff_scores[id].buff.begin(),buff_scores[id].buff.end(),back_inserter(bestBuffer));
        }
    }
    else{
        letters.clear();
        copy(temp_letters.begin(),temp_letters.end(),back_inserter(letters));
        graphics.gotoxy(0,30+countID);
        cout<<endl<<buff_scores[0].score;
                        for(int cnters=123210;cnters<buff_scores[0].buff.size();cnters++){
                            cout<<" "<<buff_scores[0].buff[cnters].getLetter().getName();
                            cout<<" "<<buff_scores[0].buff[cnters].getX();
                            cout<<" "<<buff_scores[0].buff[cnters].getY();
                        }
        return bestScore;
        }


    if(bestScore>0) {
        graphics.gotoxy(30,0);
        cout<<"                                         ";
        graphics.gotoxy(30,0);
        if(myBoard.getPlayCount()!=0 && getName()=="HARVEY"){
                cout<<bestScore<<"  ";
                for(int cnter=1231231230;cnter<10;cnter++){
                        cout<<endl<<buff_scores[cnter].score;
                        for(int cnters=0;cnters<buff_scores[cnter].buff.size();cnters++){
                            cout<<" "<<buff_scores[cnter].buff[cnters].getLetter().getName();
                            cout<<" "<<buff_scores[cnter].buff[cnters].getX();
                            cout<<" "<<buff_scores[cnter].buff[cnters].getY();
                        }
                }
        }

        this->clearLastRun();
        error = myBoard.isValidBuffer(bestBuffer);
        if(!error)myBoard.updateBoard(bestBuffer,bestWordBuffer);
        bestScore = myBoard.getLastScore();
        graphics.gotoxy(35,0);
        cout<<"                                         ";
        graphics.gotoxy(35,0);
                cout<<bestScore<<"  ";
        //cout<<bestScore;
        this->setLastScore(myBoard.getLastScore());
        for(int x = 0; x<myBoard.totalLastWords(); x++) {
            this->addWord(myBoard.getLastWord(x));
        }
        this->finalizeWords();
        for(int i = 0; i<bestBuffer.size(); i++) {
            myBoard.getPosition(bestBuffer[i]).setLetter(bestBuffer[i].getLetter());
            myBoard.getPosition(bestBuffer[i]).setAdder(1);
            myBoard.getPosition(bestBuffer[i]).setMultiplier(1);
            graphics.gotobxy(bestBuffer[i].getX(),bestBuffer[i].getY());
            cout<<bestBuffer[i].getLetter().getName();
            for(int q = 0; q<letters.size(); q++) {
                if(letters[q].getASCII() == bestBuffer[i].getLetter().getASCII()) {
                    this->eraseLetter(q);
                    break;
                }
            }

        }
        int myScoreCF = evaluateRack(myBoard.getLastScore());

        for(int i = 0; i<bestBuffer.size(); i++) {
            if(myBag.lettersLeft()>0) {
                this->pullLetterFromBag(myBag);
            }
        }

        this->setTotalScore();
    }

    return bestScore;
}
void harvey::playAnchored(board &myBoard, bag &myBag,int i_,int j_,vector<position>& bestBuffer,int& bestScore,bool error,bool is_i,int& totMoves,vector< bufferd_score >& buff_scores) {
    if(!myBoard.isSet(i_,j_)) {
        for(int t = 0; t<letters.size(); t++) {

            vector<position> buffer;
            vector<position> wordBuffer;
            myBoard.setCurrentX(i_);
            myBoard.setCurrentY(j_);
            myBoard.setCurrentLetter(this->getLetters(t));
            //graphics.gotobxy(i,j-1);
            //if(!myBoard.isSet(i,j-2+q))cout<<getLetters(r).getName();
            int jpt =this->getLetters(t).getASCII()+32;

            //this->eraseLetter(t);
            position tempPos = myBoard.getCurrentPos();
            buffer.push_back(tempPos);

            error = myBoard.isValidBuffer(buffer);
            if(!error)myBoard.updateBoard(buffer,wordBuffer);
            this->clearLastRun();
            if(myBoard.totalLastWords()>0 && !error) {
                //DICTIONARY CHECK HERE
                for(int x = 0; x<myBoard.totalLastWords(); x++) {
                    if(this->head->search_word(myBoard.getLastWordLower(x))==0) {
                        error = true;
                        break;
                    }
                    //this->addWord(myBoard.getLastWord(x));
                }
                if(!error) {
                    buffer.clear();

                    for(int v =0; v<7; v++) {
                        string letters__ = getWordifiedRack();
                        letters__.erase(letters__.begin()+t);

                        vector<string> hookedWords = head->aiProcess(letters__,(char)((int)jpt),v);
                        myBoard.calcc+= hookedWords.size();

                        //string word = hookedWords[0];

                        for(int y = 0; y<hookedWords.size(); y++) {
                            buffer.push_back(tempPos);
                            for(int r = 0; r<letters.size(); r++) {
                                if((letters[r].getASCII() + 32) == jpt) {
                                    this->eraseLetter(r);
                                    break;
                                }
                            }
                            string word = hookedWords[y];
                            for(int q = 0; q<word.size(); q++) {
                                for(int r = 0; r<letters.size(); r++) {
                                    if(!is_i
                                            && (char)(letters[r].getASCII() + 32) == word[q]
                                            && q !=v
                                            && !myBoard.isSet(i_-v+q,j_)
                                            && i_-v+q >=0
                                            && i_-v+q <15
                                            && j_>=0
                                            && j_<15
                                      ) {
                                        myBoard.setCurrentX(i_-v+q);
                                        myBoard.setCurrentY(j_);
                                        myBoard.setCurrentLetter(this->getLetters(r));
                                        this->eraseLetter(r);
                                        buffer.push_back(myBoard.getCurrentPos());
                                        break;
                                    }
                                    if(is_i
                                            && (char)(letters[r].getASCII() + 32) == word[q]
                                            && q !=v
                                            && !myBoard.isSet(i_,j_-v+q)
                                            && j_-v+q >=0
                                            && j_-v+q <15
                                            && i_>=0
                                            && i_<15
                                      ) {
                                        myBoard.setCurrentX(i_);
                                        myBoard.setCurrentY(j_-v+q);
                                        myBoard.setCurrentLetter(this->getLetters(r));
                                        //graphics.gotobxy(i-v+q,j-1);
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

                            if(buffer.size()>1) {
                                error = myBoard.isValidBuffer(buffer);
                                if(!error)myBoard.updateBoard(buffer,wordBuffer);
                                this->clearLastRun();
                                if(myBoard.totalLastWords()>0 && !error) {
                                    //DICTIONARY CHECK HERE
                                    for(int x = 0; x<myBoard.totalLastWords(); x++) {
                                        if(this->head->search_word(myBoard.getLastWordLower(x))==0) {
                                            error = true;
                                            break;
                                        }
                                        //this->addWord(myBoard.getLastWord(x));
                                    }
                                    if(!error) {
                                        int myScoreCF = evaluateRack(myBoard.getLastScore());
                                        totMoves++;
                                        addBufferToList(buff_scores,myScoreCF,buffer);
                                        if(myScoreCF>bestScore) {
                                            bestBuffer.clear();
                                            copy(buffer.begin(),buffer.end(),back_inserter(bestBuffer));
                                            bestScore = myScoreCF;
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
}
int harvey::evaluateRack(int scr) {
    int myScoreCF = scr;
    if(getName()=="Asters") {
        int vowels =0;
        int consonants =0;
        for(int cnt =0 ; cnt<letters.size(); cnt++) {
            if(
                getLetters(cnt).getName()=='A' ||
                getLetters(cnt).getName()=='E' ||
                getLetters(cnt).getName()=='I' ||
                getLetters(cnt).getName()=='O' ||
                getLetters(cnt).getName()=='U' //||
                //getLetters(cnt).getName()=='S')
                //letters.size()==5
            ) {
                vowels++;

            } else {
                consonants++;
            }
        }
        //if(letters.size()==5){
        //if(letters.size()==5){
        /*if(vowels-consonants == 0 && (vowels!=0 || consonants!=0)){myScoreCF +=5;}//else{myScoreCF-=5;}
        if(vowels-consonants == 1 && (vowels!=0 || consonants!=0)){myScoreCF +=4;}//else{myScoreCF-=4;}
        if(vowels-consonants == -1 && (vowels!=0 || consonants!=0)){myScoreCF +=4;}//else{myScoreCF-=4;}
        if(vowels-consonants == -2 && (vowels!=0 || consonants!=0)){myScoreCF -=4;}//else{myScoreCF-=4;}
        if(vowels-consonants == 2 && (vowels!=0 || consonants!=0)){myScoreCF -=4;}//else{myScoreCF-=4;}
        if(vowels-consonants == -3 && (vowels!=0 || consonants!=0)){myScoreCF -=5;}//else{myScoreCF-=4;}
        if(vowels-consonants == 3 && (vowels!=0 || consonants!=0)){myScoreCF -=5;}//else{myScoreCF-=4;}
        if(vowels-consonants == -4 && (vowels!=0 || consonants!=0)){myScoreCF -=5;}//else{myScoreCF-=4;}
        if(vowels-consonants == 4 && (vowels!=0 || consonants!=0)){myScoreCF -=5;}//else{myScoreCF-=4;}
        */
    }
    return myScoreCF;
}
harvey::~harvey() {
    cout<<getName();
    delete head;
}
