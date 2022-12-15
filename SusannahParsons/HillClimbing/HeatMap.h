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
#include <limits>
#include <set>
using namespace std;
struct Location{
    Location(){};
    Location(int newx, int newy)
    :x(newx),y(newy)
    {};
    Location(const Location& l)
    :x(l.x),y(l.y)
    {};
    int x;
    int y;
    string toString() const {
        string locationString = "(" + to_string(x);
        locationString += "," + to_string(y) + ")";
        return locationString;
    };
    friend bool operator< (const Location& a, const Location& b){
        if(a.x==b.x){
            return a.y<b.y;
        }
	    return (a.x < b.x);
	};
};
struct MapNode{
    MapNode()
    :distanceFromSource(numeric_limits<double>::infinity()), visited(false)
    {};
    MapNode(int newx, int newy, char newelevation)
    :loc(newx,newy), elevation(newelevation), distanceFromSource(numeric_limits<double>::infinity()), visited(false)
    {
        elevationIndex = gradients.find(newelevation);
    };
    using difference_type = std::ptrdiff_t;
    using value_type = MapNode;
    using pointer = MapNode*;
    using reference = MapNode&;
    using iterator_category = std::output_iterator_tag;
    Location loc;
    char elevation;
    int elevationIndex;
    double distanceFromSource;
    bool visited;
    list<Location> shortestpath;
    string gradients = "abcdefghijklmnopqrstuvwxyz";
    const string toString() const {
        string MapNode = "x: " + to_string(loc.x);
        MapNode += " y: " + to_string(loc.y);
        MapNode += " elevation: " + string(1, elevation);
        MapNode += " distance from source: " + to_string(distanceFromSource) + "\n";
        for (auto & location : shortestpath) {
            MapNode += location.toString() + " ";
        }
        return MapNode;
    };
    friend bool operator==(const MapNode &a, const MapNode &b){
        return (a.loc.x==b.loc.x && a.loc.y==b.loc.y);
    };
	friend bool operator!=(const MapNode &a, const MapNode &b){
	    return (!(a.loc.x==b.loc.x && a.loc.y==b.loc.y));
	};
	friend bool operator< (const MapNode& a, const MapNode& b){
	    return (a.loc < b.loc);
	};
	void reset(){
	    shortestpath.clear();
	    distanceFromSource = numeric_limits<double>::infinity();
	    visited=false;
	};
};

class HeatMap{
public:
    HeatMap(string filename);
private:
    void Initialise(string filename);
    int xLimit;
    int yLimit;
    vector<vector<MapNode*>> elevationMap;//elevationMap[x][y]
    list<MapNode*> unvisitedNodes;//unvisitedNodes
    set<MapNode*> unvisitedNodesWithDistanceOnPath;
    MapNode* startPosition;
    MapNode* endPosition;
    void deleteFromUnvisited(MapNode* mp);
    list<MapNode*> getAdjacentNodes(MapNode* mp);
    void runDjikstrasAlgorithm(MapNode* nodeToAnalyse);
    void resetMap();
    void prepareStart(MapNode* mp);
};
#endif
