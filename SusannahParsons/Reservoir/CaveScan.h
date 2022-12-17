#ifndef CAVESCAN_H
#define CAVESCAN_H
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <list>
using namespace std;
struct Location{
    Location(){};
    Location(int newx, int newy)
    :x(newx), y(newy){};
    Location(const Location& l)
    :x(l.x),y(l.y){};
    int x;
    int y;
    string toString() const{
        return "(" + to_string(x) + "," + to_string(y) + ")";
    };
    friend bool operator< (const Location& l1, const Location& l2)
    {
        if(l1.x==l2.x){
            return l1.y<l2.y;
        }else{
            return l1.x<l2.x;
        }
    };
    friend bool operator== (const Location& l1, const Location& l2){
        return ((l1.x==l2.x) && (l1.y==l2.y));
    };
};
struct Tile{
    enum TYPE
    {
        SAND,
        ROCK,
        ENTRY,
        AIR
    };
    Tile(){};
    Tile(TYPE newType)
    :type(newType)
    {};
    TYPE type;
    string toString() const
    {
        if(type==SAND){
            return "o";
        }else if(type==ROCK){
            return "#";
        }else if(type==ENTRY){
            return "+";
        }else if(type==AIR) {
            return ".";
        }
        return "";
    };
};
struct RockStructure{
    vector<Location> lines;
    vector<Location> allRocks;
    bool hasLocation(Location l){
        for (auto & rock : allRocks) {
            if(rock==l){
                return true;
            }
        }
        return false;
    };
    Location getSetLocation(string locstring){
        char location[locstring.size() + 1];
        strcpy(location, locstring.c_str());
        string x(strtok(location, ","));
        string y(strtok(NULL, ","));
        Location l = Location(stoi(x),stoi(y));
        lines.insert(lines.end(),l);
        startLine = endLine;
        endLine = l;
        if(secondCoordFound){
            allRocks.insert(allRocks.end(),endLine);
            if(startLine.x==endLine.x){
                //It's a vertical line
                int addition = (endLine.y > startLine.y) ? -1 : 1;
                int newY = endLine.y + addition;
                while(newY != startLine.y){
                    allRocks.insert(allRocks.end(),Location(endLine.x, newY));
                    newY = newY + addition;
                }
                allRocks.insert(allRocks.end(),startLine);
            }else{
                //Horizontal line
                int addition = (endLine.x > startLine.x) ? -1 : 1;
                int newX = endLine.x + addition;
                while(newX != startLine.x){
                    allRocks.insert(allRocks.end(),Location(newX, endLine.y));
                    newX = newX + addition;
                }
                allRocks.insert(allRocks.end(),startLine);
            }
        }else{
            secondCoordFound = true;
        }
        return l;
    };
private:
    bool secondCoordFound = false;
    Location startLine;
    Location endLine;
};
class CaveScan{
public:
    CaveScan(string filename);
    void toString() const;
private:
    void dropSand(Location sand);
    bool sandFlowsIntoVoid = false;
    bool sandBlocksEntryPoint = false;
    vector<RockStructure> rockStructures;
    vector<vector<Tile>> cave;
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    uint64_t sandNumber = 0;
    Location entryPoint = Location(500,0);
    bool locationIsRock(Location l);
    Location convertCaveLocToVectorLoc(Location l);
    Location convertVectorLocToCaveLog(Location l);
    void addColumn(bool isLeft);
};
#endif // CAVESCAN_H
