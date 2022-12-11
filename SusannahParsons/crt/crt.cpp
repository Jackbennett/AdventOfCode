#include "crt.h"

CathodeRayTube::CathodeRayTube(string file)
:inputFile(file), X(1), cycle(1), timeToCheckSignalStrength(1), periodCheckSignalStrength(40)
{

}

void CathodeRayTube::runProgram()
{
    while (getline (inputFile, fileContent)) {
            if(fileContent.find("noop") != string::npos){
                noop();
            }else if(fileContent.find("addx") != string::npos){
                int amount = stoi(fileContent.substr(5));
                addx(amount);
            }
    }
    cout << "\nTotal signal strength samples: " << getTotalSignalStrengthSamples() << "\n";
    // Close the file
    inputFile.close();
}

void CathodeRayTube::noop()
{
    runCycle();
}

void CathodeRayTube::addx(int amount)
{
    runCycle();
    runCycle();
    X = X+amount;
}


void CathodeRayTube::runCycle()
{
    if(cycle==timeToCheckSignalStrength){
//        cout << "Cycle: " << cycle << " signalStrength: " << getSignalStrength() << "\n";
        strengthSamples.insert(strengthSamples.begin(),getSignalStrength());
        timeToCheckSignalStrength = timeToCheckSignalStrength + periodCheckSignalStrength;
        cout << "\n";
    }
    if((cycle-1)%40==X || (cycle-1)%40==(X-1) || (cycle-1)%40==(X+1)){
        cout << "#";
    }else{
        cout << " ";
    }
    cycle++;
}

int CathodeRayTube::getSignalStrength()
{
    return cycle * X;
}

int CathodeRayTube::getTotalSignalStrengthSamples()
{
    int totals = 0;
    for(int i=0; i<strengthSamples.size(); i++){
        totals = totals + strengthSamples[i];
    }
    return totals;
}


