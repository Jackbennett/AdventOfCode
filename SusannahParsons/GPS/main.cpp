#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

printCode(vector<int> code){
    for(auto & c : code){
        printf("%d,", c);
    }
    printf("\n");
}

int getPosition(vector<int> code, int value){
    int index=0;
    for(auto & v : code){
        if(v==value){
            return index;
        }
        index++;
    }
}

int getNewPos(vector<int> code, int moves, int currentPos, bool movingItem){
    int codeSize = code.size();
    int codeMaxIndex = code.size()-1;
    int modulo = (movingItem) ? codeMaxIndex : codeSize;
    int newPos = (moves%modulo);//This gets rid of complete circuits
    if(false){
        printf("modulo %d moves %d currentPos %d moves%%modulo %d\n",modulo, moves, currentPos, newPos);
    }
    if(moves<0){
        newPos = newPos + currentPos;
        if(newPos<=0){
            return codeMaxIndex+newPos;
        }else{
            return newPos;
        }
    }else if(moves>0){
        newPos = currentPos + newPos;
        if(newPos>codeMaxIndex){
            return newPos-modulo;
        }else{
            return newPos;
        }
    }else{
        //Not moved
        return currentPos;
    }
}

vector<int> mixCode(vector<int> code, vector<int> mixedCode, bool debug){
    int highestCodeIndex = code.size()-1;
    for(int codeIndex=0; codeIndex<=highestCodeIndex; codeIndex++){
        int itemToMove = code[codeIndex];
        if(debug){
            printCode(mixedCode);
            printf("Moving item %d\n", itemToMove);
        }
        int posInMixed = getPosition(mixedCode, itemToMove);
        int newPos = getNewPos(mixedCode, itemToMove, posInMixed, true);
        if(debug){
            printf("New position %d\n", newPos);
        }
        //Remove the old item and replace in new position
        for(vector<int>::iterator it = mixedCode.begin(); it<mixedCode.end(); it++){
            if(*it==itemToMove){
                mixedCode.erase(it);
                break;
            }
        }
        if(debug){
            printf("Removed from mixed code\n");
            printCode(mixedCode);
        }
        if(newPos==mixedCode.size()){
           mixedCode.insert(mixedCode.end(),itemToMove);
        }else{
            int insertIndex=0;
            for(vector<int>::iterator it = mixedCode.begin(); it<mixedCode.end(); it++){
                if(insertIndex==newPos){
                    mixedCode.insert(it,itemToMove);
                    break;
                }
                insertIndex++;
            }
        }

        if(debug){
            printf("Inserted in new position\n");
            printCode(mixedCode);
        }
    }
    return mixedCode;
}



int getGroveCoordinate(vector<int> mixedCode, int moves){

    int positionZero = getPosition(mixedCode, 0);
    return mixedCode.at(getNewPos(mixedCode, moves, positionZero, false)+1);
}

int main()
{
    bool debug = false;
//    ifstream inputs("testInput.txt");
    ifstream inputs("input.txt");
    vector<int> code;
    vector<int> mixedCode;
    string coord;
    while(getline(inputs, coord)){
        code.insert(code.end(),stoi(coord));
        mixedCode.insert(mixedCode.end(),stoi(coord));
    }

    //Mixing once
    mixedCode = mixCode(code, mixedCode, debug);

    int move1 = 1000;
    int move2 = 2000;
    int move3 = 3000;

    int coord1 = getGroveCoordinate(mixedCode, move1);
    int coord2 = getGroveCoordinate(mixedCode, move2);
    int coord3 = getGroveCoordinate(mixedCode, move3);

    printf("First coordinate is %d, second is %d and third is %d\n", coord1, coord2, coord3);
    //2695 is too low -6852 is wrong -4317. 17612 is too high. Try 17297 - nope, not that I can remember how I came to that one anyway.
    printf("Sum of grove coordinates is %d",(coord1+coord2+coord3));
    return 0;
}
