#ifndef ROCKFLOW_H
#define ROCKFLOW
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
struct Location{
    Location(){};
    Location(int newx, int newy)
    :x(newx), y(newy)
    {};
    int x;
    int y;
};
struct XSorter{
    bool operator() (Location l1,Location l2){
        return l1.x<l2.x;
    }
};
struct YSorter{
    bool operator() (Location l1,Location l2){
        return l1.y<l2.y;
    }
};
struct Rock{
    Rock(){};
    Rock(const Rock& r)
    {
        for(auto & loc : r.structure){
            structure.insert(structure.end(),Location(loc.x, loc.y));
        }
    }
    XSorter sortByX;
    YSorter sortByY;
    vector<Location> getCol(int colNum){
        vector<Location> col;
        for(auto & loc : structure){
            if(loc.x==colNum){
                col.insert(col.end(),Location(loc.x,loc.y));
            }
        }
        return col;
    }
    bool isAbove(int rowy){
        sort(structure.begin(), structure.end(),sortByY);
        return rowy < structure.front().y;
    }
    bool isOverlap(Location loc){
        for(auto rock : structure){
            if(rock.x == loc.x && rock.y ==  loc.y){
                return true;
            }
        }
        return false;
    }
    bool inRow(int row){
        return row>=getMinY() && row<=getMaxY();
    }
    int getHeight(){
        sort(structure.begin(), structure.end(),sortByY);
        return structure.back().y - structure.front().y + 1;
    }
    int getWidth(){
        sort(structure.begin(), structure.end(),sortByX);
        return structure.back().x - structure.front().x + 1;
    }
    int getMinX(){
        sort(structure.begin(), structure.end(),sortByX);
        return structure.front().x;
    }

    int getMaxX(){
        sort(structure.begin(), structure.end(),sortByX);
        return structure.back().x;
    }
    int getMinY(){
        sort(structure.begin(), structure.end(),sortByY);
        return structure.front().y;
    }

    int getMaxY(){
        sort(structure.begin(), structure.end(),sortByY);
        return structure.back().y;
    }
    void setLocation(Location start){
        int xDiff = start.x-getMinX();
        int yDiff = start.y-getMinY();
        for(auto & l: structure){

            l.x = l.x+xDiff;
            l.y = l.y+yDiff;
        }
    };

    void printLoc(Location l){
        for(auto loc: structure){
            if(l.x==loc.x && l.y==loc.y){
                cout << "#";
                return;
            }
        }
        cout << ".";
    }
    void printRow(int rowNum){
        for(int xVal=0; xVal<=getWidth(); xVal++){
            printLoc(Location(xVal, rowNum));
        }
    }
    void printRock(){
        for(int row=0; row<getHeight(); row++){
            printRow(row);
            cout << "\n";
        }
    }
    void setStructure(vector<Location> s){
        structure = s;
//        convertY();
        setLocation(Location(2,0));
    }
    vector<Location> structure;
    void convertY(){
        int yConvertor = getHeight()-1;
        for(auto & l: structure){
            l.y = yConvertor-l.y;
        }
    }
};
class RockFlow{
public:
    RockFlow();
    Rock getNext();
private:
    deque<Rock> rockQueue;
    void initialiseRocks();
};
#endif // ROCKFLOW_H
