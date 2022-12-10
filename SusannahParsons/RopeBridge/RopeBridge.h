#ifndef ROPEBRIDGE_H
#define ROPEBRIDGE_H
#include <set>
#include <tuple>
#include <cstdlib>
#include <iostream>
#include <type_traits>
using namespace std;
struct place {
    place(int x1, int y1)
    :x(x1), y(y1)
    {
    }
    int x;
    int y;
    friend bool operator<(const place& l, const place& r)
    {
        return std::tie(l.x, l.y)
             < std::tie(r.x, r.y);
    }
};

class RopeBridge{
public:
    RopeBridge();
    void moveHead(char direction, int moves);
    int numberTailPlaces();
    void testComparePlaces();
private:
    void moveTail();
    place head;
    place tail;
    static constexpr bool comparePlaces = [](place a, place b) {
        if(a.x==b.x){
                cout << "X is the same, returning y<y\n";
            return a.y<b.y;
        }else{
            cout << "Returning x<x\n";
            return a.x<b.x;
        }
    };
    set<place> tailPlaces;
};
#endif
