#include "Monkey.h"
Monkey::Monkey(list<int>startingItems)
:items(startingItems),totalInspections(0)
{

}

void Monkey::takeTurn()
{
    for (list<int>::iterator it = items.begin(); it != items.end(); it++){
        inspect(it);
        bored(it);
        throwItem(it, test(it));
        //Delete item from the list
        items.erase(it);
    };
}

void Monkey::inspect(list<int>::iterator old)
{
    totalInspections++;
    int firstOperand = (*inspectOperands[0]=="old")?*old:stoi(*inspectOperands[0]);
    int secondOperand = ((*inspectOperands[2]=="old")?*old:stoi(*inspectOperands[2]));
    string operatorString = *inspectOperands[1];
    const char* operatorchar = operatorString.c_str();
    switch(*operatorchar){
        case '+':
            *old = (firstOperand+secondOperand);
            break;
        case '-':
            *old = (firstOperand-secondOperand);
            break;
        case '*':
            *old = (firstOperand*secondOperand);
            break;
        case '/':
            *old = (firstOperand/secondOperand);
            break;
        default:
            *old = (firstOperand+secondOperand);
    }
}

void Monkey::bored(list<int>::iterator old)
{
    *old = (floor(*old/3.0));
}

bool Monkey::test(list<int>::iterator old)
{
    return (*old%divider==0);
}

void Monkey::throwItem(list<int>::iterator item, bool testResult)
{

    //Throw it to another monkey
    if(testResult){
        monkeys[monkeyIfTrue]->catchItem(*item);
    }else{
        monkeys[monkeyIfFalse]->catchItem(*item);
    }
}

void Monkey::catchItem(int item)
{
    items.insert(items.end(),item);
}

void Monkey::setOperands(vector<string> ops)
{
    for(int i=0; i<ops.size(); i++){
        string* op = new string(ops[i]);
        inspectOperands.insert(inspectOperands.end(),op);
    }
}

void Monkey::setDivider(int div)
{
    divider = div;
}

void Monkey::setMonkeyIfTrue(int monkey)
{
    monkeyIfTrue = monkey;
}

void Monkey::setMonkeyIfFalse(int monkey)
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
            [this](int item)
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

int Monkey::getTotalInspections()
{
    return totalInspections;
}

