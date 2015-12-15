//
//  Trie.h
//  130aProject
//
//  Created by Ray Ouyang on 7/5/15.
//  Copyright (c) 2015 Ray Ouyang. All rights reserved.
//

#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

const int StrMaxElem = 81;
const int TrieMaxElem = 26;
class MultiSet;

class BasicTrieNode {
private:
    MultiSet *ptr2ms;
public:
    BasicTrieNode();
    virtual int             WhoAmI();
    virtual bool            CheckTrie(int*);
    virtual BasicTrieNode*  GetPtr(int i);
    virtual void            SetPtr(int i, BasicTrieNode* j);
    virtual void            SetPtr2MS(MultiSet* ptr);
    MultiSet*               GetPtr2MS();
};

class TrieNode : public BasicTrieNode {
private:
    BasicTrieNode*  ptr[TrieMaxElem];
public:
                    TrieNode();
    int             WhoAmI();
    bool            CheckTrie(int*);
    void            SetPtr(int i, BasicTrieNode* j);
    BasicTrieNode*  GetPtr(int i);
};

class Trie{
private:
    BasicTrieNode *root;
public:
    int useSLL;
    int useWBLT;
    Trie();
    BasicTrieNode*  GetRoot();
    void            SetRoot(BasicTrieNode *node);
    bool            CheckTrie(int*);
    void            Create(char x[]);
    void            Insert(char x[], int number);
    void            Merge(char x[], char y[]);
    SLLNode*        MergeList(SLLNode* list1, SLLNode* list2);
    MultiSet*       GetMultiSet(char x[]);
    int             PrintNum(char x[]);
    int             PrintCount(char x[], int i);
    bool            CheckTrieNodeEmpty(BasicTrieNode* thisOne);
    void            Delete(char x[]);
    BasicTrieNode*  Delete(char x[], int i, BasicTrieNode* current);
    void            DeleteAll(char x[]);
    BasicTrieNode*  DeleteAll(char x[], int i, BasicTrieNode* current);
    void            DeleteGEElem(char x[], int number);
    void            DeleteMin(char x[]);
    void            DeleteGT(char x[]);
    BasicTrieNode*  Collapse(char x[], int i, int lowerbound, BasicTrieNode* current);
    void            Collapse1(int lowerbound, BasicTrieNode* current);
    BasicTrieNode*  Collapse2(BasicTrieNode* current);
    BasicTrieNode*  Collapse3(BasicTrieNode* current);
    int             PrintMax(char x[]);
    int             PrintMin(char x[]);
    int             PrintNumGT(char x[], int* p);
    void            PrintNumGT(char x[], int iterator,int lowerbound ,int* p, BasicTrieNode* current);
    int             CountN(int* pcount, BasicTrieNode *root);
    int             CountNT(int* pcount, BasicTrieNode *root);
    void            DeleteElem( char x[], int number);
    int             FindMax(WBLTNode* node, int* p);
};

#endif /* defined(___30aProject__Trie__) */
