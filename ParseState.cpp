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