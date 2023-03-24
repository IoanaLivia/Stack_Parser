//
// Created by ioana on 3/19/2023.
//

#ifndef TC_PROIECT_1_4_STACKPARSER_H
#define TC_PROIECT_1_4_STACKPARSER_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include "Transition.h"
using namespace std;

class StackParser {
public:
    StackParser(istream&, istream&);
    void parse(ofstream&);
    vector<string> inputs;
    static const string LAMBDA;
    bool hasFinalStates;
    string initState;
    string initStackSymbol;
    set<string> finalStates;
    vector<string> states;
    vector<Transition*> transitions;
    unordered_map<string, vector<Transition*>> graph;
    set<string> inputAlph;
    set<string> outputAlph;
};
#endif //TC_PROIECT_1_4_STACKPARSER_H
