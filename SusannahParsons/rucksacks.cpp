#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <tuple>
using namespace std;

//Priority is index+1
string alphaArray = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

class ElfGroup{
public:
    string rucksack1Content;
    string rucksack2Content;
    string rucksack3Content;
    tuple<string, int> getBadgePriority(){
        string debug;
        sort(rucksack1Content.begin(), rucksack1Content.end());
        sort(rucksack2Content.begin(), rucksack2Content.end());
        sort(rucksack3Content.begin(), rucksack3Content.end());
        debug += rucksack1Content + "\n";
        debug += rucksack2Content + "\n";
        debug += rucksack3Content + "\n";
        string intersectionFirstTwo;
        set_intersection(rucksack1Content.begin(), rucksack1Content.end(),
                          rucksack2Content.begin(), rucksack2Content.end(),
                          back_inserter(intersectionFirstTwo));
        string badgeChars;
        set_intersection(intersectionFirstTwo.begin(), intersectionFirstTwo.end(),
                          rucksack3Content.begin(), rucksack3Content.end(),
                          back_inserter(badgeChars));
        debug += "Badge " + badgeChars + "\n";
        //Now get the priority of the badge
        return {debug, alphaArray.find_first_of(badgeChars[0]) + 1};
    }
};

int main() {
    // Create a text string, which is used to output the text file
    string fileContent;

    // Read from the text file
    ifstream inputFile("rucksackInput.txt");

    int rucksackCount = 1;
    int tallyPriority = 0;
    int tallyBadgePriority = 0;
    int groupNumber = 1;
    ElfGroup group;
    while (getline (inputFile, fileContent)) {
            cout << "Rucksack " << rucksackCount << ": \n" << fileContent << "\n";
            if(rucksackCount % 3 == 1){
                //Start of group of 3
                cout << "Group " << groupNumber << ": \n";
                cout << "Elf1\n";
                groupNumber++;
                group.rucksack1Content = fileContent;
            }else if(rucksackCount % 3 == 2){
                cout << "Elf2\n";
                //Second elf in group
                group.rucksack2Content = fileContent;
            }else if(rucksackCount % 3 == 0){
                cout << "Elf3\n";
                //Last elf in group
                group.rucksack3Content = fileContent;
                //Should have all the rucksack contents, so can find the badge
                auto [debug, badgePriority] = group.getBadgePriority();
                cout << debug;
                tallyBadgePriority = tallyBadgePriority + badgePriority;
            }
            int totalStuff = fileContent.size();
            string compartment1 = fileContent.substr(0, totalStuff/2);
            string compartment2 = fileContent.substr((totalStuff/2));
//            cout << "compartment1 size: " << compartment1.size() << " " << compartment1 << "\n";
//            cout << "compartment2 size: " << compartment2.size() << " " << compartment2 << "\n";
            //Sort both compartments to set_intersection can be used
            sort(compartment1.begin(), compartment1.end());
            sort(compartment2.begin(), compartment2.end());
            string sharedObjects;
            set_intersection(compartment1.begin(), compartment1.end(),
                          compartment2.begin(), compartment2.end(),
                          back_inserter(sharedObjects));
            //Find index of shared character in the alphaArray to get priority
            int priority = alphaArray.find_first_of(sharedObjects[0]) + 1;
//            cout << "Shared items: " << sharedObjects << " priority: " << priority << "\n";
            tallyPriority = tallyPriority + priority;
            rucksackCount++;
    }
    cout << "Total priority: " << tallyPriority << "\n";
    cout << "Badge total priority: " << tallyBadgePriority << "\n";
    // Close the file
    inputFile.close();
    return 0;
}
