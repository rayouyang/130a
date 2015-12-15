//
//  Trie.cpp
//  130aProject
//
//  Created by Ray Ouyang on 7/5/15.
//  Copyright (c) 2015 Ray Ouyang. All rights reserved.
//
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Trie.h"
#include "Node.h"
//*************************************************************************************************************************

BasicTrieNode::BasicTrieNode(){
    ptr2ms = 0;
}
//*************************************************************************************************************************


int BasicTrieNode::WhoAmI(){
    return(1);
}
//*************************************************************************************************************************

bool BasicTrieNode::CheckTrie(int* pcount){
    if(ptr2ms == 0) {return false;}
    (*pcount)++;
    return true;
}
//*************************************************************************************************************************

BasicTrieNode* BasicTrieNode::GetPtr(int i)
{}
//*************************************************************************************************************************

void BasicTrieNode::SetPtr(int i, BasicTrieNode* j)
{}
//*************************************************************************************************************************

void BasicTrieNode::SetPtr2MS(MultiSet *ptr){
    ptr2ms = ptr;
}
//*************************************************************************************************************************

MultiSet* BasicTrieNode::GetPtr2MS(){
    return ptr2ms;
}
//*************************************************************************************************************************

TrieNode::TrieNode(){
    BasicTrieNode();
    for (int i = 0; i < TrieMaxElem; i++)
        SetPtr(i,0);
}
//*************************************************************************************************************************

int TrieNode::WhoAmI(){
    return(2);
}
//*************************************************************************************************************************

bool TrieNode::CheckTrie(int* pcount)
{ // USE THIS PROCEDURE DIRECTLY IN YOUR CODE
    // IF YOU HAVE DIFFERENT CLASS NAMES, FUNCTIONS OR VALUES
    // YOU NEED TO CHANGE THEM HERE TOO.
    int            i,countl;
    countl= *pcount;
    for(i=0; i<TrieMaxElem; i++)
    {if(GetPtr(i)!=0)
        if(!GetPtr(i)->CheckTrie(pcount)) {return false;}
    }
    if(countl == *pcount) return false;
    if (GetPtr2MS() != 0) (*pcount)++;
    return true;
}
//*************************************************************************************************************************

void TrieNode::SetPtr(int i, BasicTrieNode* j){
    this->ptr[i]= j;
}
//*************************************************************************************************************************

BasicTrieNode* TrieNode::GetPtr(int i){
    return this->ptr[i];
}
//*************************************************************************************************************************

BasicTrieNode* Trie::GetRoot(){
    return root;
}
//*************************************************************************************************************************

void Trie::SetRoot(BasicTrieNode* node){
    root = node;
}
//*************************************************************************************************************************

Trie::Trie(){
    root = new TrieNode;
}
//*************************************************************************************************************************

bool Trie::CheckTrie(int* count)
{ // USE THIS PROCEDURE DIRECTLY IN YOUR CODE
    // IF YOU HAVE DIFFERENT CLASS NAMES, FUNCTIONS OR VALUES
    // YOU NEED TO CHANGE THEM HERE TOO.
    int countl;
    countl=0;
    bool result;
    result = root->CheckTrie(&countl);
    *count=countl;
    return result;
}
//*************************************************************************************************************************

void Trie::Create(char x[]){
    if(root == nullptr){
        SetRoot(new TrieNode());
    }
    BasicTrieNode* current = GetRoot();
    int j = 0;
    for(int i = 0; x[i] != '\0'; i++){
        j = x[i]-'a';
        if(current->GetPtr(j) == 0){
            if(x[i+1] == '\0'){
                current->SetPtr(j, new BasicTrieNode());
            }else{
                current->SetPtr(j, new TrieNode());
            }
        }else if (current->GetPtr(j)->WhoAmI() == 1 && x[i+1] != '\0'){
            //CASE: next is BasicTrieNode && not at end of string
            //TODO: perform a swap between BasicTrieNode and TrieNode
            BasicTrieNode* replacement = new TrieNode();
            replacement->SetPtr2MS(current->GetPtr(j)->GetPtr2MS());
            BasicTrieNode* ToBeDeleted = current->GetPtr(j);
            current->SetPtr(j, replacement);
            delete ToBeDeleted;
        }
        current = current->GetPtr(j);
    }
    if(useSLL == 0){
        WBLT* NewMultiSet = new WBLT();
        NewMultiSet->SetPtr2PV(current->GetPtr2MS());
        current->SetPtr2MS(NewMultiSet);
    }else{
        SLL* NewMultiSet = new SLL();
        if(current && current->GetPtr2MS())// need to adjust for when we implement WBLT
            NewMultiSet->SetPtr2PV(current->GetPtr2MS());
        current->SetPtr2MS(NewMultiSet);
    }
}
//*************************************************************************************************************************

void Trie::Insert(char x[], int number){
    MultiSet* k = GetMultiSet(x);
    if(k && k->WhoAmI() == 1){
            if(k->GetLength() == useWBLT){
                k = k->ConvertMeWBLT(k);
                int j(0);
                BasicTrieNode* current = GetRoot();
                for(int i= 0; x[i] != '\0'; i++){
                    j = x[i] - 'a';
                    current = current->GetPtr(j);
                }
                return current->SetPtr2MS(k);
            }
        k->Insert(number);

    }else{
        k->Insert(number);
    }
}
//*************************************************************************************************************************

MultiSet* Trie::GetMultiSet(char x[]){
    if(GetRoot() == 0)
        return 0;
    int j(0);
    BasicTrieNode* current = GetRoot();
    for(int i= 0; x[i] != '\0'; i++){
        j = x[i] - 'a';
        if(current->GetPtr(j) == 0)
            return 0;
        current = current->GetPtr(j);
    }
    return current->GetPtr2MS();
}
//*************************************************************************************************************************

void Trie::Merge(char x[], char y[]){
    /* If at least one of the multisets < s > or < t > is not defined, or if < s >=< t >, then operation
     will be a no-op. Otherwise, the current version of multiset < s > will get all the elements in the
     current version of multiset < t > in addition to keeping all is elements. The current multiset < t >
     will remain defined, but it will become an empty multiset. Do NOT implement this operation as
     a series of DeleteMins and Inserts.*/
    MultiSet* x1 = GetMultiSet(x);
    MultiSet* y1 = GetMultiSet(y);
    if(x1 && y1) {
        if(x1->WhoAmI() == y1->WhoAmI()){
            if(x1->WhoAmI() == 3){
                x1->SetFirst(MergeList( x1->GetFirst(), y1->GetFirst()));
                y1->SetFirst(0);
            }else{
                x1->SetRoot(x1->Meld(x1->GetRoot(), y1->GetRoot()));
                y1->SetRoot(0);
            }
        }
    }
        
}
//*************************************************************************************************************************

SLLNode* Trie::MergeList(SLLNode* list1, SLLNode* list2){
    if(list1 == 0) return list2;
    if(list2 == 0) return list1;
    
    if(list1->GetData() < list2->GetData()){
        list1->SetNext(MergeList(list1->GetNext(), list2));
        return list1;
    }else{
        list2->SetNext(MergeList(list1, list2->GetNext()));
        return list2;
    }
}
//*************************************************************************************************************************

int Trie::PrintNum(char x[]){

    MultiSet* k = GetMultiSet(x);
    if(k == 0){
        return -1;
    }
    int count = 0;
    if(k && k->WhoAmI() == 3){
        SLLNode* current = k->GetFirst();
        while(current){
            count++;
            current = current->GetNext();
        }
    }
    if(k && k->WhoAmI() == 4){
        if(k->GetRoot()){
        count = k->GetRoot()->GetW();
        }
    }
    return count;
}
//*************************************************************************************************************************

int Trie::PrintCount(char x[], int i){
    MultiSet* k = GetMultiSet(x);
    if(k == 0){
        return -1;
    }
    int count = 0;
    if(k->WhoAmI() == 3){
        SLLNode* current = k->GetFirst();
        while(current){
            if(current->GetData() == i){
                count++;
            }
            current = current->GetNext();
        }
    }
    return count;
}
//*************************************************************************************************************************
bool Trie::CheckTrieNodeEmpty(BasicTrieNode* thisOne){
    for(int i = 0; i < TrieMaxElem; i++){
        if(thisOne->GetPtr(i)){
            return false;
        }
    }
    return true;
}
//*************************************************************************************************************************

/*Delete < s >
If multiset < s > is not defined, then it will be a no-op. Otherwise delete the current version
of multiset < s >. I.e., delete all its elements. If this was the only version of multiset < s >
then delete the name of the multiset from the current multisets available and multiset < s >
will become undefined. On the other hand, if there is another version of multiset < s > then
the multiset < s > that was created last and has not yet been deleted will become the current
multiset < s > from now on and multiset < s > continues to be defined. Do NOT implement this
as series of DeleteMins.*/
void Trie::Delete(char x[]){
    BasicTrieNode* current = GetRoot();
    int i = 0;
    if(x[i] == '\0') return;
    Delete(x, i, current);
    
}

//*************************************************************************************************************************
/*bool Trie::Delete(char x[], int i, BasicTrieNode* current){
    if(current != 0){
        if(x[i] == '\0'){
            MultiSet* k = current->GetPtr2MS();
            if(k && k->GetPtr2PV()){
                current->SetPtr2MS(k->GetPtr2PV());
                delete k;
                return false;
                
            }
            if(current->WhoAmI() == 1 || CheckTrieNodeEmpty(current)){
                delete current;
                return true;
            }else{
                delete k;
                current->SetPtr2MS(0);
                return false;
            }
        }else{
            if(Delete(x, i+1, current->GetPtr(x[i]-'a'))){
                current->SetPtr(x[i]-'a', 0);
                if(CheckTrieNodeEmpty(current) && current->GetPtr2MS()){
                    return false;
                }
                if(i != 0 && CheckTrieNodeEmpty(current)){
                    delete current;
                    return true;
                }
            }else{
                if(current->GetPtr(x[i]-'a') && CheckTrieNodeEmpty(current->GetPtr(x[i]-'a')) && current->GetPtr(x[i]-'a')->GetPtr2MS()){
                    BasicTrieNode* replacement = new BasicTrieNode;
                    replacement->SetPtr2MS(current->GetPtr(x[i]-'a')->GetPtr2MS());
                    delete current->GetPtr(x[i]-'a');
                    current->SetPtr(x[i]-'a', replacement);
                }
            }
        }
    }
    return false;
}*/
//*************************************************************************************************************************

/*DeleteAll < s >
If multiset < s > is not defined, then it will be a no-op. Otherwise delete all the versions of
multiset < s >. I.e., delete all the elements in all the multisets named < s >. Multiset < s > will
become undefined after this operation. Do NOT implement this as sequence of Delete < s > or
DeleteMins.*/

void Trie::DeleteAll(char x[]){
    BasicTrieNode* current = GetRoot();
    int i = 0;
    if(x[i] == '\0') return;
    DeleteAll(x, i, current);
    
}


//*************************************************************************************************************************
// revision of delete Trie
BasicTrieNode* Trie::Delete(char x[],int i,BasicTrieNode* current){
    if(current == 0){return 0;}
    if(x[i] == '\0'){
        MultiSet* k = current->GetPtr2MS();
        if(current->GetPtr2MS() && current->GetPtr2MS()->GetPtr2PV()){
            current->SetPtr2MS(current->GetPtr2MS()->GetPtr2PV());
            delete k;
            return current;
        }else{
            delete k;
            current->SetPtr2MS(0);
            if(current->WhoAmI() == 1 || CheckTrieNodeEmpty(current)){
                delete current;
                return 0;
            }
            return current;
        }
    }else{
        if(current->WhoAmI() == 1){
            return current;
        }
        current->SetPtr( x[i]-'a', Delete(x, i+1, current->GetPtr(x[i]-'a')));
        if(i != 0 && CheckTrieNodeEmpty(current) && current->GetPtr2MS()){
            BasicTrieNode* newNode = new BasicTrieNode;
            newNode->SetPtr2MS(current->GetPtr2MS());
            return newNode;
        }else if(i != 0 && CheckTrieNodeEmpty(current)){
            delete current;
            return 0;
        }
        return current;
    }
}

BasicTrieNode* Trie::DeleteAll(char x[], int i, BasicTrieNode* current){
    if(current == 0){return 0;}
    if(x[i] == '\0'){
        MultiSet* k = current->GetPtr2MS();
        while(k){
            delete current->GetPtr2MS();
            current->SetPtr2MS(k->GetPtr2PV());
            k = current->GetPtr2MS();
        }
        if(current->WhoAmI() == 1 || CheckTrieNodeEmpty(current)){
            delete current;
            return 0;
        }
        current->SetPtr2MS(0);
        return current;
    }else{
        if(current->WhoAmI() == 1){
            return current;
        }
        current->SetPtr( x[i]-'a', DeleteAll(x, i+1, current->GetPtr(x[i]-'a')));
        if(i != 0 && CheckTrieNodeEmpty(current) && current->GetPtr2MS()){
            BasicTrieNode* newNode = new BasicTrieNode;
            newNode->SetPtr2MS(current->GetPtr2MS());
            return newNode;
        }else if(i != 0 && CheckTrieNodeEmpty(current)){
            delete current;
            return 0;
        }
        return current;
    }
}


//*************************************************************************************************************************

/*DeleteElem < s > < x >
If multiset < s > is not defined or if element < x > is not in the current version of multiset < s >,
2
then it will be a no-op. Otherwise delete element < x > from the current version of multiset
< s >. I.e., note that you will delete one instance of element < x > from the current version of
multiset < s >.*/

void Trie::DeleteElem( char x[], int number){
    MultiSet* k = GetMultiSet(x);
    if(k && k->WhoAmI() == 3){
        SLLNode* current = k->GetFirst();
        if(current){
            if(current->GetData() == number){
                k->SetFirst(current->GetNext());
                delete current;
            }
            while (current->GetNext()) {
                if(current->GetNext()->GetData() != number){
                    current = current->GetNext();
                }else{
                    SLLNode* deleted = current->GetNext();
                    current->SetNext(current->GetNext()->GetNext());
                    delete deleted;
                    return;
                }
            }
            
        }
    }else{
        if(k->WhoAmI() == 4){
            k->DeleteElem(number);
            return;
        }
    }
}


//*************************************************************************************************************************
/*DeleteGEElem < s > < x >
If multiset < s > is not defined, then it will be a no-op. Otherwise delete all occurrences of
elements whose value is greater or equal to < x > from the current version of multiset < s >.*/
void Trie::DeleteGEElem(char x[], int number){
    MultiSet* k = GetMultiSet(x);
    if(k && k->WhoAmI() == 3){
        SLLNode* current = k->GetFirst();
        if(current){
            if(current->GetData() > number){
                while(k->GetFirst()){
                k->SetFirst(current->GetNext());
                delete current;
                }
                return;
            }
            while (current->GetNext() &&
                   current->GetNext()->GetData() > number) {
                current = current->GetNext();
            }
            while(current->GetNext()){
                SLLNode* deleted = current->GetNext();
                current->SetNext(current->GetNext()->GetNext());
                delete deleted;
            }
            return;
        }
    }
    if(k && k->WhoAmI() == 4){
        if(k->FindGreaterThenDelete(k->GetRoot(), number)){
            if(k->GetRoot()){
                if(k->GetRoot()->GetRightChild() && k->GetRoot()->GetLeftChild()){
                    k->GetRoot()->SetW(k->GetRoot()->GetRightChild()->GetW()+k->GetRoot()->GetLeftChild()->GetW()+1);
                }else if(k->GetRoot()->GetRightChild()){
                    k->GetRoot()->SetW(k->GetRoot()->GetRightChild()->GetW()+1);
                }else if(k->GetRoot()->GetLeftChild()){
                    k->GetRoot()->SetW(k->GetRoot()->GetLeftChild()->GetW()+1);
                }
            }else{
                k->SetRoot(0);
            }
        }
        
    }

}


//*************************************************************************************************************************
/*DeleteMin < s >
If the multiset < s > is not defined or it is defined and empty, then it will be a no-op. Otherwise
delete one occurrence of the smallest element from the current multiset < s >. The multiset will
continue to be defined, even if it becomes empty.*/

void Trie::DeleteMin(char x[]){
    MultiSet* k = GetMultiSet(x);
    if(k && k->WhoAmI() == 3){
        SLLNode* current = k->GetFirst();
        if(current){
            k->SetFirst(current->GetNext());
            delete current;
            return;
        }
    }
    if(k && k->WhoAmI() == 4){
        k->DeleteMin();
    }
}


//*************************************************************************************************************************
/*PrintMax < s >
 If the multiset < s > is not defined or it is defined and the current multiset < s > is empty, then
 it will be a no-op and nothing will be printed. Otherwise, the operation will print the largest
 element in the current multiset < s > and the contents of the current multiset < s > will not
 change.*/
int Trie::PrintMax(char x[]){
    MultiSet* k = GetMultiSet(x);
    if(k && k->WhoAmI() == 3){
        SLLNode* current = k->GetFirst();
        if(current){
        while(current->GetNext()){
            current = current->GetNext();
        }
        return current->GetData();
        }
    }else{
        if(k->WhoAmI() == 4){
            int max = -1;
            
            FindMax(k->GetRoot(), &max);
            return max;
        }
    }
    return -1;
}

int Trie::FindMax(WBLTNode* node, int* p){
    if (node == 0) {
        return 0;
    }
    FindMax(node->GetLeftChild(), p);
    FindMax(node->GetRightChild(), p);
    if( (*p) < node->GetData())
        (*p) = node->GetData();
}


//*************************************************************************************************************************
/*PrintMin < s >
 If the multiset < s > is not defined or it is defined and the current multiset < s > is empty, then
 it will be a no-op and nothing will be printed. Otherwise, the operation will print the smallest
 element in the current multiset < s > and the contents of the current multiset < s > will not
 change. Do NOT implement this as a sequence of DeleteMins and Inserts.*/
int Trie::PrintMin(char x[]){
    MultiSet* k = GetMultiSet(x);
    if(k && k->WhoAmI() == 3){
        if(k->GetFirst()){
            return k->GetFirst()->GetData();
        }else{
            return -1;
        }
    }
    if(k && k->WhoAmI() == 4){
        if(k->GetRoot()){
        return k->GetRoot()->GetData();
        }else{
            return -1;
        }
    }
}

//*************************************************************************************************************************

/*CountN
Count and print the number of multisets currently defined. If there are none defined, then print
0.*/

int Trie::CountN(int * pcount, BasicTrieNode* root){
    if(root == 0){
        return 0;
    }
    if(root->WhoAmI() ==1){
        (*pcount)++;
        return 0;
    }
    
    if(root->GetPtr2MS()) (*pcount)++;
    for(int i = 0; i < TrieMaxElem; i++){
        if(root->GetPtr(i)){
            CountN(pcount, root->GetPtr(i));
        }
    }
    return 0;
}
//************************************************************************************************************************

int Trie::CountNT(int * pcount, BasicTrieNode* root){
    if(root == 0) return 0;
    if(root->WhoAmI() ==1)
    {
        MultiSet* current = root->GetPtr2MS();
        while(current)
        {
            (*pcount)++;
            current = current->GetPtr2PV();
        }
    return 0;
    }
    
    if(root->GetPtr2MS()){
        MultiSet* current = root->GetPtr2MS();
        while(current){
            (*pcount)++;
            current = current->GetPtr2PV();
        }
    }
    for(int i = 0; i < TrieMaxElem; i++)
    {
        if(root->GetPtr(i)){
            CountNT(pcount, root->GetPtr(i));
        }
    }
    return 0;
}

//*************************************************************************************************************************
/*PrintNumGT < s >
 Print the total number of multisets with names (in alphabetical order) after name < s >. Include
 in the count all the versions of all the multisets. Note that multiset < s > will not be
 included in the count. Note that < s > may or may not be defined multisets. If there are no
 names in this set, then print 0.*/
int Trie::PrintNumGT(char x[], int* p){
    BasicTrieNode* current = GetRoot();
    int iterator = 0;
    if(x[iterator] == '\0'){// run the countNT function
        CountNT(p, current);
    }
    PrintNumGT(x,iterator, x[iterator]-'a',p, GetRoot());
    return 0;

}

//*************************************************************************************************************************
void Trie::PrintNumGT(char x[], int iterator,int lowerbound ,int* p, BasicTrieNode* current){
    if(current == 0){
        return;
    }
    if(current->GetPtr2MS()){
        MultiSet* current2 = current->GetPtr2MS();
        while(current2){
            (*p)++;
            current2 = current2->GetPtr2PV();
        }
    }
    for(int j = lowerbound; j < TrieMaxElem; j++){
        if(current->GetPtr(j)) {
            if(x[iterator+1] != '\0'){
                PrintNumGT(x, iterator+1, x[iterator+1]-'a', p, current->GetPtr(j));
            }else{
                CountNT(p,current->GetPtr(j));
            }
        }
    }
}

//*************************************************************************************************************************
/*DeleteGT < s >
Delete all the CURRENT multisets with names (in alphabetical order) after name < s >. Note
3
that < s > will not be deleted. Note that < s > may or may not be a multiset that is defined. DO
NOT implement the operation as a sequence of Delete operations. The implementation should be
an “integrated” operation.
 Defining the problem:
    Example: delete cat means everything from d* is deleted, everthing cb* is deleted everything cau* is deleted and everything cat* is deleted. IF cat is the only element in the TrieNode, therefore all previous nodes pointing to cat should also be deleted, this would involve recursively calling to cat so we can free all previous nodes.
 
 */
void Trie::DeleteGT(char x[]){
    BasicTrieNode* current = GetRoot();
    if(current == 0){
        return;
    }
    int i = 0;
    if(x[i] == '\0') return;
    Collapse(x, i, x[i]-'a'+1, current);
    std::cout << current->WhoAmI() << std::endl;
}

//*************************************************************************************************************************
BasicTrieNode* Trie::Collapse(char x[], int i, int lowerbound, BasicTrieNode* current){
    if(current == 0){return 0;}
    if(x[i+1] == '\0'){
        Collapse1(lowerbound, current); // to delete for all words ***(*-z)
        current->SetPtr(x[i]-'a', Collapse3(current->GetPtr(x[i]-'a')));
        if(i != 0 && CheckTrieNodeEmpty(current)){
            if(current->GetPtr2MS()){
                BasicTrieNode* newNode = new BasicTrieNode;
                newNode->SetPtr2MS(current->GetPtr2MS());
                delete current;
                return newNode;
            }
        }
    }else{
        Collapse(x, i+1, x[i+1]-'a'+1, current->GetPtr(x[i]-'a'));
        Collapse1(lowerbound, current);

        if(i != 0 && CheckTrieNodeEmpty(current)){
            if(current->GetPtr2MS()){
                BasicTrieNode* newNode = new BasicTrieNode;
                newNode->SetPtr2MS(current->GetPtr2MS());
                delete current;
                return newNode;
            }
        }
    }
    return current;
}

void Trie::Collapse1( int lowerbound, BasicTrieNode* current){
    for(int j = lowerbound; j < TrieMaxElem; j++){ // delete recursively to the right of lowerbound
        current->SetPtr(j ,Collapse2(current->GetPtr(j)));
    }
    return;
}

BasicTrieNode* Trie::Collapse2(BasicTrieNode* current){
    if(current == 0){
        return 0;
    }
    if(current->WhoAmI() == 2){
        for(int j = 0; j < TrieMaxElem; j++){
            current->SetPtr(j ,Collapse2(current->GetPtr(j)));
        }
    }
    MultiSet* temp = current->GetPtr2MS();
    if(temp){
        if(temp->GetPtr2PV()){
            current->SetPtr2MS(temp->GetPtr2PV());
            delete temp;
            return current;
        }else{
            if(CheckTrieNodeEmpty(current) || current->WhoAmI() == 1){
            delete temp;
            delete current;
            return 0;
            }
        }
    }
return current;
}

BasicTrieNode* Trie::Collapse3(BasicTrieNode* current){
    if(current == 0){
        return 0;
    }
    if(current->GetPtr2MS()){
        BasicTrieNode* newNode =new BasicTrieNode;
        newNode->SetPtr2MS(current->GetPtr2MS());
        BasicTrieNode* aNode = Collapse2(current);
        if(aNode){
            delete newNode;
            return aNode;
        }else{
            return newNode;
        }
    }
    return Collapse2(current);
}

//************************************************************************************************************************
