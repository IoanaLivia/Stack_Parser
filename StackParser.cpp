#include "StackParser.h"
#include "Transition.h"
#include "auxiliary.h"
#include "ParseState.h"
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

StackParser::StackParser(istream &in, istream &fin, ofstream &fout) {
    string line;
    vector<string> splitLine = {};

    while(getline(fin, line))
    {
        inputs.push_back(line);
    }

    getline(in, line);
    this->states = splitString(line, " ");

    getline(in, this->initState);
    getline(in, line);
    line == "1" ? this->hasFinalStates = true : this->hasFinalStates = false;

    if (this->hasFinalStates) {
        (getline(in, line));
        splitLine = splitString(line, " ");
        for (string &s: splitLine) {
            this->finalStates.insert(s);
        }
        splitLine.clear();
    }


    getline(in, this->initStackSymbol);

    while(getline(in, line)) {
        // in case of empty lines
        if (line.size() == 0) break;
        splitLine = splitString(line, " ");
        Transition* t = new Transition(splitLine[0], splitLine[4], splitLine[1], splitLine[2], splitLine[3]);
        this->transitions.push_back(t);
        //cout<<*t<<endl;
        splitLine.clear();;
    }

    for (int i = 0; i < (int)states.size(); ++i) {
        graph[states[i]] = {};
    }

    for (int i = 0; i < (int)transitions.size(); ++i) {
        graph[transitions[i]->startState].push_back(transitions[i]);
    }
}

void StackParser::parse() {
    queue<ParseState> q;
    stack<string> s;
    string output = "";
    s.push(initStackSymbol);
    ParseState y = ParseState(initState, s, inputs[0], output, {});
    q.push(y);

    while (!q.empty()) {
        ParseState now = q.front();
        q.pop();

        for (const Transition *t: graph[now.currState]) {
            string pInitState = t->endState, pInput = now.currInput, pOutput = now.currOutput;
            vector<Transition> pPath = now.path;
            stack<string> pS = now.s;

            if (t->input == "^" || t->input == string(1, pInput[0])) {
                if (t->input != "^") {
                    pInput.erase(pInput.begin());
                }

                if (t->stackRemove == "^" || ((!(pS.empty())) && (t->stackRemove == pS.top()))) {
                    if (t->stackRemove != "^") pS.pop();

                    if(t->stackAdd != "^") {
                        string aux = t->stackAdd;
                        for (int i =  aux.size() - 1; i >= 0; i--) {
                            //cout<<"adding : "<<aux[i]<<"\n";
                            pS.push(string(1,  aux[i]));
                        }
                    }

                    if(t->output != "^") {
                        pOutput += t->output;
                    }

                    pPath.push_back(*t);
                    ParseState x = ParseState(t->endState, pS, pInput, pOutput, pPath);
                    if (this->hasFinalStates && finalStates.find(x.currState) != finalStates.end()) {
                        cout<<"Final state with output : "<<x.currOutput<<"\n";
                    }
                    else if (!this->hasFinalStates && (x.s).size() == 0) {
                        cout<<"Final bbb state with output : "<<x.currOutput<<"\n";
                    }
                    else
                    {
                        q.push(x);
                    }
                }
            }
        }
    }
}