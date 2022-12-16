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
    cout << "Initialising cave " << "(" << xMin << "," << yMin << ")(" << xMax << "," << yMax << ")\n";
    for(int xnum = 0; xnum <= (xMax-xMin); xnum++){
        cave.insert(cave.end(),vector<Tile>());
    }
    for(int yVal = yMin; yVal<=yMax; yVal++){
            cout << "\n";
        for(int xVal = xMin; xVal<=xMax; xVal++){
            Location l(xVal, yVal);
            Tile::TYPE type;
            if(locationIsRock(l)){
                type = Tile::ROCK;
            }else{
                if(l.x==entryPoint.x && l.y==entryPoint.y){
                    type = Tile::ENTRY;
                }else{
                    type = Tile::AIR;
                }
            }
            Tile t(l,type);
            cout << t.toString();
            Location vecLoc(convertCaveLocToVectorLoc(l));
            cave[vecLoc.x].insert(cave[vecLoc.x].end(),t);
        }
    }
    cout << "\n";
    while(!sandFlowsIntoVoid){
        dropSand(Location(convertCaveLocToVectorLoc(entryPoint)),0);
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

void CaveScan::dropSand(Location sand, int counter)
{
    bool debug = false;
    //Try to drop down
    if(sand.y+1 > (cave[0].size()-1)){
        sandFlowsIntoVoid = true;
    }else if(cave[sand.x][sand.y+1].type == Tile::AIR){
        if(debug){
            cout << "Sand drops down " << sand.toString() << "\n";
        }
        sand.y++;
    }//Try to drop diagonal down and left
    else if(sand.x-1 < 0){
        sandFlowsIntoVoid = true;
    }
    else if(cave[sand.x-1][sand.y+1].type == Tile::AIR){
        if(debug){
            cout << "Sand drops left " << sand.toString() << "\n";
        }
        sand.x--;
        sand.y++;
    }//Try to drop diagonal down and right
    else if(sand.x+1 > cave.size()-1){
        sandFlowsIntoVoid = true;
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
        sand = Location(convertCaveLocToVectorLoc(entryPoint));
        sandNumber++;
        dropSand(sand,counter);
    }
    if(!sandFlowsIntoVoid && counter<200){
        counter++;
        dropSand(sand,counter);
    }
}
