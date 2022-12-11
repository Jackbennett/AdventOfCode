#include "KeepAway.h"
KeepAway::KeepAway(string file)
{
    initialiseMonkeys(file);
}

void KeepAway::playRound()
{
    for (auto & monkey : monkeys)
  {
    monkey->takeTurn();
  }
}

void KeepAway::showStartingState()
{
    int monk = 0;
    for (auto & monkey : monkeys)
  {
    cout << "Monkey " << monk << ":\n";
    monkey->showState();
    monk++;
  }
}

void KeepAway::showState()
{
    vector<int> totalInspections;
    int monk = 0;
    for (auto & monkey : monkeys)
    {
        cout << "Monkey " << monk << ": ";
        monkey->listItems();
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
    while (getline (inputFile, fileLine)) {
            if(fileLine.find("Starting items")!=string::npos){
                //This is a new monkey, initialise with starting items
                list<int> startingItems;
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
                int divider = stoi(fileLine.substr(21));
                monkeys.back()->setDivider(divider);
            }
            if(fileLine.find("If true: throw to monkey")!=string::npos){
                int monkey = stoi(fileLine.substr(29));
                monkeys.back()->setMonkeyIfTrue(monkey);
            }
            if(fileLine.find("If false: throw to monkey")!=string::npos){
                int monkey = stoi(fileLine.substr(30));
                monkeys.back()->setMonkeyIfFalse(monkey);
            }
    }
    //Make sure all monkeys have access to the other monkeys
    for_each(monkeys.begin(), monkeys.end(),
            [this](Monkey * monk)
            {
                monk->setMonkeys(monkeys);
            }
    );
    cout << "Monkeys initialised. There are " << monkeys.size() << "\n";
    inputFile.close();
}
