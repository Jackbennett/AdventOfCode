#ifndef CUBESCAN_H
#define CUBESCAN_H
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
struct Location{
    Location(){}
    Location(int newx, int newy, int newz)
    :x(newx), y(newy), z(newz){};
    int x;
    int y;
    int z;
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
};
struct Cube{
    Cube(){};
    Cube(int newx, int newy, int newz)
    :loc(newx, newy, newz){}
    Location loc;
    int exposedSides = 6;
    void checkTouch(Cube& c){
        if(c.loc.isTouching(loc)){
            //Both cubes have one less exposed side
            c.exposedSides--;
            exposedSides--;
        }
    }
};
class CubeScan{
public:
    CubeScan(string fileName);
private:
    void checkTouches(Cube& c);
    vector<Cube> cubes;
};
#endif // CUBESCAN_H
