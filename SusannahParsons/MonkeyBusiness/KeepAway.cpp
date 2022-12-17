#include "KeepAway.h"
KeepAway::KeepAway(string file)
{
    initialiseMonkeys(file);
}

void KeepAway::playRound()
{
    uint64_t  i = 0;
    for (auto & monkey : monkeys)
    {
//        cout << "Monkey: " << i << "\n";
//        monkey->listItems();
        monkey->takeTurn();
        i++;
    }
}

void KeepAway::showStartingState()
{
    uint64_t  monk = 0;
    for (auto & monkey : monkeys)
  {
    cout << "Monkey " << monk << ":\n";
    monkey->showState();
    monk++;
  }
}

void KeepAway::showState()
{
    vector<uint64_t > totalInspections;
    uint64_t  monk = 0;
    for (auto & monkey : monkeys)
    {
        cout << "Monkey " << monk << ": ";
//        monkey->listItems();
        cout << "Total inspections " << monkey->getTotalInspections() << "\n";
        totalInspections.insert(totalInspections.end(),monkey->getTotalInspections());
        monk++;
    }
    //Sort totalInspections
    sort (totalInspections.begin(), totalInspections.end());
    cout << "Busiest monkeys: " << totalInspections[totalInspections.size()-1] << ", " << totalInspections[totalInspections.size()-2] << "\n";
    cout << "Level of monkey business: " << (totalInspections[totalInspections.size()-1] * totalInspections[totalInspections.size()-2]) << "\n";
}


void KeepAway::initialiseMonkeys(string file)
{
    ifstream inputFile(file);
    string fileLine;
    uint64_t  reducer = 1;
    while (getline (inputFile, fileLine)) {
            if(fileLine.find("Starting items")!=string::npos){
                //This is a new monkey, initialise with starting items
                list<uint64_t > startingItems;
                string items = fileLine.substr(18);
                char * itemschar = new char [items.length()+1];
                strcpy (itemschar, items.c_str());
                const char *token = ", ";
                char* itemchar;
                itemchar = strtok(itemschar,token);
                while (itemchar != NULL)
                {
                    startingItems.insert(startingItems.end(),stoi(itemchar));
                    itemchar = strtok (NULL, token);
                }
                Monkey* monkey = new Monkey(startingItems);
                monkeys.insert(monkeys.end(),monkey);
            }
            if(fileLine.find("Operation: new = ")!=string::npos){
                //This is the inspect operation
                string operands = fileLine.substr(19);
                stringstream ss(operands);
                istream_iterator<string> begin(ss);
                istream_iterator<string> end;
                vector<string> operandchars(begin, end);
                monkeys.back()->setOperands(operandchars);
            }
            if(fileLine.find("Test: divisible by ")!=string::npos){
                //This is the test function
                uint64_t  divider = stoi(fileLine.substr(21));
                monkeys.back()->setDivider(divider);
                reducer *= divider;
            }
            if(fileLine.find("If true: throw to monkey")!=string::npos){
                uint64_t  monkey = stoi(fileLine.substr(29));
                monkeys.back()->setMonkeyIfTrue(monkey);
            }
            if(fileLine.find("If false: throw to monkey")!=string::npos){
                uint64_t  monkey = stoi(fileLine.substr(30));
                monkeys.back()->setMonkeyIfFalse(monkey);
            }
    }
    //Make sure all monkeys have access to the other monkeys
    for_each(monkeys.begin(), monkeys.end(),
            [this, reducer](Monkey * monk)
            {
                monk->setMonkeys(monkeys);
                monk->setReducer(reducer);
            }
    );
    cout << "Monkeys initialised. There are " << monkeys.size() << "\n";
    inputFile.close();
}
