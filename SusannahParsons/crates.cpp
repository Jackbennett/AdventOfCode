#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
runCrates(ifstream & inputFile, string fileContent){
    vector<vector<char>> crates;
    while (getline (inputFile, fileContent)) {
        if(crates.size()==0){
            //Initialise cratestacks
            int numberOfStacks = (fileContent.length()/4) + 1;//The final space stack has no space next to it, so won't divide by 4, add it in
            cout << "Initialising crate stacks, number of stacks: " << numberOfStacks << "\n";
            for(int i=0; i<numberOfStacks; i++){
                vector<char> newStack;
                crates.push_back(newStack);
            }
        }
        if(fileContent.find("[") != string::npos){
            //lines with square brackets have crates in them.
            //4 char to a crate
            int characterNumber = 0;
            for ( string::iterator it=fileContent.begin(); it!=fileContent.end(); ++it){
                int stackNumber = (characterNumber - (characterNumber%4))/4;
                char crateChar = *it;
                if(((characterNumber%4) == 1) && (crateChar != ' ')){
                    //Crate stack has a crate in it
                    crates[stackNumber].push_back(crateChar);
                }
                characterNumber++;
            }
        }
        if(fileContent.find("move") != string::npos){
            //These are instructions for moving crates.
            int indexStartFirstNumber = fileContent.find(' ') + 1;
            int indexEndFirstNumber = fileContent.find(' ', indexStartFirstNumber) -1;
            int indexStartSecondNumber = fileContent.find(' ', indexEndFirstNumber + 2) +1;
            int indexEndSecondNumber = fileContent.find(' ', indexStartSecondNumber) -1;
            int indexStartThirdNumber = fileContent.find(' ', indexEndSecondNumber + 2) +1;
            int indexEndThirdNumber = fileContent.find(' ', indexStartThirdNumber) -1;
            int numberToMove = stoi(fileContent.substr(indexStartFirstNumber,indexEndFirstNumber));
            int fromStack = stoi(fileContent.substr(indexStartSecondNumber,indexEndSecondNumber))-1;//Zero based index
            int toStack = stoi(fileContent.substr(indexStartThirdNumber,indexEndThirdNumber))-1;
            //Part 1, crates change order when moved
//            for(int count = 0; count<numberToMove; count++){
//                //Now move the crates from to...
//                char crateToMove = crates[fromStack].front();
//                //Delete from from stack
//                crates[fromStack].erase(crates[fromStack].begin());
//                //Add to to stack
//                crates[toStack].insert(crates[toStack].begin(), crateToMove);
//
//            }
        //Part 2
            for(int count = numberToMove-1; count > -1; count--){
                //Iterating backwards 3,2,1...
                //Copy the crates to to
                char crateToMove = crates[fromStack][count];
                crates[toStack].insert(crates[toStack].begin(), crateToMove);
            }
            //Now delete the crates from from
            for(int count = numberToMove-1; count > -1; count--){
                crates[fromStack].erase(crates[fromStack].begin());
            }

        }
    }
    //Print out crates to see what's what
    int stackNumber = 1;
    for(vector<vector<char>>::iterator it = crates.begin(); it!=crates.end(); ++it){
        vector<char> crateStack = *it;
        cout << crateStack.front();
        stackNumber++;
    }
}

int main() {
    string fileContent;
    // Read from the text file
    ifstream inputFile("cratesInput.txt");
    runCrates(inputFile, fileContent);
    // Close the file
    inputFile.close();
    return 0;
}
