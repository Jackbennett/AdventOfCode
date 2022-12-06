#include <iostream>
#include <fstream>
#include "CommsDevice.h"

using namespace std;

runFileProcessor(ifstream & inputFile, string fileContent){
    CommsDevice comms;
    cout << "Comms Device initialized\n";
    while (getline (inputFile, fileContent)) {
            //Iterate the char in the string
            for(char& signalChar : fileContent) {
                    cout << signalChar;
                comms.addSignal(signalChar);
                if(comms.getStartOfMessageMarkerPosition()>0){
                    break;
                }
            }
    }
    cout << "\nStart of packet marker is at pos " << comms.getStartOfPacketMarkerCompletePosition();
    cout << "\nStart of message marker is at pos " << comms.getStartOfMessageMarkerPosition();
    return 0;
}
int main()
{
    string fileContent;
    // Read from the text file
    ifstream inputFile("comsInput.txt");
    runFileProcessor(inputFile, fileContent);
    // Close the file
    inputFile.close();
    return 0;
}
