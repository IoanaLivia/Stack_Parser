#ifndef TC_PROIECT_1_4_TRANSITION_H
#define TC_PROIECT_1_4_TRANSITION_H

#include <iostream>

using namespace std;

class Transition {
public:
    Transition(string startState, string endState, string input, string stack, string output);
    string startState;
    string endState;
    string input;
    string output;
    string stackRemove;
    string stackAdd;

    friend ostream &operator <<(ostream &out,  const Transition& t){
        out << "Transition: "<<t.startState<<" "<<t.input<<" "<<t.stackRemove<<"|"<<t.stackAdd<<" "<<t.output<<" "<<t.endState;
        return out;
    }

    friend bool operator<(Transition x, Transition y) {
        return x.startState < y.startState;
    }
};


#endif //TC_PROIECT_1_4_TRANSITION_H
