#ifndef CATHODERAYTUBE_H
#define CATHODERAYTUBE_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class CathodeRayTube{
public:
    CathodeRayTube(string file);
    void runProgram();
private:
    ifstream inputFile;
    string fileContent;
    int X;
    int cycle;
    int timeToCheckSignalStrength;
    int periodCheckSignalStrength;
    int getSignalStrength();
    vector<int> strengthSamples;
    void runCycle();
    void noop();
    void addx(int amount);
    int getTotalSignalStrengthSamples();
};
#endif
