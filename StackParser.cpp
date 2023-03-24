#include "StackParser.h"
#include "Transition.h"
#include "auxiliary.h"
#include "ParseState.h"
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

const string StackParser::LAMBDA = "^";

StackParser::StackParser(istream &in, istream &fin) {
    string line;
    vector<string> splitLine = {};

    getline(in, line);

    splitLine = splitString(line, " ");

    for (string &s: splitLine) {
        this->inputAlph.insert(s);
    }

    splitLine.clear();

    getline(in, line);

    splitLine = splitString(line, " ");

    for (string &s: splitLine) {
        this->outputAlph.insert(s);
    }

    splitLine.clear();

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
        if (line.size() == 0) break;
        splitLine = splitString(line, " ");
        if ((this->inputAlph.find(splitLine[1]) != this->inputAlph.end() || splitLine[1]  == LAMBDA) && (this->outputAlph.find(splitLine[3]) != this->outputAlph.end() || splitLine[3]  == LAMBDA))
        {
            Transition* t = new Transition(splitLine[0], splitLine[4], splitLine[1], splitLine[2], splitLine[3]);
            this->transitions.push_back(t);
        }
        splitLine.clear();;
    }

    for (int i = 0; i < (int)states.size(); ++i) {
        graph[states[i]] = {};
    }

    for (int i = 0; i < (int)transitions.size(); ++i) {
        graph[transitions[i]->startState].push_back(transitions[i]);
    }
}

void StackParser::parse(ofstream &fout) {
    queue<ParseState> q;
    stack<string> s;
    string output = "";
    bool foundOutput = false;
    s.push(initStackSymbol);
    for (int i = 0; i < inputs.size(); ++i) {
        fout<<"For input : "<<inputs[i]<<" the following outputs were found:\n";
        cout<<"Currently parsing input "<<inputs[i]<<"\n";

        foundOutput = false;

        ParseState y = ParseState(initState, s, inputs[i], output, {});
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

                    if (t->stackRemove == LAMBDA || ((!(pS.empty())) && (t->stackRemove == pS.top()))) {
                        if (t->stackRemove != LAMBDA) pS.pop();

                        if (t->stackAdd != LAMBDA) {
                            string aux = t->stackAdd;
                            for (int i = aux.size() - 1; i >= 0; i--) {
                                pS.push(string(1, aux[i]));
                            }
                        }

                        if (t->output != LAMBDA) {
                            pOutput += t->output;
                        }

                        pPath.push_back(*t);
                        ParseState x = ParseState(t->endState, pS, pInput, pOutput, pPath);
                        if (this->hasFinalStates && finalStates.find(x.currState) != finalStates.end() &&
                            x.currInput == "") {
                            fout << "Output [by final state] : " << x.currOutput << "\n";
                            foundOutput = true;
                        } else if (!this->hasFinalStates && (x.s).size() == 0) {
                            fout << "Output [by empty stack] : " << x.currOutput << "\n";
                            foundOutput = true;
                        } else {
                            q.push(x);
                        }
                    }
                }
            }
        }

        if(!foundOutput) {
            fout << "None\n";
        }
    }

    cout<<"Parsing ended.\n";
}