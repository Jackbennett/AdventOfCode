#include "StepCalculator.h"

StepCalculator::StepCalculator(string fileName)
{
    ifstream inputStream(fileName);
    string fileLine;
    while(getline(inputStream, fileLine)){
        char char_array[fileLine.size() + 1];
        strcpy(char_array, fileLine.c_str());
        char * stringItem;
        int itemNumber = 1;
        stringItem = strtok (char_array," ,=;");
        Valve* v = new Valve();
        while (stringItem != NULL)
        {
            if(itemNumber==2){
                //Valve name
                v->valveName = stringItem;
            }
            if(itemNumber==6){
                //Flow rate
                v->flowrate = stoi(stringItem);
            }
            if(itemNumber>10){
                //Tunnels to valves
                v->reachableValves.insert(v->reachableValves.end(),stringItem);
            }
            itemNumber++;
            stringItem = strtok (NULL, " ,=;");
        }
        valves.insert(valves.end(), *v);
    }
    cout << "Initialised valves\n";
    //Part 2 answer is too high 5137. Also not 2920. And not 3138. Need to run my turn and elephant turn concurrently in time by each step or won't work....
    //While there are still unopened valves
    uint64_t currentPressure=0;
    uint64_t totalPressure=0;
    int time=1;
    //I'm starting at A and going to the best valve
    Valve* elephantTargetValve = new Valve(getNextValve("AA",false));
    vector<Valve> openedValves = open(findValve(elephantTargetValve->valveName));
    cout << "\n\nOPENED\n";
    for(auto valv : valves){
        cout << valv.toString() << "\n";
    }
    Valve* myTargetValve = new Valve(getNextValve("AA", false));
    close(openedValves);
    cout << "\n\nCLOSED\n";
    for(auto valv : valves){
        cout << valv.toString() << "\n";
    }

    int myMoves =myTargetValve->distance();
    int elephantMoves =elephantTargetValve->distance();
    Valve* myCurrentPos = &findValve(myTargetValve->shortestPath.at(0).valveName);
    Valve* elephantCurrentPos = &findValve(elephantTargetValve->shortestPath.at(0).valveName);
    while(time!=27){
        cout << "Minute " << time << "\n";
        totalPressure = totalPressure + currentPressure;

        int myPathIndx = myTargetValve->shortestPath.size()-myMoves;
        int elephantPathIndx = elephantTargetValve->shortestPath.size()-elephantMoves;

        cout << "My target " << myTargetValve->toString() << " size " << myTargetValve->shortestPath.size() << " my moves " << myMoves << "\n";
        cout << "Elephant target " << elephantTargetValve->toString() << " size " << elephantTargetValve->shortestPath.size() << " elephant moves " << elephantMoves << "\n";

        cout << "My current position " <<myCurrentPos->toString() << "\n";
        if(!myCurrentPos->opened && myCurrentPos->flowrate>0){
            Valve* vToOpen = &findValve(myCurrentPos->valveName);
            cout << "I open valve " << vToOpen->valveName << "\n";
            findValve(vToOpen->valveName).opened = true;
            currentPressure = currentPressure + vToOpen->flowrate;
        }else if(myPathIndx < myTargetValve->pathEndIdx()){
            cout << "I move along path\n";
            myMoves--;
            myPathIndx = myTargetValve->shortestPath.size()-myMoves;
            myCurrentPos = &findValve(myTargetValve->shortestPath.at(myPathIndx).valveName);
            cout << "I move to " << myCurrentPos->valveName << " at path index " << myPathIndx << "\n";
        }else if(myPathIndx == myTargetValve->pathEndIdx()){
            cout << "I find the next valve and move to the first place\n";
            //Get the next valve
            vector<Valve> openedValves = open(findValve(elephantTargetValve->valveName));
            myTargetValve = new Valve(getNextValve(myTargetValve->valveName, false));
            close(openedValves);
            myMoves = myTargetValve->pathEndIdx();
            myPathIndx = myTargetValve->shortestPath.size()-myMoves;
            cout << "My target " << myTargetValve->toString() << " size " << myTargetValve->shortestPath.size() << " my moves " << myMoves << "\n";
            myCurrentPos = &findValve(myTargetValve->shortestPath.at(myPathIndx).valveName);
            cout << "I move to " << myCurrentPos->valveName << " at path index " << myPathIndx << "\n";
        }
        cout << "Elephant current position " <<elephantCurrentPos->toString() << "\n";

        if(!elephantCurrentPos->opened && elephantCurrentPos->flowrate>0){
            Valve* vToOpen = &findValve(elephantCurrentPos->valveName);
            cout << "Elephant opens valve " << vToOpen->valveName << "\n";
            findValve(vToOpen->valveName).opened = true;
            currentPressure = currentPressure + vToOpen->flowrate;
        }else if(elephantPathIndx < elephantTargetValve->pathEndIdx()){
            cout << "Elephant moves along path\n";
            elephantMoves--;
            elephantPathIndx = elephantTargetValve->shortestPath.size()-elephantMoves;
            elephantCurrentPos = &findValve(elephantTargetValve->shortestPath.at(elephantPathIndx).valveName);
            cout << "Elephant moves to " << elephantCurrentPos->valveName << " at path index " << elephantPathIndx << "\n";
        }else if(elephantPathIndx == elephantTargetValve->pathEndIdx()){
            cout << "Elephant finds the next valve and moves to the first place\n";
            //Get the next valve.
            vector<Valve> openedValves = open(findValve(myTargetValve->valveName));
            elephantTargetValve = new Valve(getNextValve(elephantTargetValve->valveName, false));
            close(openedValves);
            elephantMoves = elephantTargetValve->pathEndIdx();
            elephantPathIndx = elephantTargetValve->shortestPath.size()-elephantMoves;
            cout << "Elephant target " << elephantTargetValve->toString() << " size " << elephantTargetValve->shortestPath.size() << " elephant moves " << elephantMoves << "\n";
            elephantCurrentPos = &findValve(elephantTargetValve->shortestPath.at(elephantPathIndx).valveName);
            cout << "Elephant moves to " << elephantCurrentPos->valveName << " at path index " << elephantPathIndx << "\n";
        }
        time++;
    }
    cout << "Finished running. Total pressure released: " << totalPressure << "\n";

}

Valve& StepCalculator::getNextValve(string startValve, bool debug)
{
    if(debug){
        cout << "Running get next valve, resetting Djikstra\n";
    }
    resetDjikstra();
    if(debug){
        cout << "Reset complete, finding shortest paths\n";
    }
    Valve& vstart = findValve(startValve);
    vstart.distanceFromStart = 0;
    int countRuns(0);
    //Find the shortest paths
    runDjikstra(vstart.valveName,countRuns);
    if(debug){
        cout << "\n\nShortest paths found\n";
        cout <<"sorting by time cost\n";
    }
    struct sortByCost{
        bool operator() (Valve v1,Valve v2){
            return v1.timeCost()<v2.timeCost();
        }
    } sorter;
    //Sort by time cost
    sort(valves.begin(), valves.end(), sorter);
    if(debug){
        cout << "Sorted, now find the best valve\n";
    }

    Valve* bestValve = &valves.front();
    if(debug){
        cout << "Starting with valve " << bestValve->toString() << "\n";
    }
    for(auto & v : valves){
        if(debug){
            cout << "Current best valve " << bestValve->toString() << "\n" << v.toString() << "\n";
        }
        if(v.timeCost()==bestValve->timeCost()){
            if(debug)
            {
                cout << "Time cost is the same, choosing greatest benefit\n";
            }
            if(v.benefit() >  bestValve->benefit()){
                bestValve = &v;
            }
        }

        if(v.timeCost()>bestValve->timeCost() && v.benefit() > bestValve->benefit()){
            if(debug){
                cout << "Comparing with valve " << v.toString() << "\n";
            }
            int costDiff = v.timeCost()-bestValve->timeCost()+1;
            int cumulativeBestValue = bestValve->benefit() * costDiff;
            if(debug){
                cout << "cost difference " << costDiff << " cumulative best value " << cumulativeBestValue << "\n";
            }
            if(cumulativeBestValue < v.benefit()){
                bestValve = &v;
            }
            if(debug){
                cout << "Valve " << bestValve->valveName << " won the comparison: " << v.toString() << "\nBest valve is now " << bestValve->toString() << "\n";
            }
        }
    }
    if(debug){
        cout << "Returning best valve " << bestValve->toString() << "\n";
    }
    return *bestValve;
}

bool StepCalculator::unopenedValves()
{
    for(auto v : valves){
        if(!v.opened && v.flowrate>0){
            return true;
        }
    }
    return false;
}

void StepCalculator::resetDjikstra()
{
    for(vector<Valve>::iterator it = valves.begin(); it<valves.end(); it++){
        it->shortestPath.clear();
        it->visited = false;
        it->distanceFromStart = numeric_limits<double>::infinity();
    }
}

void StepCalculator::runDjikstra(string startvalve, int& countruns)
{
    Valve& v = findValve(startvalve);
//    if(countruns==9){
//        return;
//    }
    bool debug = false;
    if(debug){
        cout << "\n\nDJIKSTRA\n";
        cout << "Running with valve " << v.toString() << "\n";
    }
    if(v.shortestPath.size()==0 || v.shortestPath.back().valveName != v.valveName){
        v.shortestPath.insert(v.shortestPath.end(),v);
        if(debug){
            cout << "Added to shortest path " << v.toString() << "\n";
        }
    }
    //Mark start point as visited

    if(debug){
        cout << "Setting visited to true " << v.valveName << "\n";
    }
    v.visited = true;
    if(debug){
        Valve v2 = findValve(startvalve);
        cout << ((v2.visited)?" Visited " : " Not visited ") << v2.valveName << "\n";
    }
    if(debug){
        cout << "Adjacent valves:\n";
    }
    //Update distance and shortest paths to adjacent nodes
    for(auto adjacent : v.reachableValves){
        if(debug){
            cout << adjacent << "\n";
        }
        Valve& adj = findValve(adjacent);
        if(debug){
            cout << adj.toString() << "\n";
        }
        if(adj.distanceFromStart > v.distanceFromStart + 1){
            if(debug){
                cout << "updating distance and path ";
            }
            adj.distanceFromStart = v.distanceFromStart + 1;
            adj.shortestPath.clear();
            for(auto pathValve: v.shortestPath){
                adj.shortestPath.insert(adj.shortestPath.end(),findValve(pathValve.valveName));
            }
            adj.shortestPath.insert(adj.shortestPath.end(),findValve(adj.valveName));
            struct {
                bool operator() (Valve v1,Valve v2){
                    return v1.valveName < v2.valveName;
                }
            } uniqueByName;
            unique(adj.shortestPath.begin(), adj.shortestPath.end(), uniqueByName);
        }
        if(debug){
            cout << "\n";
        }
    }
    if(debug){
        cout << "Possible next valves:\n";
    }
    //Choose an unvisited path adjacent to visited paths with smallest distance
    vector<Valve*> visited;
    for(auto &valvev : valves){
        if(valvev.visited){
            visited.insert(visited.end(), &valvev);
        }
    }
    vector<Valve> possibleValves;
    for(auto& pathValve : visited){
        if(debug){
            cout << "Valve on path " << pathValve->valveName << "\n";
        }
        set<string> adjacentValves = pathValve->reachableValves;
        for(auto adjvalvStr : adjacentValves){
            if(debug){
                cout << "Checking adjacent valve " << adjvalvStr << "\n";
            }
            Valve& possibleValve = findValve(adjvalvStr);
            if(debug){
                cout << "Possible valve: " << possibleValve.valveName << "\n";
            }
            if(!possibleValve.visited){
                if(debug){
                    cout << possibleValve.valveName << " has not been visited\n";
                }
                possibleValves.insert(possibleValves.end(),possibleValve);
            }else{
                if(debug){
                    cout << possibleValve.valveName << " has already been visited\n";
                }
            }
        }
    }
    if(possibleValves.size()>0){
        //Which has shortest distance?
        Valve* nextValve = &possibleValves.front();
        if(debug)
        {
            cout << "Checking shortest distance\n";
            nextValve->toString();
        }
        for(auto pv : possibleValves){
            if(nextValve->distanceFromStart>pv.distanceFromStart){
                nextValve = &pv;
            }
        }
        countruns++;
        runDjikstra(nextValve->valveName, countruns);
    }
}
Valve& StepCalculator::findValve(string vName)
{
    for(vector<Valve>::iterator it = valves.begin(); it<valves.end(); it++){
        if(it->valveName==vName){
            Valve& vPoint = *it;
            return vPoint;
        }
    }
}

void StepCalculator::showValves()
{
    cout << "\n\nSHOW VALVES\n";
    for(auto v : valves){
        cout << v.toString() << "\n";
    }
    cout << "\n";
}
vector<Valve> StepCalculator::open(Valve v)
{
    vector<Valve> lOpened;
    for(auto &vcopy : v.shortestPath){
        if(!vcopy.opened && vcopy.flowrate>0){
            Valve& vToOpen = findValve(vcopy.valveName);
            cout << "Opening " << vToOpen.valveName << "\n";
            vToOpen.opened = true;
            lOpened.insert(lOpened.end(),vToOpen);
        }
    }
    return lOpened;
}

void StepCalculator::close(vector<Valve> v)
{
    for(auto vcopy : v){
        cout << "Closing " << vcopy.valveName << "\n";
        findValve(vcopy.valveName).opened = false;
    }
}
