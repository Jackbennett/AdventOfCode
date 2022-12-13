#include "HeatMap.h"
HeatMap::HeatMap(string filename)
{
    Initialise(filename);
    runDjikstrasAlgorithm();
}

void HeatMap::Initialise(string filename)
{
    string fileLine;
    ifstream inputFile(filename);
    int rowNum = 0;
    while (getline (inputFile, fileLine)) {
        //Iterate chars in string
        int colNum = 0;
        for(char& c : fileLine) {
            if(rowNum==0){
                //Initialise column vectors
                vector<MapNode> colVec;
                elevationMap.insert(elevationMap.end(), colVec);
            }
            MapNode mp;
            if(c=='S'){
                mp = MapNode(colNum, rowNum, 'a');
                startPosition = mp;
            }else if(c=='E'){
                mp = MapNode(colNum, rowNum, 'z');
                endPosition = mp;
            }else{
                mp = MapNode(colNum, rowNum, c);
            }
            unvisitedNodes.insert(unvisitedNodes.end(), mp);
            elevationMap[colNum].insert(elevationMap[colNum].end(), mp);
            colNum++;
        }
        rowNum++;
    }
    deleteFromUnvisited(startPosition);
    shortestPath.insert(shortestPath.end(),startPosition);
    xLimit = elevationMap.size();
    yLimit = elevationMap[0].size();
    cout << "S is at " << startPosition.toString() << "\n";
    cout << "E is at " << endPosition.toString() << "\n";
}

void HeatMap::deleteFromUnvisited(MapNode mp)
{
    for (set<MapNode>::iterator it = unvisitedNodes.begin(); it != unvisitedNodes.end(); it++)
    if (*it == mp)
    {
        unvisitedNodes.erase(it);
        break;
    }
}

list<MapNode> HeatMap::getAdjacentNodes(MapNode mp){
    list<MapNode> adjacentNodes;
    if(mp.x+1<xLimit){
        //elevation of node must be < mp.elevationindex+2
        MapNode adjacentNode = elevationMap[mp.x+1][mp.y];
        if(adjacentNode.elevationIndex < (mp.elevationIndex+2)){
            if(!adjacentNode.visited()){
                adjacentNodes.insert(adjacentNodes.end(),adjacentNode);
            }
        }
    }
    if(mp.x-1>-1){
        MapNode adjacentNode = elevationMap[mp.x-1][mp.y];
        if(adjacentNode.elevationIndex < (mp.elevationIndex+2)){
            if(!adjacentNode.visited()){
                adjacentNodes.insert(adjacentNodes.end(),adjacentNode);
            }
        }
    }
    if(mp.y+1<yLimit){
        MapNode adjacentNode = elevationMap[mp.x][mp.y+1];
        if(adjacentNode.elevationIndex < (mp.elevationIndex+2)){
            if(!adjacentNode.visited()){
                adjacentNodes.insert(adjacentNodes.end(),adjacentNode);
            }
        }
    }
    if(mp.y-1>-1){
        MapNode adjacentNode = elevationMap[mp.x][mp.y-1];
        if(adjacentNode.elevationIndex < (mp.elevationIndex+2)){
            if(!adjacentNode.visited()){
                adjacentNodes.insert(adjacentNodes.end(),adjacentNode);
            }
        }
    }
    return adjacentNodes;
}

void HeatMap::runDjikstrasAlgorithm()
{
    //Get the adjacent nodes for each member of shortestpath
    list<MapNode> unvisitedNodesWithDistance;
    for (auto const& node : shortestPath) {
        list<MapNode> adjacentNodes = getAdjacentNodes(node);
        //Set the distances
        for (auto const& adjacentNode : adjacentNodes) {
            if(adjacentNode.distanceFromSource!=numeric_limits<double>::infinity()){
                //Node already had a distance from another route. Is this one better?
                if(adjacentNode.distanceFromSource>node.distanceFromSource+1){
                    //TODO it is better, so what do I do about the shortest path now?
                    adjacentNode.distanceFromSource=node.distanceFromSource+1;
                }
            }else{
                adjacentNode.distanceFromSource=node.distanceFromSource+1;
            }
            unvisitedNodesWithDistance.insert(unvisitedNodesWithDistance.end(),adjacentNode);
        }
    }
    //Sort by distance from source
    unvisitedNodesWithDistance.sort();
    //Now analyse closest node
    MapNode nodeToAnalyse = unvisitedNodesWithDistance.front();
    //Insert it into the path
    shortestPath.insert(shortestPath.end(),nodeToAnalyse);
    //Delete from unvisited
    deleteFromUnvisited(nodeToAnalyse);
    //Mark as visited
    nodeToAnalyse.visited = true;
}
