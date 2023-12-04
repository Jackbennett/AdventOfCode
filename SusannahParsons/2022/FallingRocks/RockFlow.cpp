#include "RockFlow.h"

RockFlow::RockFlow()
{
    initialiseRocks();
}

Rock RockFlow::getNext()
{
    Rock nextRock=rockQueue.front();
    rockQueue.pop_front();
    rockQueue.push_back(nextRock);
    return Rock(nextRock);//Return a copy
}

void RockFlow::initialiseRocks()
{
    //Initialise Rocks
    Rock minusRock;
    vector<Location> minusStruct;
    minusStruct.insert(minusStruct.end(),Location(0,0));
    minusStruct.insert(minusStruct.end(),Location(1,0));
    minusStruct.insert(minusStruct.end(),Location(2,0));
    minusStruct.insert(minusStruct.end(),Location(3,0));
    minusRock.setStructure(minusStruct);
    Rock plusRock;
    vector<Location> plusStruct;
    plusStruct.insert(plusStruct.end(),Location(1,0));
    plusStruct.insert(plusStruct.end(),Location(0,1));
    plusStruct.insert(plusStruct.end(),Location(1,1));
    plusStruct.insert(plusStruct.end(),Location(2,1));
    plusStruct.insert(plusStruct.end(),Location(1,2));
    plusRock.setStructure(plusStruct);
    Rock lRock;
    vector<Location> lStruct;
    lStruct.insert(lStruct.end(),Location(0,0));
    lStruct.insert(lStruct.end(),Location(1,0));
    lStruct.insert(lStruct.end(),Location(2,0));
    lStruct.insert(lStruct.end(),Location(2,1));
    lStruct.insert(lStruct.end(),Location(2,2));
    lRock.setStructure(lStruct);
    Rock iRock;
    vector<Location> iStruct;
    iStruct.insert(iStruct.end(),Location(0,0));
    iStruct.insert(iStruct.end(),Location(0,1));
    iStruct.insert(iStruct.end(),Location(0,2));
    iStruct.insert(iStruct.end(),Location(0,3));
    iRock.setStructure(iStruct);
    Rock squareRock;
    vector<Location> squareStruct;
    squareStruct.insert(squareStruct.end(),Location(0,0));
    squareStruct.insert(squareStruct.end(),Location(1,0));
    squareStruct.insert(squareStruct.end(),Location(0,1));
    squareStruct.insert(squareStruct.end(),Location(1,1));
    squareRock.setStructure(squareStruct);
    //insert into deque
    rockQueue.insert(rockQueue.end(), minusRock);
    rockQueue.insert(rockQueue.end(), plusRock);
    rockQueue.insert(rockQueue.end(), lRock);
    rockQueue.insert(rockQueue.end(), iRock);
    rockQueue.insert(rockQueue.end(), squareRock);
}
