#include <iostream>
#include "StackParser.h"

using namespace std;

int main()
{
    ifstream in("stackParser.in");
    ifstream fin("input.in");

    ofstream fout("output.out");

    StackParser parser(in, fin);

    parser.parse(fout);

    in.close();
    fin.close();
    fout.close();

    return 0;
}