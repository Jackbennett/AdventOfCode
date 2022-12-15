#ifndef HEATMAP_H
#define HEATMAP_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct PacketPair{
    PacketPair(string newOne)
    :one(newOne){};
    string one;
    string two;
    string toString()const{
        return "(" + one + "   ,   " + two + ")";
    };
};
class SignalParser{
public:
    SignalParser(string filename);
private:
    vector<PacketPair> signal;
    bool compare(PacketPair pp);

    //Overloaded method. Non-arrays return false, arrays return true
//    template <typename T, size_t N>
//    bool testIfArray(const T (&arr)[N]);
//    template <typename T>
//    bool testIfArray(const T& );
};
#endif
