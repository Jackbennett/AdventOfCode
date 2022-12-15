#include "SignalParser.h"

bool sortPacketListFunc (PacketList i,PacketList j) {
    //Pair the two up
    PacketPair pp;
    pp.left = i;
    pp.right = j;
    variant<bool, size_t> ppcorrect = pp.correctOrder();
    if(holds_alternative<bool>(ppcorrect)){
        return get<bool>(ppcorrect);
    }else{
        //They match exactly
        return true;
    };
}

SignalParser::SignalParser(string filename)
{
    ifstream inputFile(filename);
    string fileLine;
    int packetNum = 1;
    vector<PacketList> fullPacketList;
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
        fullPacketList.insert(fullPacketList.end(),PacketList(fileLine));
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

    //Day 2 add 2 extra divider packets
    fullPacketList.insert(fullPacketList.end(),PacketList("[[2]]"));
    fullPacketList.insert(fullPacketList.end(),PacketList("[[6]]"));
    //Sort the list
    sort(fullPacketList.begin(), fullPacketList.end(), sortPacketListFunc);
    //Now iterate to find the indexes of the divider packets and multiply them together
    int dividerIndexMultiple(1);
    int listIndex(1);
    for (auto & pl : fullPacketList) {
        if(pl.originalPacket.compare ("[[2]]") == 0 || pl.originalPacket.compare ("[[6]]") == 0){
            dividerIndexMultiple *= listIndex;
        }
        listIndex++;
    }
    cout << "Part 2 answer: " << dividerIndexMultiple << "\n";

}
