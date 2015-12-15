//
//  Node.cpp
//  130aProject
//
//  Created by Ray Ouyang on 7/6/15.
//  Copyright (c) 2015 Ray Ouyang. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "Trie.h"
#include "Node.h"



class MultiSet;
class WBLTNode;
class WBLT;
class SLLNode;
class SLL;


MultiSet* MultiSet::GetPtr2PV(){
    return ptr2previousVersion;
}
//*************************************************************************************************************************

void MultiSet::SetPtr2PV(MultiSet* ptr){
    ptr2previousVersion = ptr;
}
//*************************************************************************************************************************

WBLT::WBLT(){
    root=0;
    SetPtr2PV(0);
}

WBLT::~WBLT(){
    MakeEmpty(GetRoot());
    SetRoot(0);
}
void WBLT::MakeEmpty(WBLTNode* top){
    WBLTNode* t = top;
    if(t){
        MakeEmpty(top->GetLeftChild());
        MakeEmpty(top->GetRightChild());
    }
    delete t;
}
//*************************************************************************************************************************

void WBLT::SetRoot(WBLTNode* ptr){
    root=ptr;
}
//*************************************************************************************************************************
WBLTNode::WBLTNode(){
    SetW(1);
    SetRightChild(0);
    SetLeftChild(0);
    SetData(0);

}
//*************************************************************************************************************************

void WBLTNode::SetLeftChild(WBLTNode* node){
    leftchild = node;
}

//*************************************************************************************************************************
void WBLTNode::SetRightChild(WBLTNode* node){
    rightchild = node;
}

//*************************************************************************************************************************

void WBLT::Meld(WBLTNode* theRoot){
    if(GetRoot() == theRoot) return;
    SetRoot(Meld(GetRoot(), theRoot));
}

WBLTNode*   WBLT::Meld(WBLTNode* x, WBLTNode* y){
    if(x == 0) return y;
    if(y == 0) return x;
    if(x->GetData() < y->GetData()){
        return Meld1(x,y);
    }else{
        return Meld1(y,x);
    }
}

WBLTNode* WBLT::Meld1(WBLTNode* x, WBLTNode* y){
    if(x->GetLeftChild() == 0){
        x->SetLeftChild(y);
    }else{
        x->SetRightChild(Meld(x->GetRightChild(), y));
        if(x->GetLeftChild()->GetW() < x->GetRightChild()->GetW()){
            SwapChildren(x);
        }
    }
    if(x->GetRightChild() && x->GetLeftChild()){
        x->SetW(x->GetRightChild()->GetW()+x->GetLeftChild()->GetW()+1);
    }else if(x->GetRightChild()){
        x->SetW(x->GetRightChild()->GetW()+1);
    }else if(x->GetLeftChild()){
        x->SetW(x->GetLeftChild()->GetW()+1);
    }
    return x;
}

void WBLT::SwapChildren(WBLTNode* x){
    WBLTNode* temp = x->GetLeftChild();
    x->SetLeftChild(x->GetRightChild());
    x->SetLeftChild(temp);
}
//*************************************************************************************************************************

void WBLT::Insert(int number){
    WBLTNode* newNode = new WBLTNode;
    newNode->SetData(number);
    Meld(newNode);
    
}
//*************************************************************************************************************************
void WBLT::DeleteMin(){
    WBLTNode* oldRoot = GetRoot();
    SetRoot(Meld(GetRoot()->GetLeftChild(), GetRoot()->GetRightChild()));
    delete oldRoot;
}

void WBLT::DeleteElem(int x){
    if (root != NULL) {
        WBLTNode* current = root;
        if (current->GetData() == x) {
            DeleteMin();
            return;
        }
        current = SearchParent(current, x);
        if (current!= NULL) {
            if (current->GetLeftChild() && current->GetLeftChild()->GetData() == x) {
                WBLTNode* temp = current->GetLeftChild();
                current->SetLeftChild(Meld(current->GetLeftChild()->GetLeftChild(), current->GetLeftChild()->GetRightChild()));
                delete temp;
            }
            else if (current->GetRightChild() && current->GetRightChild()->GetData() == x) {
                WBLTNode* temp = current->GetRightChild();
                current->SetRightChild(Meld(current->GetRightChild()->GetLeftChild(), current->GetRightChild()->GetRightChild()));
                delete temp;
            }
        }
    }
}

WBLTNode* WBLT::SearchParent(WBLTNode* current, int number){
    if(current == 0 || current->GetData() > number)
        return 0;
    if(current->GetLeftChild() && current->GetLeftChild()->GetData() == number){
        current->SetW(current->GetW()-1);
        return current;
    }
    if(current->GetRightChild() && current->GetRightChild()->GetData() == number){
        current->SetW(current->GetW()-1);
        return current;
    }
    WBLTNode* next = SearchParent(current->GetLeftChild(), number);
    if(next != 0){
        current->SetW(current->GetW()-1);
        return next;
    }
    next = SearchParent(current->GetRightChild(), number);
    if(next !=0){
        current->SetW(current->GetW()-1);
        return next;
    }
}


bool WBLT::FindGreaterThenDelete(WBLTNode* theRoot, int number){
    if(theRoot == 0){
        return false;
    }
    if(theRoot->GetData() >= number){
        MakeEmpty(theRoot);
        return true;
    }else{
        if(FindGreaterThenDelete(theRoot->GetLeftChild(), number)){
            theRoot->SetLeftChild(0);
            if(theRoot->GetRightChild() && theRoot->GetLeftChild()){
                theRoot->SetW(theRoot->GetRightChild()->GetW()+theRoot->GetLeftChild()->GetW()+1);
            }else if(theRoot->GetRightChild()){
                theRoot->SetW(theRoot->GetRightChild()->GetW()+1);
            }else if(theRoot->GetLeftChild()){
                theRoot->SetW(theRoot->GetLeftChild()->GetW()+1);
            }
            return true;
        }
        
        if(FindGreaterThenDelete(theRoot->GetRightChild(), number)){
            theRoot->SetRightChild(0);
            if(theRoot->GetRightChild() && theRoot->GetLeftChild()){
                theRoot->SetW(theRoot->GetRightChild()->GetW()+theRoot->GetLeftChild()->GetW()+1);
            }else if(theRoot->GetRightChild()){
                theRoot->SetW(theRoot->GetRightChild()->GetW()+1);
            }else if(theRoot->GetLeftChild()){
                theRoot->SetW(theRoot->GetLeftChild()->GetW()+1);
            }
            return true;
        }
    }
    return false;
    
}



//*************************************************************************************************************************

WBLTNode* WBLT::GetRoot(){
    return root;
}
//*************************************************************************************************************************


bool WBLT::Check(int* pcount)
{bool temp;
    int countl;
    if(GetRoot() == 0) {*pcount=0; return true;}
    temp=root->Check(&countl,1);
    *pcount=countl;
    return temp;
}
//*************************************************************************************************************************

bool WBLTNode::Check(int* pcount, int value)
{int countl, countll;
    bool resp;
    int leftw, rightw;
    countl=0;
    leftw=rightw=0;
    resp=true;
    if(leftchild != 0) {resp=leftchild->Check(&countll,GetData())&&resp;
        leftw=leftchild->GetW();
        if(value > leftchild->GetData() ||
           value > 2000000000) return false;
        countl=countl+countll;
    }
    if(rightchild != 0) {resp=rightchild->Check(&countll,GetData())&&resp;
        rightw=rightchild->GetW();
        if(value > rightchild->GetData() ||
           value > 2000000000) return false;
        countl=countl+countll;
    }
    if(leftw < rightw) resp=false;
    *pcount=countl+1;
    return resp;
}

//*************************************************************************************************************************

void WBLTNode::SetData(int i){
    data = i;
}

//*************************************************************************************************************************

int WBLTNode::GetData(){
    return data;
}
//*************************************************************************************************************************

WBLTNode* WBLTNode::GetLeftChild(){
    return leftchild;
}
//*************************************************************************************************************************

WBLTNode* WBLTNode::GetRightChild(){
    return rightchild;
}
//*************************************************************************************************************************

int WBLTNode::GetW(){
    return w;
}
//*************************************************************************************************************************

int WBLT::WhoAmI(){
    return(4);
}
//*************************************************************************************************************************

void WBLTNode::SetW(int i){
    w = i;
}

//*************************************************************************************************************************

SLLNode::SLLNode(){
    SetNext(0);
    SetData(0);
}

//*************************************************************************************************************************

bool SLLNode::Check(int* pcount, int value)
{ int countl;
    if(GetData() < 1 || GetData() >2000000000 || value > GetData()) return false;
    if(GetNext() == 0) {*pcount=1; return true;}
    if(!GetNext()->Check(&countl,GetData())) return false;
    *pcount=countl+1;
    return true;
}
//*************************************************************************************************************************

void SLLNode::SetData(int NewData){
    data = NewData;
}
//*************************************************************************************************************************

void SLLNode::SetNext(SLLNode* NewNode){
    next= NewNode;
}
//*************************************************************************************************************************

int SLLNode::GetData(){
    return data;
}

//*************************************************************************************************************************

SLLNode* SLLNode::GetNext(){
    return next;
}
//*************************************************************************************************************************

//*************************************************************************************************************************

bool SLL::Check(int* pcount)
{int countl;
    *pcount=0;
    if(GetFirst()== 0) return true;
    if(!GetFirst()->Check(&countl,1)) return false;
    *pcount = countl;
    return true;
}
//*************************************************************************************************************************

SLL::SLL(){
    first=0;
    SetPtr2PV(0);
}
//*************************************************************************************************************************

int SLL::WhoAmI(){
    return 3;
}
//*************************************************************************************************************************

SLLNode* SLL::GetFirst(){
    return first;
}
//*************************************************************************************************************************

void SLL::SetFirst(SLLNode* ptr){
    first=ptr;
}
//*************************************************************************************************************************

void SLL::Insert(int number){
    SLLNode* head = GetFirst();
    SLLNode* newNode = new SLLNode();
    SLLNode* current;
    newNode->SetData(number);
    if(head == 0 || head->GetData() >= newNode->GetData()){
        newNode->SetNext(head);
        SetFirst(newNode);
    }
    else
    {
        current = head;
        while(current->GetNext() != 0 &&
              current->GetNext()->GetData() < newNode->GetData())
        {
            current = current->GetNext();
        }
        newNode->SetNext(current->GetNext());
        current->SetNext(newNode);
    }
}
//*************************************************************************************************************************
int SLL::GetLength(){
    SLLNode* current = GetFirst();
    if(current == 0){
        return 0;
    }
    int count(1);
    while(current->GetNext()){
        count++;
        current = current->GetNext();
    }
    return count;
    
}

MultiSet* SLL::ConvertMeWBLT(SLL* sll){
    SLLNode* current = sll->GetFirst();
    MultiSet* newWBLT = new WBLT();
    while(current){
        newWBLT->Insert(current->GetData());
        current = current->GetNext();
    }
    delete sll;
}

MultiSet* WBLT::ConvertMeSLL(MultiSet* wblt){
    MultiSet* newSLL = new SLL();
    while(wblt->GetRoot()){
        newSLL->Insert(wblt->GetRoot()->GetData());
        wblt->DeleteMin();
    }
    return newSLL;
}
//*************************************************************************************************************************
SLL::~SLL(){
    SLLNode* current = GetFirst();
    while(current){
        SLLNode* temp = current;
        current = current->GetNext();
        delete temp;
    }
}

