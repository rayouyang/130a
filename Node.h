//
//  Node.h
//  130aProject
//
//  Created by Ray Ouyang on 7/6/15.
//  Copyright (c) 2015 Ray Ouyang. All rights reserved.
//

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "Trie.h"
class SLLNode;
class WBLTNode;
class WBLT;
class SLL;

class MultiSet{
private:
    MultiSet*       ptr2previousVersion;
public:
    virtual           ~MultiSet(){};
    virtual int       WhoAmI()
    {}; //Leave these virtual functions defined as {}
    //for this base class.
    virtual SLLNode*  GetFirst()
    {}; //For technical reasons it needs to be defined this way.
    virtual void      SetFirst(SLLNode* ptr)
    {}; //For technical reasons it needs to be defined this way.
    virtual void      SetRoot(WBLTNode* ptr)
    {};
    virtual WBLTNode* GetRoot()
    {};
    MultiSet*         GetPtr2PV();
    void              SetPtr2PV(MultiSet* ptr);
    virtual bool      Check(int*)
    {};
    virtual void      Insert(int number)
    {};
    virtual void      DeleteMin()
    {};
    virtual void      DeleteElem(int number)
    {};
    virtual bool      FindGreaterThenDelete(WBLTNode* theRoot, int number)
    {};
    virtual WBLTNode* Meld(WBLTNode* x, WBLTNode* y)
    {};
    virtual int       GetLength()
    {};
    virtual MultiSet*     ConvertMeWBLT(MultiSet* sll)
    {};
    virtual MultiSet*     ConvertMeSLL(MultiSet* wblt)
    {};
    
};

class WBLT: public MultiSet{
private:
    WBLTNode* root;
public:
    int         WhoAmI();
    WBLT();
    ~WBLT();
    void        MakeEmpty(WBLTNode* top);
    void        SetRoot(WBLTNode* ptr);
    WBLTNode*   GetRoot();
    bool        Check(int*);
    void        Insert(int number);
    void        Meld(WBLTNode* theRoot);
    WBLTNode*   Meld(WBLTNode* x, WBLTNode* y);
    WBLTNode*   Meld1(WBLTNode* x, WBLTNode* y);
    void        SwapChildren(WBLTNode* x);
    void        DeleteMin();
    void        DeleteElem(int number);
    bool        FindGreaterThenDelete(WBLTNode* theRoot, int number);
    WBLTNode*   SearchParent(WBLTNode* current, int number);
    MultiSet*   ConvertMeSLL(MultiSet* wblt);
};

class WBLTNode {
private:
    int data;
    int w;   // This is the s value in the slides.
    WBLTNode*    leftchild;
    WBLTNode*    rightchild;
public:
    WBLTNode();
    bool        Check(int*,int);
    int         GetData();
    void        SetData(int i);
    WBLTNode    * GetLeftChild();
    WBLTNode    * GetRightChild();
    void        SetLeftChild(WBLTNode* node);
    void        SetRightChild(WBLTNode* node);
    int         GetW();
    void        SetW(int i);
};
class SLL: public MultiSet{
private:
    SLLNode*     first;
public:
    SLL();
    ~SLL();
    int          WhoAmI();
    SLLNode*     GetFirst();
    void         SetFirst(SLLNode* ptr);
    bool         Check(int*);
    void         Insert(int number);
    int          GetLength();
    MultiSet*    ConvertMeWBLT(SLL* sll);
};

class SLLNode {
private:
    int     data;
    SLLNode *next;
public:
    SLLNode();
    bool        Check(int*,int);
    void        SetData(int NewData);
    void        SetNext(SLLNode* NewNode);
    int         GetData();
    SLLNode*    GetNext();
};



#endif /* defined(___30aProject__Node__) */
