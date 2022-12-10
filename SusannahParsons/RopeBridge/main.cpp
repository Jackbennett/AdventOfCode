#include <iostream>
#include <fstream>
#include <string>
#include "RopeBridge.h"
#include <set>
using namespace std;

runFileProcessor(ifstream & inputFile, string fileContent){
    RopeBridge rp;
//    rp.testComparePlaces();//Tested and all working
    while (getline (inputFile, fileContent)) {
            char direction = fileContent[0];
            int moves = stoi(fileContent.substr(2));
            rp.moveHead(direction, moves);
    }
    cout << "Tail places taken " << rp.numberTailPlaces();
    return 0;
}
int main()
{
    string fileContent;

    // Read from the text file
//    ifstream inputFile("testInput.txt");
    ifstream inputFile("ropeInput.txt");
    runFileProcessor(inputFile, fileContent);
    // Close the file
    inputFile.close();
    return 0;
}
