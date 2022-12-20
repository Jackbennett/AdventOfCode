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
                v->name = stringItem;
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
    //While there are still unopened valves
    uint64_t currentPressure=0;
    uint64_t totalPressure=0;
    int time=1;
    Valve* nextValve = new Valve(getNextValve("AA"));
    while(unopenedValves() && time<30){
        for(int minutes=1; minutes<nextValve->timeCost(); minutes++){
            cout << "Time " << time << " Moved\nCurrent pressure: " << currentPressure << "\n";
            totalPressure = totalPressure + currentPressure;
            time++;
        }
        cout << "Time " << time << " Opening valve " << nextValve->toString() << "\nCurrent pressure: " << currentPressure << "\n";
        totalPressure = totalPressure + currentPressure;
        currentPressure = currentPressure + nextValve->benefit();
        findValve(nextValve->name).opened = true;
        time++;
        nextValve = new Valve(getNextValve(string(nextValve->name)));
    }
    if(time<30){
        while(time!=31){
    //        cout << "Time " << time << " Current pressure: " << currentPressure << "\n";
            totalPressure = totalPressure + currentPressure;
            time++;
        }
    }
    cout << "Finished running. Total pressure released: " << totalPressure << "\n";

}

Valve& StepCalculator::getNextValve(string startValve)
{
    bool debug = false;
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
    runDjikstra(vstart.name,countRuns);
    if(debug){
        cout << "Shortest paths found, sorting by time cost\n";
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
                cout << "Valve won the comparison: " << v.toString() << "\nBest valve is now " << bestValve->toString() << "\n";
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
        if(!v.opened && v.benefit()>0){
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
        cout << "Running with valve " << v.toString() << "\n";
    }
    if(v.shortestPath.size()==0 || v.shortestPath.back() != v.name){
        v.shortestPath.insert(v.shortestPath.end(),v.name);
        if(debug){
            cout << "Added to shortest path " << v.toString() << "\n";
        }
    }
    //Mark start point as visited

    if(debug){
        cout << "Setting visited to true " << v.name << "\n";
    }
    v.visited = true;
    if(debug){
        Valve v2 = findValve(startvalve);
        cout << ((v2.visited)?" Visited " : " Not visited ") << v2.name << "\n";
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
                adj.shortestPath.insert(adj.shortestPath.end(),string(pathValve));
            }
            adj.shortestPath.insert(adj.shortestPath.end(),string(adjacent));
            unique(adj.shortestPath.begin(), adj.shortestPath.end());
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
            cout << "Valve on path " << pathValve->name << "\n";
        }
        set<string> adjacentValves = pathValve->reachableValves;
        for(auto adjvalvStr : adjacentValves){
            if(debug){
                cout << "Checking adjacent valve " << adjvalvStr << "\n";
            }
            Valve& possibleValve = findValve(adjvalvStr);
            if(debug){
                cout << "Possible valve: " << possibleValve.name << "\n";
            }
            if(!possibleValve.visited){
                if(debug){
                    cout << possibleValve.name << " has not been visited\n";
                }
                possibleValves.insert(possibleValves.end(),possibleValve);
            }else{
                if(debug){
                    cout << possibleValve.name << " has already been visited\n";
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
        runDjikstra(nextValve->name, countruns);
    }
}
Valve& StepCalculator::findValve(string vName)
{
    for(vector<Valve>::iterator it = valves.begin(); it<valves.end(); it++){
        if(it->name==vName){
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
