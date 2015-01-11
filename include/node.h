#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class node{
public:
    bool is_end;
    char key;
    char level;
    node* parent;
    //vector<node*> parents;
    vector<node*> child;
    node();
    node(char k_,bool e_);
    node(node &par);
    void cleanVector(vector<string> &myWords);
    int getLevel();
    vector<string> aiProcess(string word,char hook_into,int place);
    vector<string> aiProcess(string word,string hook_into,int offset);
    vector<string> getWords(string word,char hook_into,int place,string preFix);
    vector<string> getWords_hOOkS(string word,string hook_into,int offset,string preFix);
    string getWord();
    node& getChild(char key_);
    void insert_word(string word,bool,vector<node*>&);
    bool search_word(string word);

    virtual ~node();

    protected:
    private:
};

#endif // NODE_H
