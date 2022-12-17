#ifndef PACKETLIST_H
#define PACKETLIST_H
#include <vector>
#include <string.h>
#include <string>
#include <variant>
#include <iostream>
#include <deque>
using namespace std;
class PacketList{
public:
    PacketList();
    PacketList(string pl);
    string originalPacket;
    vector<string> listContent;
    variant<int, string, size_t> getItem();
private:
    deque<string> listContentCopy;

    void getListContent(string packet);
    void extractInt(string* packetContent);
    void extractPacketListItem(string* packetContent);
};
#endif // PACKETLIST_H
