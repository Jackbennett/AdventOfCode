#ifndef MONKEY_H
#define MONKEY_H
#include <list>
#include <cmath>
#include <functional>
#include <iostream>
#include <string.h>
using namespace std;
class Monkey{
public:
    Monkey(list<int>startingItems);
    void catchItem(int item);
    void takeTurn();
    void setOperands(vector<string> ops);
    void setDivider(int div);
    void setMonkeyIfTrue(int monkey);
    void setMonkeyIfFalse(int monkey);
    void setMonkeys(vector<Monkey*> monkeys);
    void listItems();
    void showState();
    int getTotalInspections();
private:
    list<int> items;
    vector<Monkey*> monkeys;
    int monkeyIfTrue;
    int monkeyIfFalse;
    int totalInspections;
    void inspect(list<int>::iterator old);
    void bored(list<int>::iterator old);
    bool test(list<int>::iterator old);
    void throwItem(list<int>::iterator item, bool testResult);
    int divider;
    vector<string*> inspectOperands;
};
#endif
