#ifndef HEATMAP_H
#define HEATMAP_H
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iterator>
#include <cmath>
#include <algorithm>
using namespace std;
struct MapNode{
    MapNode()
    :distanceFromSource(numeric_limits<double>::infinity()), visited(false)
    {};
    MapNode(int newx, int newy, char newelevation)
    :x(newx), y(newy), elevation(newelevation), distanceFromSource(numeric_limits<double>::infinity()), elevationIndex(gradients.find(newelevation)), visited(false)
    {};
    int x;
    int y;
    char elevation;
    int elevationIndex;
    double distanceFromSource;
    bool visited;
    string gradients = "abcdefghijklmnopqrstuvwxyz";
    string toString(){
        string MapNode = "x: " + to_string(x);
        MapNode += " y: " + to_string(y);
        MapNode += " elevation: " + string(1, elevation);
        return MapNode;
    };
    friend bool operator==(const MapNode &a, const MapNode &b){
        return (a.x==b.x && a.y==b.y);
    };
	friend bool operator!=(const MapNode &a, const MapNode &b){
	    return (!(a.x==b.x && a.y==b.y));
	};
	bool operator<(const MapNode&a,const MapNode&b){
	    return a.distanceFromSource<b.distanceFromSource;
	}
};

class HeatMap{
public:
    HeatMap(string filename);
private:
    void Initialise(string filename);
    int xLimit;
    int yLimit;
    vector<vector<MapNode>> elevationMap;//elevationMap[x][y]
    set<MapNode> unvisitedNodes;//unvisitedNodes
    MapNode startPosition;
    MapNode endPosition;
    void deleteFromUnvisited(MapNode mp);
    list<MapNode> getAdjacentNodes();
    void runDjikstrasAlgorithm();
    list<MapNode> shortestPath;
};
#endif
