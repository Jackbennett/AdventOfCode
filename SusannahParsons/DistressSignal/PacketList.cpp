#include "PacketList.h"
PacketList::PacketList()
{

}

PacketList::PacketList(string pl)
{
    getListContent(pl);
}

variant<int, string, size_t> PacketList::getItem()
{
    if(listContentCopy.size()==0){
        return string::npos;
    }
    string item = listContentCopy.front();
    listContentCopy.pop_front();
    if(item[0]=='['){
        //This is a list
        return item;
    }else{
        return stoi(item);
    }
}

void PacketList::getListContent(string packet)
{
    string packetContent = packet.substr(1,packet.size()-2);
    if(packetContent.size()==0){
        //There was nothing in the list
        return;
    }
    int stringPos = 0;
    char& packChar = packetContent[stringPos];
    while(packetContent.size()>0){
        if(packChar=='['){
            //Start list item
            extractPacketListItem(&packetContent);
        }else if(packChar==','){
            //content item separator
            packetContent.erase(0,1);
        }else {
            extractInt(&packetContent);
        }
        packChar = packetContent[stringPos];
    }
    return;
}

void PacketList::extractInt(string* packetContent)
{
    //int, will be other-ended by either a commma or right bracket or the end of the string.
    size_t found = packetContent->find_first_of(",]");
    if(found==string::npos){
        found = packetContent->size();
    }
    vector<char> packInt;
    for(int i=0; i<found; i++){
        char packChar = packetContent->at(i);
        packInt.insert(packInt.end(),packChar);
    }
    string packetInt(packInt.begin(), packInt.end());
    listContent.insert(listContent.end(), packetInt);
    listContentCopy.insert(listContentCopy.end(), packetInt);
    //Remove from packetContent
    int amountToRemove = packetInt.size();
    packetContent->erase(0,amountToRemove);
}

void PacketList::extractPacketListItem(string* packetContent)
{
    int lb(0);
    int rb(0);
    vector<char> pl;
    for(int i=0; i<packetContent->size(); i++){
        char packChar = packetContent->at(i);
        if(packChar=='['){
            lb++;
        }
        if(packChar==']'){
            rb++;
        }
        pl.insert(pl.end(),packChar);
        if(lb==rb){
            break;
        }
    }
    string packetlist(pl.begin(), pl.end());
    listContent.insert(listContent.end(), packetlist);
    listContentCopy.insert(listContentCopy.end(), packetlist);
    //Remove from packetContent
    int amountToRemove = packetlist.size();
    packetContent->erase(0,amountToRemove);
}

