#include "CubeScan.h"
CubeScan::CubeScan(string fileName)
{
    initialise(fileName);
    int totalExposedSides = 0;
    for(auto & cube : cubes){
        totalExposedSides = totalExposedSides + cube.exposedSides;
    }
    cout << "Total exposed cube sides " << totalExposedSides << "\n";
    findTrappedAir();
    totalExposedSides = 0;
    for(auto & cube : cubes){
        totalExposedSides = totalExposedSides + cube.exposedSides;
    }
    //4026 is too high
    cout << "Recalculated total exposed cube sides " << totalExposedSides << "\n";
}

void CubeScan::initialise(string fileName)
{
    ifstream inputs(fileName);
    string fileLine;
    while(getline(inputs, fileLine)){
        //Each line is a cube. Each token is a coordinate.
        char char_array[fileLine.size() + 1];
        strcpy(char_array, fileLine.c_str());
        char * coord;
        coord = strtok (char_array,",");
        Cube* c = new Cube();
        int tokenNum = 1;
        while (coord != NULL)
        {
            if(tokenNum==1){
                c->loc.x = stoi(coord);
            }else if(tokenNum==2){
                c->loc.y = stoi(coord);
            }else{
                c->loc.z = stoi(coord);
            }
            coord = strtok (NULL, ",");
            tokenNum++;
        }
        //Check if cube touches any of the others
        checkTouches(*c);
        //Add cube to content
        cubes.insert(cubes.end(), *c);
    }
    //Initialise limits
    sort(cubes.begin(), cubes.end(), sortByX);
    xMin = cubes.front().loc.x;
    xMax = cubes.back().loc.x;
    sort(cubes.begin(), cubes.end(), sortByY);
    yMin = cubes.front().loc.y;
    yMax = cubes.back().loc.y;
    sort(cubes.begin(), cubes.end(), sortByZ);
    zMin = cubes.front().loc.z;
    zMax = cubes.back().loc.z;
}

void CubeScan::findTrappedAir()
{
    for(int xval=xMin; xval<=xMax; xval++){
        for(int yval=yMin; yval<=yMax; yval++){
            for(int zval=zMin; zval<=zMax; zval++){
                Cube possibleTrappedAir = Cube(xval, yval, zval);
                if(!isPartOfDroplet(possibleTrappedAir)){
                    //Definitely air
                    if(possibleTrappedAir.exposedSides==0){
                        //Trapped air!
                        cout << "Found trapped air at " << possibleTrappedAir.getString() << "\n";
                        checkTouches(possibleTrappedAir);
                    }
                }
            }
        }
    }
}

bool CubeScan::isPartOfDroplet(Cube& c)
{
    for (auto & drop : cubes){
        if(c==drop){
            return true;
        }else{
            if(drop.touches(c)){
                c.exposedSides--;
            }
        }
    }
}


void CubeScan::checkTouches(Cube& c)
{
    for(auto & cube : cubes){
        cube.checkTouch(c);
    }
}

