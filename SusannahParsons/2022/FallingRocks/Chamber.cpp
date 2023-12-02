#include "Chamber.h"

Chamber::Chamber(string fileName)
{
    ifstream inputs(fileName);
    getline(inputs, jets);
    for(int countRock=0; countRock<2022; countRock++){
        rockAppears();
//        toString();
        rockFall();
//        toString();
    }
    cout << "Top of heap " << getTop() << "\n";

}

void Chamber::rockFall()
{
    bool rockFalling = true;
    int moves=0;
    while(rockFalling){
        if(moves%2==0){
            //Jet move
            char jet = jets[currentJetIndex];
            currentJetIndex++;
            if(currentJetIndex==jets.size()){
                currentJetIndex = 0;
            }
            if(debug){
                cout << "Jet of gas pushes rock " << ((jet=='<')?"left\n":"right\n");
            }
            jetMove(jet);
            if(debug){
                toString();
            }
        }else{
            if(debug){
                cout << "Rock falls one unit\n";
            }
            //Fall down
            if(!fallDown()){
                rockFalling=false;
                //Move current rock to chamber contents, get a new falling rock
                for(auto & loc : currentRock.structure){
                    contents.insert(contents.end(),loc);
                }
            }
            if(debug){
                toString();
            }
        }
        moves++;
    }
}

void Chamber::jetMove(char & jet)
{
    Rock newPosition = Rock(currentRock);
    if(jet=='<'){
        //Move left
        for(auto & loc : newPosition.structure){
            loc.x--;
        }
    }else{
        //Move right
        for(auto & loc : newPosition.structure){
            loc.x++;
        }
    }
    moveRockToPosition(newPosition);

}

bool Chamber::fallDown()
{
    Rock newPosition = Rock(currentRock);
    for(auto & loc : newPosition.structure){
        loc.y--;
    }
    return moveRockToPosition(newPosition);
}

bool Chamber::moveRockToPosition(Rock newPosition){
    int hitsSomething = false;
    for(auto loc : newPosition.structure){
        //If it won't hit anything, then move current rock to the new position.
        if(loc.x == leftWall || loc.x == rightWall || loc.y == floor || isRock(loc)){
            hitsSomething = true;
        }
    }
    if(!hitsSomething){
        currentRock = newPosition;
    }
    return !hitsSomething;
}


void Chamber::toString()
{
    cout << "\n";
    int maxRow = currentRock.getMaxY();
    for(int row = maxRow; row>-1; row--){
        cout << getRowString(row) << "\n";
    }
}


string Chamber::getRowString(int row)
{
    string rowString;
    for(int col=leftWall; col<=rightWall; col++){
        Location loc(col, row);
        if(row==floor){
            //floor
            if(col==leftWall){
                rowString += "+";
            }else if(col==rightWall){
                rowString += "+";
            }else{
                rowString += "-";
            }
        }else{
            //We're down to the contents. Either falling rock, stationary rock, air or wall
            if(col==leftWall || col==rightWall){
                rowString += "|";
            }else if(isRock(loc)){
                rowString += "#";
            }else if(currentRock.isOverlap(loc)){
                rowString += "@";
            }else{
                rowString += ".";
            }
        }
    }
    return rowString;
}

bool Chamber::isRock(Location l)
{
    for(auto rock : contents){
        if(rock.x==l.x && rock.y==l.y){
            return true;
        }
    }
    return false;
}

void Chamber::rockAppears()
{
    if(debug){
        cout << "A new rock appears\n";
    }
    currentRock = rf.getNext();
    currentRock.setLocation(Location(leftWall + 3, getTop() + 4));
}
int Chamber::getTop()
{
    int top = floor;
    //Find height of contents
    if(contents.size()>0){
        sort(contents.begin(), contents.end(), sortByY);
        top = contents.back().y;
    }
    return top;
}

