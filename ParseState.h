#ifndef TC_PROIECT_1_4_PARSESTATE_H
#define TC_PROIECT_1_4_PARSESTATE_H

using namespace std;

#include <stack>
#include <iostream>
#include "Transition.h"
#include <vector>

class ParseState {
public:
    ParseState(const string currState, stack<string> s, string currInput, string currOutput, vector<Transition> path);
    string currState;
    string currInput;
    string currOutput;
    stack<string> s;
    vector<Transition> path;

    friend ostream &operator <<(ostream &out, ParseState& p){
        out << "Current State: "<<p.currState<<" Current Input: "<<p.currInput<<" Current Output: "<<p.currOutput<<" Stack: ";
        stack<string> aux = p.s;
        while (!((p.s).empty())) {
            out<<(p.s).top()<<" ";
            (p.s).pop();
        }
        p.s = aux;
        return out;
    }
};


#endif //TC_PROIECT_1_4_PARSESTATE_H
