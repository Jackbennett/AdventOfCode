#ifndef HEATMAP_H
#define HEATMAP_H
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <cmath>
#include <algorithm>
using namespace std;
struct MapPoint{
    MapPoint(){};
    MapPoint(int newx, int newy, char newelevation)
    :x(newx), y(newy), elevation(newelevation)
    {};
    int x;
    int y;
    int distanceToPoint;
    char elevation;
    string toString(){
        string mappoint = "x: " + to_string(x);
        mappoint += " y: " + to_string(y);
        mappoint += " elevation: " + string(1, elevation);
        return mappoint;
    };
    friend bool operator==(const MapPoint &a, const MapPoint &b){
        return (a.x==b.x && a.y==b.y);
    };
	friend bool operator!=(const MapPoint &a, const MapPoint &b){
	    return (!(a.x==b.x && a.y==b.y));
	};
	int calculateDistanceToPoint(const MapPoint &a){
	    //a^2 + b^2 = h^2
	    distanceToPoint = sqrt(pow(abs(x-a.x),2)+pow(abs(y-a.y),2));
	};
	//Allows sort by distance from a point
	friend bool operator<(const MapPoint &a, const MapPoint &b){
	    return a.distanceToEnd<b.distanceToEnd;
	};
};
struct DirectionPoint{
    DirectionPoint(){};
    DirectionPoint(MapPoint newcentre, MapPoint newup, MapPoint newdown, MapPoint newleft, MapPoint newright)
    :centre(newcentre), up(newup), down(newdown), left(newleft), newright(newright)
    {};
    MapPoint centre;
    MapPoint up;
    MapPoint down;
    MapPoint left;
    MapPoint right;
};
class HeatMap{
public:
    HeatMap(string filename);
    void calculateReverseJourney();
private:
    void Initialise(string filename);
    string gradients;
    vector<vector<MapPoint>> elevationMap;
    MapPoint startPosition;
    vector<MapPoint> journey;
    MapPoint positionWithBestSignal;
    MapPoint nextMove(bool towardsE);
    MapPoint nearest(char elevation);
};
#endif
