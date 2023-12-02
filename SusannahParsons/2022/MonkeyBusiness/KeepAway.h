#ifndef KEEPAWAY_H
#define KEEPAWAY_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <iterator>
#include <vector>
#include <algorithm>
#include "Monkey.h"
using namespace std;
class KeepAway{
public:
    KeepAway(string file);
    void playRound();
    void showStartingState();
    void showState();
private:
    vector<Monkey*> monkeys;
    void initialiseMonkeys(string file);
};
#endif
