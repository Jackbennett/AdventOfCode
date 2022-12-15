#include "SignalParser.h"

SignalParser::SignalParser(string filename)
{
    ifstream inputFile(filename);
    string fileLine;
    int packetNum = 1;
    while(getline(inputFile, fileLine)){
        if(fileLine==""){
            packetNum = 1;
            continue;
        }
        if(packetNum==1){
            signal.insert(signal.end(),PacketPair(fileLine));
        }else{
            signal.back().two = fileLine;
        }
        packetNum++;
    }
    for (auto & pp : signal) {
            cout << pp.toString() << "\n";
    }
}

bool SignalParser::compare(PacketPair pp)
{

}
