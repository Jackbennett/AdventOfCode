#include "Monkey.h"
Monkey::Monkey(list<uint64_t >startingItems)
:items(startingItems),totalInspections(0)
{

}

void Monkey::takeTurn()
{
    for (list<uint64_t >::iterator it = items.begin(); it != items.end(); it++){
        inspect(it);
        bored(it);
        throwItem(it, test(it));
        //Delete item from the list
        items.erase(it);
    };
}

void Monkey::inspect(list<uint64_t >::iterator old)
{
    totalInspections++;
    uint64_t  firstOperand = (*inspectOperands[0]=="old")?*old:stoi(*inspectOperands[0]);
    uint64_t  secondOperand = ((*inspectOperands[2]=="old")?*old:stoi(*inspectOperands[2]));
    string operatorString = *inspectOperands[1];
    const char* operatorchar = operatorString.c_str();
    switch(*operatorchar){
        case '+':
            *old = (firstOperand + secondOperand);
            break;
        case '-':
            *old = (firstOperand - secondOperand);
            break;
        case '*':
            *old = (firstOperand * secondOperand);
            break;
        case '/':
            *old = (firstOperand / secondOperand);
            break;
        default:
            *old = (firstOperand + secondOperand);
    }

}

void Monkey::bored(list<uint64_t >::iterator old)
{
    //No longer happens in part 2
//    *old = (floor(*old/3.0));
    //Part 2 reduce the size of the item if possible
    *old = *old%reducer;//Reducer is a multiple of all the monkeys' test dividers
}

bool Monkey::test(list<uint64_t >::iterator old)
{
    return (*old%divider==0);
}

void Monkey::throwItem(list<uint64_t >::iterator item, bool testResult)
{

    //Throw it to another monkey
    if(testResult){
//        cout << "Throwing to monkey " << monkeyIfTrue << " " << *item << " divisible by " << divider << "\n";
        monkeys[monkeyIfTrue]->catchItem(*item);
    }else{
//        cout << "Throwing to monkey " << monkeyIfFalse << " " << *item << " not divisible by " << divider << "\n";
        monkeys[monkeyIfFalse]->catchItem(*item);
    }
}

void Monkey::catchItem(uint64_t  item)
{
    items.insert(items.end(),item);
}

void Monkey::setOperands(vector<string> ops)
{
    for(uint64_t  i=0; i<ops.size(); i++){
        string* op = new string(ops[i]);
        inspectOperands.insert(inspectOperands.end(),op);
    }
}

void Monkey::setDivider(uint64_t  div)
{
    divider = div;
}

void Monkey::setMonkeyIfTrue(uint64_t  monkey)
{
    monkeyIfTrue = monkey;
}

void Monkey::setMonkeyIfFalse(uint64_t  monkey)
{
    monkeyIfFalse = monkey;
}

void Monkey::setMonkeys(vector<Monkey*> monkeysvec)
{
    monkeys = monkeysvec;
}

void Monkey::listItems()
{
    for_each(items.begin(), items.end(),
            [this](uint64_t  item)
            {
                cout << item << ",";
            }
    );
    cout << "\n";
}

void Monkey::showState()
{
    cout << "\tStarting items: ";
    listItems();
    cout << "\tOperation: new = " << *inspectOperands[0] << *inspectOperands[1] << *inspectOperands[2] << "\n";
    cout << "\tTest: divisible by " << divider << "\n";
    cout << "\t\tIf true: throw to monkey " << monkeyIfTrue << "\n";
    cout << "\t\tIf false: throw to monkey " << monkeyIfFalse << "\n";
}

uint64_t  Monkey::getTotalInspections()
{
    return totalInspections;
}
void Monkey::setReducer(uint64_t  red)
{
    reducer = red;
}

