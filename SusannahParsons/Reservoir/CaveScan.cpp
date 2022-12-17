#include "CaveScan.h"
CaveScan::CaveScan(string filename)
{
    ifstream inputStream(filename);
    string fileLine;
    list<int> xRange;
    list<int> yRange;
    while(getline(inputStream, fileLine)){
        RockStructure rockStructure;
        string delimiter = " -> ";
        string locstring = fileLine.substr(0, fileLine.find(delimiter));
        while(locstring.size()>0){
            Location l = rockStructure.getSetLocation(locstring);
            xRange.insert(xRange.end(), l.x);
            yRange.insert(yRange.end(), l.y);
            //Delete old locstring string and first delimiter from fileLine and search for next
            fileLine.erase(0, locstring.size()+4);
            locstring = fileLine.substr(0, fileLine.find(delimiter));
        }
        rockStructures.insert(rockStructures.end(),rockStructure);
    }
    //Add the AIR entry point (500,0)
    xRange.insert(xRange.end(),entryPoint.x);
    yRange.insert(yRange.end(),entryPoint.y);
    xRange.sort();
    yRange.sort();
    xMin = xRange.front();
    xMax = xRange.back();
    yMin = yRange.front();
    yMax = yRange.back();
    yMax = yMax+2;//Add the floor
    cout << "Initialising cave " << "(" << xMin << "," << yMin << ")(" << xMax << "," << yMax << ")\n";
    for(int xnum = 0; xnum <= (xMax-xMin); xnum++){
        cave.insert(cave.end(),vector<Tile>());
    }
    for(int yVal = yMin; yVal<=yMax; yVal++){
        for(int xVal = xMin; xVal<=xMax; xVal++){
            Location l(xVal, yVal);
            Tile::TYPE type;
            if(locationIsRock(l) || yVal==yMax){
                type = Tile::ROCK;
            }else{
                if(l.x==entryPoint.x && l.y==entryPoint.y){
                    type = Tile::ENTRY;
                }else{
                    type = Tile::AIR;
                }
            }
            Tile t(type);
            Location vecLoc(convertCaveLocToVectorLoc(l));
            cave[vecLoc.x].insert(cave[vecLoc.x].end(),t);
        }
    }
    cout << "\n";
    toString();
    while(!sandBlocksEntryPoint){
        dropSand(Location(convertCaveLocToVectorLoc(entryPoint)));
    }
    toString();
    cout << sandNumber << " grains of sand landed\n";
}

bool CaveScan::locationIsRock(Location l)
{
    for (auto & rockStructure : rockStructures) {
        if(rockStructure.hasLocation(l)){
            return true;
        }
    }
    return false;
}

Location CaveScan::convertCaveLocToVectorLoc(Location l)
{
    return Location(l.x-xMin,l.y-yMin);
}

Location CaveScan::convertVectorLocToCaveLog(Location l)
{
    return Location(l.x+xMin,l.y+yMin);
}

void CaveScan::toString() const
{
    for(int y=0; y < cave[0].size(); y++){
        cout << "\n";
        for (int x=0; x < cave.size(); x++){
            cout << cave[x][y].toString();
        }
    }
    cout << "\n";
}

void CaveScan::dropSand(Location sand)
{
    bool debug = false;
    bool sandFinishedFalling = false;
    //Try to drop down
    if(cave[sand.x][sand.y+1].type == Tile::AIR){
        if(debug){
            cout << "Sand drops down " << sand.toString() << "\n";
        }
        sand.y++;
    }//Try to drop diagonal down and left
    else if(sand.x-1 < 0){
        addColumn(true);
        sand.x++;//Sand is now in the column to the right
        if(cave[sand.x-1][sand.y+1].type == Tile::AIR){
            sand.x--;
            sand.y++;
        }
    }
    else if(cave[sand.x-1][sand.y+1].type == Tile::AIR){
        if(debug){
            cout << "Sand drops left " << sand.toString() << "\n";
        }
        sand.x--;
        sand.y++;
    }//Try to drop diagonal down and right
    else if(sand.x+1 > cave.size()-1){
        addColumn(false);
        if(cave[sand.x+1][sand.y+1].type == Tile::AIR){
            sand.x++;
            sand.y++;
        }
    }
    else if(cave[sand.x+1][sand.y+1].type == Tile::AIR){
        if(debug){
            cout << "Sand drops right " << sand.toString() << "\n";
        }
        sand.x++;
        sand.y++;
    }//Can't move, sand comes to rest
    else{
        if(debug){
            cout << "Sand comes to rest " << sand.toString() << "\n";
        }
        cave[sand.x][sand.y].type = Tile::SAND;
        sandFinishedFalling = true;
        sandNumber++;
        sandBlocksEntryPoint = (convertVectorLocToCaveLog(sand)==entryPoint);
    }
    if(!sandFinishedFalling){
        dropSand(sand);
    }
}

void CaveScan::addColumn(bool isLeft)
{
    vector<Tile> newColumn;
    for(int y=0; y <= (yMax-yMin); y++){
        if(y+yMin==yMax){
            newColumn.insert(newColumn.end(),Tile(Tile::ROCK));
        }else{
            newColumn.insert(newColumn.end(),Tile(Tile::AIR));
        }
    }

    if(isLeft){
        cave.insert(cave.begin(), newColumn);
        xMin--;
    }else{
        cave.insert(cave.end(), newColumn);
        xMax++;
    }
}
