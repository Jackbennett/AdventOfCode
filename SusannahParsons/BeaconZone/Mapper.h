#ifndef MAPPER_H
#define MAPPER_H
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <set>
#include <algorithm>
#include <stdlib.h>

using namespace std;
struct Location{
    Location(){}
    Location(int newx, int newy)
    :x(newx),y(newy){};
    int x;
    int y;
    virtual bool isBeacon(){
        return false;
    };
    virtual bool isSensor(){
        return false;
    };
    friend bool operator< (const Location& l1, const Location& l2){
        if(l1.x == l2.x){
            return l1.y < l2.y;
        }else{
            return l1.x < l2.x;
        }
    };
    friend bool operator== (const Location& l1, const Location& l2){
        return (l1.x == l2.x && l1.y == l2.y);
    }
    string virtual toString(){
        return "(" + to_string(x) + "," + to_string(y) + ")";
    }
    static double distance(Location& l1, Location& l2){
        return abs(l1.x - l2.x) + abs(l1.y - l2.y);
    }
};

struct Beacon: public Location{
    bool isBeacon(){
        return true;
    };
};

struct Sensor: public Location{
    bool isSensor(){
        return true;
    };
    Beacon nearestBeacon;
    double beaconDistance(){
        return Location::distance(*this,nearestBeacon);
    };
    string toString(){
        return Location::toString() + ": " + "Nearest known beacon " + to_string(beaconDistance());
    };
    bool pointInRange(Location l){
        return (Location::distance(l, *this) <= beaconDistance());
    }
};

class Mapper{
public:
    Mapper(string fileName, int rowToCheck);
private:
    set<Beacon> beacons;
    set<Sensor> sensors;
    set<int> amountSensorsCoverRow(int rowy);
};
#endif // MAPPER_H
