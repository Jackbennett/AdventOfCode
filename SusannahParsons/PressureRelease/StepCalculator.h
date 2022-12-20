#ifndef STEPCALCULATOR_H
#define STEPCALCULATOR_H
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <limits>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
struct Valve{
    Valve()
    :visited(false), distanceFromStart(numeric_limits<double>::infinity()), opened(false)
    {};
    Valve(string newname)
    :visited(false), distanceFromStart(numeric_limits<double>::infinity()),name(newname), opened(false)
    {};
    Valve(const Valve& newv)
    :visited(newv.visited),distanceFromStart(newv.distanceFromStart),name(newv.name), flowrate(newv.flowrate), opened(newv.opened)
    {
        for(auto v : newv.reachableValves){
            reachableValves.insert(reachableValves.end(), v);
        }
        for(auto sp : newv.shortestPath){
            shortestPath.insert(shortestPath.end(),sp);
        }
    };
    bool visited;
    double distanceFromStart;
    vector<string> shortestPath;
    string name;
    int flowrate;
    bool opened = false;
    set<string> reachableValves;
    friend bool operator== (const Valve& v1, const Valve& v2){
        return v1.name==v2.name;
    }
    friend bool operator< (const Valve& v1, const Valve& v2){
        return v1.name<v2.name;
    }
    int benefit() {
        if(opened){
            return 0;
        }else{
            return flowrate;
        }
    }
    int timeCost(){
        int sp = shortestPath.size();
        if(opened || flowrate==0){
            return (sp-1);
        }else{
            return (sp);//Need an extra minute to open the valve
        }
    }
    string toString(){
        int tc = this->timeCost();
        int benefit = this->benefit();
        int spSize = shortestPath.size();
        int spLength = (spSize==0) ? -1 : spSize-1;
        string desc = name + " Shortest path " + to_string(spLength) + " timeCost " + to_string(tc) + " benefit " + to_string(benefit) + " Adjacent valves ";
        for(auto step : reachableValves){
            desc += step + ", ";
        }
        if(visited){
            desc += " visited";
        }else{
            desc += " not visited";
        }
        if(opened){
            desc += " OPEN";
        }else{
            desc += " SHUT";
        }
        return desc;
    }
};
class StepCalculator{
public:
    StepCalculator(string fileName);
private:
    vector<Valve> valves;
    void resetDjikstra();
    void runDjikstra(string startvalve, int& countruns);
    Valve& findValve(string name);
    Valve& getNextValve(string startValve);
    bool unopenedValves();
    void showValves();
};
#endif // STEPCALCULATOR_H
