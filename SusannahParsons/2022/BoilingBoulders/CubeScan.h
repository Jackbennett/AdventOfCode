#ifndef CUBESCAN_H
#define CUBESCAN_H
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
struct Location{
    Location(){}
    Location(int& newx, int& newy, int& newz)
    :x(newx), y(newy), z(newz){};
    int x;
    int y;
    int z;
    friend bool operator< (const Location& l1, const Location& l2){
        if(l1.x == l2.x && l1.y == l2.y){
            return l1.z < l2.z;
        }else if(l1.x == l2.x && l1.z == l2.z){
            return l1.y < l2.y;
        }else {
            return l1.x < l2.x;
        }
    };
    friend bool operator== (const Location& l1, const Location& l2){
        return (l1.x == l2.x && l1.y == l2.y && l1.z == l2.z);
    }
    bool isTouching(Location loc){
        if(x==loc.x && y==loc.y){
            return abs(z-loc.z)==1;
        }else if(x==loc.x && z==loc.z){
            return abs(y-loc.y)==1;
        }else if(y==loc.y && z==loc.z){
            return abs(x-loc.x)==1;
        }else{
            return false;
        }
    }
    string getString(){
        return "(" + to_string(x) + "," + to_string(y) + "," + to_string(z) + ")";
    };

};

struct Cube{
    Cube(){};
    Cube(int& newx, int& newy, int& newz)
    {
        loc = Location(newx, newy, newz);
    };
    Location loc;
    int exposedSides = 6;
    friend bool operator== (const Cube& c1, const Cube& c2){
        return c1.loc==c2.loc;
    };
    bool touches(Cube& c){
        return c.loc.isTouching(loc);
    };
    void checkTouch(Cube& c){
        if(c.loc.isTouching(loc)){
            //Both cubes have one less exposed side
            c.exposedSides--;
            exposedSides--;
        }
    };
    string getString(){
        return loc.getString();
    };
};

struct XSorter{
    bool operator() (Cube l1,Cube l2){
        return l1.loc.x<l2.loc.x;
    }
};
struct YSorter{
    bool operator() (Cube l1,Cube l2){
        return l1.loc.y<l2.loc.y;
    }
};
struct ZSorter{
    bool operator() (Cube l1,Cube l2){
        return l1.loc.z<l2.loc.z;
    }
};

class CubeScan{
public:
    CubeScan(string fileName);
private:
    bool isPartOfDroplet(Cube& c);
    void findTrappedAir();
    void checkTouches(Cube& c);
    void initialise(string filename);
    XSorter sortByX;
    YSorter sortByY;
    ZSorter sortByZ;
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    int zMin;
    int zMax;
    vector<Cube> cubes;
    vector<Cube> aircubes;
};
#endif // CUBESCAN_H
