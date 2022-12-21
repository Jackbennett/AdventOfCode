#include "CubeScan.h"
CubeScan::CubeScan(string fileName)
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
    int totalExposedSides = 0;
    for(auto & cube : cubes){
        totalExposedSides = totalExposedSides + cube.exposedSides;
    }
    cout << "Total exposed cube sides " << totalExposedSides << "\n";
}

void CubeScan::checkTouches(Cube& c)
{
    for(auto & cube : cubes){
        cube.checkTouch(c);
    }
}

