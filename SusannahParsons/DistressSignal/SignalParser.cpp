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
            signal.back().right = PacketList(fileLine);
        }
        packetNum++;
    }
    int packetPairIndex = 1;
    int totalCorrectIndex = 0;
    for (auto & pp : signal) {
        variant<bool, size_t> ppcorrect = pp.correctOrder();
        if(holds_alternative<bool>(ppcorrect)){
            if(get<bool>(ppcorrect)){
                totalCorrectIndex += packetPairIndex;
            }else{
            }
        }else{
        };
        packetPairIndex++;
    }
    cout << "Part 1 answer: " << totalCorrectIndex << "\n";
}
