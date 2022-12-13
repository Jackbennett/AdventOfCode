#include "HeatMap.h"
HeatMap::HeatMap(string filename)
:gradients("abcdefghijklmnopqrstuvwxyz")
{
    Initialise(filename);
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
                vector<MapPoint> colVec;
                elevationMap.insert(elevationMap.end(), colVec);
            }
            MapPoint mp;
            if(c=='S'){
                mp = MapPoint(colNum, rowNum, 'a');
                startPosition = mp;
            }else if(c=='E'){
                mp = MapPoint(colNum, rowNum, 'z');
                positionWithBestSignal = mp;
            }else{
                mp = MapPoint(colNum, rowNum, c);
            }
            elevationMap[colNum].insert(elevationMap[colNum].end(), mp);
            colNum++;
        }
        rowNum++;
    }
    cout << "S is at " << startPosition.toString() << "\n";
    cout << "E is at " << positionWithBestSignal.toString() << "\n";
}

MapPoint HeatMap::nextMove(bool towardsE){
    //Possible to move 1 square u, d, l or r
    int xLimit = elevationMap.size();
    int yLimit = elevationMap[0].size();
    vector<MapPoint> possibleMoves;
    MapPoint journeyPosition = journey.front();
    if(journeyPosition.y+1<yLimit){
        //Try up
        possibleMoves.insert(possibleMoves.end(), elevationMap[journeyPosition.x][journeyPosition.y+1]);
    }
    if(journeyPosition.y-1>-1){
        //Try down
        possibleMoves.insert(possibleMoves.end(), elevationMap[journeyPosition.x][journeyPosition.y-1]);
    }
    if(journeyPosition.x+1<xLimit){
        //Try right
        possibleMoves.insert(possibleMoves.end(), elevationMap[journeyPosition.x+1][journeyPosition.y]);
    }
    if(journeyPosition.x-1>-1){
        //Try left
        possibleMoves.insert(possibleMoves.end(), elevationMap[journeyPosition.x-1][journeyPosition.y]);
    }

    //Check for backtracking
    auto it = possibleMoves.begin();
    while(it != possibleMoves.end()) {
        bool visited = false;
        for(MapPoint& pointVisited : journey) {
            if(pointVisited==(*it)){
                it = possibleMoves.erase(it);
                visited = true;
            }
        }
        if(!visited){
            it++;
        }
    }
    //Check climbability
    it = possibleMoves.begin();
    while(it != possibleMoves.end()) {
        //Check climbability
        int heightCurrent = gradients.find(journeyPosition.elevation);
        int heightMove = gradients.find((*it).elevation);
        if(towardsE){
            //Only possible if elevation is less than 2 higher than current position
            if(!((heightMove-heightCurrent) < 2)){
                it = possibleMoves.erase(it);
            }else{
                it++;
            }
        }else{
            //Only possible if elevation less than 2 lower than the current position
            if(!((heightCurrent-heightMove) < 2)){
                it = possibleMoves.erase(it);
            }else{
                it++;
            }
        }
    }

    //Now pick the one nearest to journey's end
    //First add the end point to the journey points
    it = possibleMoves.begin();
    while(it != possibleMoves.end()) {
        (*it).calculateDistanceToEnd(towardsE?positionWithBestSignal:startPosition);
        it++;
    }
    //Now sort and return the closest to end point
    sort(possibleMoves.begin(),possibleMoves.end());
    return possibleMoves.front();
}

void HeatMap::calculateReverseJourney()
{
    //Start of journey is at E
    cout << "Journey start\n" << positionWithBestSignal.toString() << "\n";
    journey.insert(journey.begin(),positionWithBestSignal);
    int indexGradient = gradients.find(positionWithBestSignal.elevation);
    char nextGradient = gradients[indexGradient-1];
    MapPoint nextPoint = nearest(nextGradient);
    cout << "Nearest next " << nextGradient << " " << nextPoint.toString() << "\n";
    cout << "Arrived at the end. Points on journey " << journey.size() << "\n";
}

MapPoint HeatMap::nearest(char elevationRequired)
{
    list<MapPoint> sameElevation;
    auto it = elevationMap.begin();
    while(it != elevationMap.end()) {
        auto it2 = (it)->begin();
        while(it2 != (it)->end()) {
            MapPoint mp = *it2;
            if((mp).elevation==elevationRequired){
                (mp).calculateDistanceToEnd(journey.front());
                sameElevation.insert(sameElevation.begin(),mp);
            }
            it2++;
        }
        it++;
    }
    sameElevation.sort();
    return sameElevation.front();
}


