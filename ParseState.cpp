//
// Created by ioana on 3/20/2023.
//

#include "ParseState.h"
#include "Transition.h"
#include <vector>

ParseState::ParseState(const string currState, stack<string> s, string currInput, string currOutput, vector<Transition> path) {
    this->currState = currState;
    this->s = s;
    this->currInput = currInput;
    this->currOutput = currOutput;
    this->path = path;
}

void ParseState::addToStack(const string input) {
    this->s.push(input);
}

void ParseState::removeFromStack() {
    this->s.pop();
}