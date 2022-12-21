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
    :visited(false), distanceFromStart(numeric_limits<double>::infinity()), flowrate(0), opened(false)
    {};
    Valve(string newname)
    :visited(false), distanceFromStart(numeric_limits<double>::infinity()),valveName(newname), flowrate(0), opened(false)
    {};
    Valve(const Valve& newv)
    {
        visited = newv.visited;
        distanceFromStart = newv.distanceFromStart;
        valveName = newv.valveName;
        flowrate = newv.flowrate;
        opened = newv.opened;
        for(auto v : newv.reachableValves){
            reachableValves.insert(reachableValves.end(), v);
        }
        for(auto sp : newv.shortestPath){
            shortestPath.insert(shortestPath.end(),sp);
        }
    };
    bool visited;
    double distanceFromStart;
    vector<Valve> shortestPath;//Pointers so you can work out total benefit and cost of travelling here
    vector<Valve> lastopened;
    string valveName;
    int flowrate;
    bool opened = false;
    set<string> reachableValves;
    friend bool operator== (const Valve& v1, const Valve& v2){
        return v1.valveName==v2.valveName;
    }
    friend bool operator< (const Valve& v1, const Valve& v2){
        return v1.valveName<v2.valveName;
    }
    int pathEndIdx(){
        return shortestPath.size()-1;
    }
    int distance(){
        return shortestPath.size();
    }
    int benefit() {
        int benefit(0);
        if(opened){
            return benefit;
        }
        benefit += flowrate;
        int multiple = 0;
        for(auto valve : shortestPath){
            if(!valve.opened){
                benefit += (valve.flowrate * multiple);
            }
            multiple++;
        }
        return benefit;
    }
    int timeCost(){
        int tc = 0;
        for(auto valve : shortestPath){
            tc++;//Move
            if(!valve.opened && valve.flowrate>0){
                tc++;//Open a valve
            }
        }
        tc--;//Take one off because we don't need to move to the start point
        return tc;
    }
    string toString(){
        int tc = this->timeCost();
        int benefit = this->benefit();
        int spSize = shortestPath.size();
        int spLength = (spSize==0) ? -1 : spSize-1;
        string desc = valveName + " Shortest path ";
        for(auto path: shortestPath){
            desc += path.valveName + "," ;
        }
        desc += " timeCost " + to_string(tc) + " benefit " + to_string(benefit) + " Adjacent valves ";
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
    Valve& findValve(string valveName);
    Valve& getNextValve(string startValve, bool debug);
    bool unopenedValves();
    void showValves();
    vector<Valve> open(Valve v);
    void close(vector<Valve> v);
};
#endif // STEPCALCULATOR_H
