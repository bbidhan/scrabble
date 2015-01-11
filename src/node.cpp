#include "node.h"


node::node(){key='X';is_end=false;level='A';}
node::node(char k_,bool e_){key=k_;is_end=e_;}
node::node(node &par):parent(&par){key='X';is_end=false;level='A';}
void node::cleanVector(vector<string> &myWords){
    sort( myWords.begin(), myWords.end() );
    myWords.erase( unique( myWords.begin(), myWords.end() ), myWords.end() );
}
int node::getLevel(){
    return (int)level - (int)'A';
}
vector<string> node::aiProcess(string word,char hook_into,int place){
    //myWords.clear();
    sort( word.begin(), word.end() );
    string word2 = word;
    //string dest="";
    word2.erase( unique( word2.begin(), word2.end() ), word2.end() );

    std::set_difference(word.begin(), word.end(), word2.begin(), word2.end(),
    std::inserter(word2, word2.end()));
    vector<string> myWords = this->getWords(word2,hook_into,place,"");

    /*for(int i=0;i<myWords.size();i++){
        cout<<myWords[i]<<"\t";
    }*/

    return myWords;


}
vector<string> node::aiProcess(string word,string hook_into,int offset){
    //myWords.clear();
    sort( word.begin(), word.end() );
    string word2 = word;
    //string dest="";
    word2.erase( unique( word2.begin(), word2.end() ), word2.end() );

    std::set_difference(word.begin(), word.end(), word2.begin(), word2.end(),
    std::inserter(word2, word2.end()));

    string pat_="";
    for(int i=0;i<offset;i++){
        pat_+="_";
    }
    vector<string> myWords = this->getWords_hOOkS(word2,pat_+hook_into,0,"");

    /*for(int i=0;i<myWords.size();i++){
        cout<<myWords[i]<<"\t";
    }*/

    return myWords;


}
vector<string> node::getWords_hOOkS(string word,string hook_into,int offset,string preFix=""){
    node *current = this;
    vector<string> myWords;
    vector<string> myTempWords;

    //if(0){
    //for(int cnt=this->getLevel();cnt<hook_into.size();cnt++){
      //  if(hook_into[cnt]=='_'){}
    //}
    //int posTemp=;
    //{}if((this->getLevel()+offset)>hook_into.size()-1)
    char hook=hook_into[this->getLevel()+offset];
    if((this->getLevel()+offset)>hook_into.size()-1){hook='_';}
    if(hook!='_' ){//}
        //if(this->getLevel()==place){
            current = &this->getChild(hook_into[this->getLevel()+offset]);
            if(current){
                if(current->is_end && this->getLevel()==(hook_into.size()-1+offset)
                   ){
                //setColor(6);
                   //cout<<current->getLevel();
                   //cout<<current->getWord()<<"\t";
                    //myWords.push_back(current->getWord());
                    myWords.push_back(preFix+hook_into[this->getLevel()+offset]);
                //setColor(15);
                }else{//cout<<current->getWord()<<"\t";
                }
                myTempWords = current->getWords_hOOkS(word,hook_into,offset,preFix+hook_into[this->getLevel()+offset]);
                copy(myTempWords.begin(),myTempWords.end(),back_inserter(myWords));
                //myWords = current->getWords(word);
            }
        }
        else {
    sort( word.begin(), word.end() );
    string word2 = word;
    word2.erase( unique( word2.begin(), word2.end() ), word2.end() );

    string dest = word2;
    std::set_difference(word.begin(), word.end(), word2.begin(), word2.end(),
    std::inserter(dest, dest.end()));
    word=dest;
    for(int i=0;i<word2.size();i++){
    //current = this->getLevel()==1?&this->getChild('n'):&this->getChild(word[i]);
    current = &this->getChild(word[i]);

        if(current){
            string word_=word;
            word_.erase(word_.begin()+i);

            if(current->is_end && this->getLevel()>=(hook_into.size()-1+offset)
               ){
                //cout<<current->getLevel();
                //cout<<current->getWord()<<"\t";
               myWords.push_back(preFix+word2[i]);
               //myWords.push_back(current->getWord());
            }else{//cout<<current->getWord()<<"\t";
            }
            //current->getWords(word_);
            myTempWords = current->getWords_hOOkS(word_,hook_into,offset,preFix+word2[i]);
           copy(myTempWords.begin(),myTempWords.end(),back_inserter(myWords));
            //myWords = current->getWords(word_);///RECURSIVE

        }

    }
    }

    return myWords;
}
vector<string> node::getWords(string word,char hook_into,int place,string preFix=""){
    node *current = this;
    vector<string> myWords;
    vector<string> myTempWords;

    //if(0){
    if(this->getLevel()==place){
        current = &this->getChild(hook_into);
        if(current){
            if(current->is_end){
            //setColor(6);
               //cout<<current->getLevel();
               //cout<<current->getWord()<<"\t";
                //myWords.push_back(current->getWord());
                myWords.push_back(preFix+hook_into);
            //setColor(15);
            }else{//cout<<current->getWord()<<"\t";
            }
            myTempWords = current->getWords(word,hook_into,place,preFix+hook_into);
            copy(myTempWords.begin(),myTempWords.end(),back_inserter(myWords));
            //myWords = current->getWords(word);
        }
    }
    else{
    sort( word.begin(), word.end() );
    string word2 = word;
    word2.erase( unique( word2.begin(), word2.end() ), word2.end() );

    string dest = word2;
    std::set_difference(word.begin(), word.end(), word2.begin(), word2.end(),
    std::inserter(dest, dest.end()));
    word=dest;
    for(int i=0;i<word2.size();i++){
    //current = this->getLevel()==1?&this->getChild('n'):&this->getChild(word[i]);
    current = &this->getChild(word[i]);

        if(current){
            string word_=word;
            word_.erase(word_.begin()+i);

            if(current->is_end && this->getLevel()>=place
               ){
                //cout<<current->getLevel();
                //cout<<current->getWord()<<"\t";
               myWords.push_back(preFix+word2[i]);
               //myWords.push_back(current->getWord());
            }else{//cout<<current->getWord()<<"\t";
            }
            //current->getWords(word_);
            myTempWords = current->getWords(word_,hook_into,place,preFix+word2[i]);
           copy(myTempWords.begin(),myTempWords.end(),back_inserter(myWords));
            //myWords = current->getWords(word_);///RECURSIVE

        }

    }
    }
    return myWords;
}
node& node::getChild(char key_){
    for(int j=0;j<this->child.size();j++){
        if(this->child[j]->key==key_){
            return *this->child[j];
        }
    }
    //return NULL;
}
void node::insert_word(string word,bool final_is_leaf,vector<node*> &finals){
    node *current = this;
    for(int i=0;i<word.length();i++){
        //int letter = (int)word[i]-(int)'a';//cout<<current->child.size()<<endl;

        bool has_node = false;
        int j=0;
        for(j=0;j<current->child.size();j++){
            if(current->child[j]->key==word[i]){
                //cout<<word[i]<<" in '"<<word<<"' already has child "<<current->child[j]->key<<endl;
                has_node=true;
                break;
        }
        }
        if(!has_node){
                if(final_is_leaf && i == word.length()-1){
                    current->child.push_back(finals[(int)word[i]-(int)'a']);
                    //if(word[i]=='s'){
                      //  finals_parents.push_back(current);
                    //}
                    //current->child.back()->parents.push_back(current);
                    break;
                }
                    current->child.push_back(new node(*current));
                    current->child.back()->key=word[i];
                    current->child.back()->level='A' + i + 1;
                    //current->child.back()->parents.push_back(current);
                    //nodes++;
                    //cout<<word[i]<<" in "<<word<<" doesnt have child "<<current->child.back()->key<<endl;
                    current=current->child.back();
        }
        if(has_node){current=current->child[j];}

    }
    if(!final_is_leaf)
        current->is_end = true;
}
bool node::search_word(string word){
    node *current = this;
    for(int i=0;i<word.length();i++){
        //int letter = (int)word[i]-(int)'a';//cout<<letter<<endl;
        bool has_node = false;
        int j=0;
        for(j=0;j<current->child.size();j++){
            if(current->child[j]->key==word[i]){
                //cout<<word[i]<<" in '"<<word<<"' already has child "<<current->child[j]->key<<endl;
                has_node=true;
                break;
            }
        }
        if(has_node){current=current->child[j];}else{return false;}
        //cout<<current->parent->key;
    }
    if(current->is_end){
        return true;
    }
    //cout<<word<<"\t";
    return false;
}


node::~node()
{
    //cout<<"a"<<endl;
    for(int i=0;i<child.size();i++){
        if(child[i]->child.size()!=0)
            delete child[i];
    }
}
