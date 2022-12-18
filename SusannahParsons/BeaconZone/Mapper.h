#ifndef MAPPER_H
#define MAPPER_H
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <set>
#include <algorithm>
#include <stdlib.h>
#include <variant>

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

struct Range{
    Range(){};
    Range(int newMin, int newMax)
    :minVal(newMin), maxVal(newMax){};
    int minVal;
    int maxVal;
    string toString(){
        return "minVal: " + to_string(minVal) + " maxVal: " + to_string(maxVal);
    }
    friend bool operator< (const Range& r1, const Range& r2){
        //Sort by min values
        if(r1.minVal==r2.minVal){
            return r1.maxVal < r2.maxVal;
        }else{
            return r1.minVal < r2.minVal;
        }
    };
    friend bool operator== (const Range& r1, const Range& r2){
        return r1.minVal == r2.minVal && r1.maxVal == r2.maxVal;
    }
    bool touchesRange(int val){
        return (val >= (minVal-1) && val <= (maxVal+1));
    }
    bool hasOverlap(Range r2){
        return touchesRange(r2.minVal) || touchesRange(r2.maxVal);
    }//0,2 and 1,3 and then 4,12
    variant<Range,bool> mergeRange(Range r){
        if(hasOverlap(r)){
            Range currentrange(minVal, maxVal);
            currentrange.minVal = min(currentrange.minVal,r.minVal);
            currentrange.maxVal = max(currentrange.maxVal, r.maxVal);
            return currentrange;
        }
        //Ranges don't overlap
        return false;
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
        return Location::toString() + ": " + "Range: " + to_string(beaconDistance());
    };
    bool pointInRange(Location l){
        return (Location::distance(l, *this) <= beaconDistance());
    }
    Range getXRangeCovered(int row){
        int plusMinus = beaconDistance() - abs(row-y);
        return Range(x-plusMinus, x+plusMinus);
    }
    bool coversRow(int row){
        if(row<y){
            return (row + beaconDistance()) >= y;
        }else{
            return (y + beaconDistance()) >= row;
        }
    }
};

class Mapper{
public:
    Mapper(string fileName, int rowToCheck, int newmaxXY);
private:
    int maxXY = 0;
    int minXY = 0;
    int tmpMaxXY = 400;
    set<Beacon> beacons;
    set<Sensor> sensors;
    vector<vector<bool>> coveredGrid;
    set<int> amountSensorsCoverRow(int rowy);
    variant<int,bool> findGapInCoverage(int rowy);
};
#endif // MAPPER_H
