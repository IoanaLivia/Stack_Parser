//
// Created by ioana on 3/19/2023.
//

#include "Transition.h"
#include "auxiliary.h"
#include <vector>

Transition::Transition(string startState, string endState, string input, string stack, string output) {
    this->startState = startState;
    this->endState = endState;
    this->input = input;
    vector<string> splitStack = splitString(stack, "|");
    this->stackRemove = splitStack[0];
    this->stackAdd = splitStack[1];
    this->output = output;
}