#ifndef CHAMBER_H
#define CHAMBER_H
#include <iostream>
#include <fstream>
#include <string>
#include "RockFlow.h"
using namespace std;
class Chamber{
public:
    Chamber(string fileName);
    void toString();
private:
    bool debug = false;
    RockFlow rf;
    string jets;
    int currentJetIndex = 0;
    Rock currentRock;
    int leftWall = 0;
    int rightWall = 8;
    int floor = 0;
    XSorter sortByX;
    YSorter sortByY;
    string getRowString(int row);
    vector<Location> contents;
    void rockAppears();
    int getTop();
    bool isRock(Location l);
    void rockFall();
    void jetMove(char& jet);
    bool fallDown();
    bool moveRockToPosition(Rock newPosition);
};
#endif // CHAMBER_H
