#include "HeatMap.h"
HeatMap::HeatMap(string filename)
{
    cout << "Initialising...\n";
    Initialise(filename);
    cout << "There are " << elevationMap.size() << " columns of data\n";
    cout << "There are " << unvisitedNodes.size() << " unvisited nodes\n";
    runDjikstrasAlgorithm(startPosition);
    cout << "Displaying shortest path size " << endPosition->shortestpath.size() << "\n";
    for (auto & node : endPosition->shortestpath) {
        cout << node.toString() << "\n";
    }
}

void HeatMap::Initialise(string filename)
{
    string fileLine;
    ifstream inputFile(filename);
    int rowNum = 0;
    while (getline (inputFile, fileLine)) {
        //Iterate chars in string
        int colNum = 0;
        for(char& elevationChar : fileLine) {
            if(rowNum==0){
                //Initialise column vectors
                vector<MapNode*> colVec;
                elevationMap.insert(elevationMap.end(), colVec);
            }
            MapNode* mp;
            if(elevationChar=='S'){
                mp = new MapNode(colNum, rowNum, 'a');
                startPosition = mp;
            }else if(elevationChar=='E'){
                mp = new MapNode(colNum, rowNum, 'z');
                endPosition = mp;
            }else{
                mp = new MapNode(colNum, rowNum, elevationChar);
            }
            unvisitedNodes.insert(unvisitedNodes.begin(), mp);
            elevationMap[colNum].insert(elevationMap[colNum].end(), mp);
            colNum++;
        }
        rowNum++;
    }
    deleteFromUnvisited(startPosition);
    startPosition->shortestpath.insert(startPosition->shortestpath.end(),Location(startPosition->loc));
    startPosition->distanceFromSource = 0;
    xLimit = elevationMap.size();
    yLimit = elevationMap[0].size();
    cout << "S is at " << startPosition->toString() << "\n";
    cout << "E is at " << endPosition->toString() << "\n";
}

void HeatMap::deleteFromUnvisited(MapNode* mp)
{
    for (list<MapNode*>::iterator it = unvisitedNodes.begin(); it != unvisitedNodes.end(); it++)
    if (*it == mp)
    {
        unvisitedNodes.erase(it);
        break;
    }
}

list<MapNode*> HeatMap::getAdjacentNodes(MapNode* mp){
    list<MapNode*> adjacentNodes;
    if(mp->loc.x+1<xLimit){
        //elevation of node must be < mp->elevationindex+2
        MapNode* adjacentNode = (elevationMap[mp->loc.x+1][mp->loc.y]);
        if(adjacentNode->elevationIndex < (mp->elevationIndex+2)){
            if(!adjacentNode->visited){
                adjacentNodes.insert(adjacentNodes.end(),adjacentNode);
            }
        }
    }
    if(mp->loc.x-1>-1){
        MapNode* adjacentNode = (elevationMap[mp->loc.x-1].at(mp->loc.y));
        if(adjacentNode->elevationIndex < (mp->elevationIndex+2)){
            if(!adjacentNode->visited){
                adjacentNodes.insert(adjacentNodes.end(),adjacentNode);
            }
        }
    }
    if(mp->loc.y+1<yLimit){
        MapNode* adjacentNode = (elevationMap[mp->loc.x].at(mp->loc.y+1));
        if(adjacentNode->elevationIndex < (mp->elevationIndex+2)){
            if(!adjacentNode->visited){
                adjacentNodes.insert(adjacentNodes.end(),adjacentNode);
            }
        }
    }
    if(mp->loc.y-1>-1){
        MapNode* adjacentNode = (elevationMap[mp->loc.x].at(mp->loc.y-1));
        if(adjacentNode->elevationIndex < (mp->elevationIndex+2)){
            if(!adjacentNode->visited){
                adjacentNodes.insert(adjacentNodes.end(),adjacentNode);
            }
        }
    }
    return adjacentNodes;
}

bool sortByDistanceFunc (MapNode* i,MapNode* j) { return (i->distanceFromSource<j->distanceFromSource); }

void HeatMap::runDjikstrasAlgorithm(MapNode* nodeToAnalyse)
{
        //Get the adjacent nodes for each member of shortestpath
        set<MapNode*> unvisitedNodesWithDistance;
        for (auto & location : nodeToAnalyse->shortestpath) {
            MapNode* node = (elevationMap[location.x][location.y]);
            list<MapNode*> adjacentNodes = getAdjacentNodes(node);
            //Set the distances
            for (auto & adjacentNode : adjacentNodes) {
                if(adjacentNode->distanceFromSource!=numeric_limits<double>::infinity()){
                    //Node already had a distance from another route. Is this one better?
                    if(adjacentNode->distanceFromSource>node->distanceFromSource+1){
                        //It is better, so update the distance
                        adjacentNode->distanceFromSource=node->distanceFromSource+1;
                    }
                }else{
                    adjacentNode->distanceFromSource=node->distanceFromSource+1;
                }
                unvisitedNodesWithDistance.insert(unvisitedNodesWithDistance.end(),adjacentNode);
            }
        }
        if(unvisitedNodesWithDistance.size()==0){
            return;
        }
        //Sort by distance from source
        //Put all the nodes in a vector, as it's easier to sort and access (set is for uniqueness of nodes)
        vector<MapNode*> sortingNodes;
        for (auto & unvisitedNode : unvisitedNodesWithDistance) {
            sortingNodes.insert(sortingNodes.end(),unvisitedNode);
        }

        sort(sortingNodes.begin(), sortingNodes.end(), sortByDistanceFunc);
        //Now analyse closest node
        MapNode* newNodeToAnalyse = sortingNodes.front();
        //Add the shortest path
        for (auto & location : nodeToAnalyse->shortestpath){
            newNodeToAnalyse->shortestpath.insert(newNodeToAnalyse->shortestpath.end(),location);
        }
        newNodeToAnalyse->shortestpath.insert(newNodeToAnalyse->shortestpath.end(),Location(newNodeToAnalyse->loc));
        //Delete from unvisited
        deleteFromUnvisited(newNodeToAnalyse);
        //Mark as visited
        newNodeToAnalyse->visited = true;
        runDjikstrasAlgorithm(newNodeToAnalyse);
}
