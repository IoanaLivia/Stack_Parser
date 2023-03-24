#ifndef TC_PROIECT_1_4_AUXILIARY_H
#define TC_PROIECT_1_4_AUXILIARY_H

#include <iostream>
#include <vector>

using namespace std;

static vector<string> splitString(string str, string delimiter)
{
    int start = 0;
    vector<string> tokens = {};
    int end = str.find(delimiter);
    while (end != -1) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start, end - start));

    return tokens;
}

#endif //TC_PROIECT_1_4_AUXILIARY_H
