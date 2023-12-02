#ifndef PACKETPAIR_H
#define PACKETPAIR_H
#include <string>
#include <variant>
#include <iostream>
#include "PacketList.h"
using namespace std;
class PacketPair{
public:
    PacketPair();
    PacketPair(string newLeft);
    PacketList left;
    PacketList right;
    variant<bool, size_t> correctOrder();
    string toString()const;
};
#endif
