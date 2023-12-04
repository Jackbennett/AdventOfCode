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
    Monkey(list<uint64_t >startingItems);
    void catchItem(uint64_t  item);
    void takeTurn();
    void setOperands(vector<string> ops);
    void setDivider(uint64_t  div);
    void setReducer(uint64_t  red);
    void setMonkeyIfTrue(uint64_t  monkey);
    void setMonkeyIfFalse(uint64_t  monkey);
    void setMonkeys(vector<Monkey*> monkeys);
    void listItems();
    void showState();
    uint64_t  getTotalInspections();
private:
    list<uint64_t > items;
    vector<Monkey*> monkeys;
    uint64_t  monkeyIfTrue;
    uint64_t  monkeyIfFalse;
    uint64_t  totalInspections;
    void inspect(list<uint64_t >::iterator old);
    void bored(list<uint64_t >::iterator old);
    bool test(list<uint64_t >::iterator old);
    void throwItem(list<uint64_t >::iterator item, bool testResult);
    uint64_t  divider;
    uint64_t  reducer;
    vector<string*> inspectOperands;
};
#endif
