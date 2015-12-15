//
//  main.cpp
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

using namespace std;
int main(void) {
    string oper,s,t;
    int x;
    // ...
    Trie Mango;
    cin >> Mango.useSLL >> Mango.useWBLT;
    while(1 == 1)
    { cin >> oper;
        
        
        if (oper == "Quit") {// delete everything then end program
            break;
        }
        
        else if (oper == "Insert")
        { cin >> s >> x;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            Mango.Insert(cstr, x);
        }
        else if (oper == "Delete")
        { cin >> s;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            Mango.Delete(cstr);
        }
        else if (oper == "DeleteGT")
        { cin >> s;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            Mango.DeleteGT(cstr);
        }
        else if (oper == "DeleteAll")
        { cin >> s;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            Mango.DeleteAll(cstr);
        }
        else if (oper == "DeleteElem")
        { cin >> s >> x;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            Mango.DeleteElem(cstr, x);
        }
        else if (oper == "DeleteGEElem")
        { cin >> s >> x;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            Mango.DeleteGEElem(cstr, x);
        }
        else if (oper == "DeleteMin")
        { cin >> s;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            Mango.DeleteMin(cstr);
        }
        else if (oper == "PrintMax")
        { cin >> s;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            int m = Mango.PrintMax(cstr);
            if(m != -1)
                cout << m << endl;
        }
        else if (oper == "PrintMin")
        { cin >> s;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            int m = Mango.PrintMin(cstr);
            if(m != -1)
                cout << m << endl;
        }
        
        else if(oper == "Create"){
            cin >> s;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            Mango.Create(cstr);
        }
        
        else if (oper == "Check")
        {cin >> s;
            int count(0);
            int count1(0);
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            MultiSet* k = Mango.GetMultiSet(cstr);
            if(k){
                bool j = k->Check(&count);
                if(j){
                    cout << "True "<< count;
                }else{
                    cout << "False "<< count;

                }
                if(k->WhoAmI() == 3){
                    count1 = 1;
                }else{
                    count1 = 2;
                }
                cout << " " << count1 << endl;
            }
        }
        else if (oper == "CountN")
        {
            int count = 0;
            Mango.CountN(&count, Mango.GetRoot());
            cout << count << endl;
        }
        else if (oper == "CountNT")
        {
            int count = 0;
            Mango.CountNT(&count, Mango.GetRoot());
            cout << count << endl;
        }
        else if (oper == "CountNT")
        {
            int count = 0;
            Mango.CountNT(&count, Mango.GetRoot());
            cout << count << endl;
        }
        else if (oper == "PrintNumGT")
        {
            cin >> s;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            int count = 0;
            Mango.PrintNumGT(cstr, &count);
            cout << count << endl;
        }
        else if (oper == "CheckTrie")
        {
            int count = 0;
            Mango.CheckTrie(&count);
            if(count != 0){
                cout << "True " << count << endl;
            }else{
                cout << "False " << count << endl;
            }
        }
        
        
        else if (oper == "Merge")
        { cin >> s >> t;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            char cstr1[t.size()+1];
            strcpy(cstr1, t.c_str());
            Mango.Merge(cstr,cstr1);
        }
        
        else if (oper == "PrintNum")
        {   cin >> s;
            int count;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            count = Mango.PrintNum(cstr);
            if(count != -1){
            cout << count  << endl;
            }
        }
        else if (oper == "PrintCount")
        {   cin >> s >> x;
            int count;
            char cstr[s.size()+1];
            strcpy(cstr, s.c_str());
            count = Mango.PrintCount(cstr, x);
            if(count != -1){
                cout << count  << endl;
            }
        }
        
        
        // ..
    }
}
