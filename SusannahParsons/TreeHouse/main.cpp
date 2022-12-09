#include <iostream>
#include <fstream>
#include <string>
#include "TreeQuad.h"

using namespace std;

runFileProcessor(ifstream & inputFile, string fileContent){
    cout << "Initialising tree quad\n";
    bool firstLine = true;
    TreeQuad tq;
    while (getline (inputFile, fileContent)) {
        if(firstLine){
            cout << "Initalising columns\n";
            tq.initColumns(fileContent.size());
            firstLine = false;
        }
        int firstChar = true;
        int col=0;
        for(char& c : fileContent) {

            tq.addTree((c - '0'),(firstChar==true),col);
            if(firstChar){
                firstChar = false;
            }
            col++;
        }
    }
    //Tree quad is now full of trees
    cout << "Tree quad initialised\n";
    tq.markVisibility();
    list<Tree*>* visibleTrees = tq.getVisibleTrees();
    cout << "Number visible trees: " << visibleTrees->size();
    return 0;
}
int main()
{
    string fileContent;
    // Read from the text file
//    ifstream inputFile("testInput.txt");
    ifstream inputFile("treeHouseInput.txt");
    runFileProcessor(inputFile, fileContent);
    // Close the file
    inputFile.close();
    return 0;
}
