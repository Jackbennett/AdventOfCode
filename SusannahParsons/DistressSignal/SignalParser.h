#ifndef HEATMAP_H
#define HEATMAP_H
#include <string>
#include <iostream>
#include <fstream>
#include "PacketList.h"
#include "PacketPair.h"
#include <algorithm>
#include <variant>
using namespace std;

class SignalParser{
public:
    SignalParser(string filename);
private:
    vector<PacketPair> signal;
};
#endif
