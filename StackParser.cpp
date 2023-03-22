//
// Created by ioana on 3/19/2023.
//

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

    // reading inputs
    while(getline(fin, line))
    {
        inputs.push_back(line);
    }

    // reading parser input
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
        splitLine = splitString(line, " ");
        Transition* t = new Transition(splitLine[0], splitLine[4], splitLine[1], splitLine[2], splitLine[3]);
        this->transitions.push_back(t);
        cout<<*t<<endl;
        splitLine.clear();
    }

    // //sort(transitions.begin(), transitions.end());

    for (int i = 0; i < (int)states.size(); ++i) {
        graph[states[i]] = {};
    }

    for (int i = 0; i < (int)transitions.size(); ++i) {
        graph[transitions[i]->startState].push_back(transitions[i]);
    }

// works
//    for (int i = 0; i < (int)states.size(); ++i) {
//        cout<<"For state: "<<states[i]<<" we have the following transitions:"<<endl;
//        for (const Transition* t: graph[states[i]]){
//            cout<<*t<<endl;
//        }
//    }
}
//

void StackParser::parse() {

}
//void StackParser::parse() {
//    queue<ParseState> q;
//    //ParseState(const string currState, stack<string> s, string currInput, string currOutput);
//    stack<string> s;
//    string output = "";
//    s.push(initStackSymbol);
//    ParseState y = ParseState(initState, s, inputs[0], output, {});
//    q.push(y);
//    //cout<<p;
//
//    while (!q.empty()) {
//        ParseState now = q.front();
//        q.pop();
//
//        for (const Transition *t: graph[now.currState]) {
//            string pInitState = t->endState, pInput = now.currInput, pOutput = now.currOutput;
//            vector<Transition> pPath = now.path;
//            stack<string> pS = now.s;
//
//           // cout << "Suntem la tranzitia: " << *t<<"\n";
//
//                // verificat daca inputul tranzitiei poate fi satisfacut
//            if (t->input == "^" || t->input == string(1, pInput[0])) {
//                //cout<<"input, putem continua cu : "<<t->input<<" "<<pInput[0]<<endl;
//                if (t->input != "^") {
//                    pInput.erase(pInput.begin());
//                }
//
//                if (t->stackRemove == "^" || ((!(pS.empty())) && (t->stackRemove == pS.top()))) {
//                   // cout<<"stack, putem continua cu : "<<t->stackRemove<<" "<<pS.top()<<endl;
//
//                    if (t->stackRemove != "^") pS.pop();
//
//                    if(t->stackAdd != "^") {
//                        string aux = t->stackAdd;
//                        for (int i =  aux.size() - 1; i >= 0; i--) {
//                            //cout<<"adding : "<<aux[i]<<"\n";
//                            pS.push(string(1,  aux[i]));
//                        }
//
//                       //cout<<"acum avem un stack de dim "<<pS.size()<<" cu pS.top() "<<pS.top()<<endl;
//                    }
//
//                    if(t->output != "^") {
//                        pOutput += t->output;
//                    }
//
//                    pPath.push_back(*t);
//                    ParseState x = ParseState(t->endState, pS, pInput, pOutput, pPath);
//                    cout<<"we would push: "<<x<<"\n";
//                    if (finalStates.find(x.currState) != finalStates.end()) {
//                        cout<<"Final state with output : "<<x.currOutput<<"\n";
//                        cout<<"And path:\n";
//                        for (const Transition tr: pPath) {
//                            cout<<tr<<"\n";
//                        }
//                        cout<<"input: "<<x.currInput<<"\n";
//                    }
//                    else
//                    {
//                        q.push(x);
//                    }
//                }
//            }
//        }
//    }
//}

// verificam daca putem scoate din stiva ce e cerut
// adaugam in stiva ce ni se spune
// modificam outputul
// adaugam in queue noul parse state
