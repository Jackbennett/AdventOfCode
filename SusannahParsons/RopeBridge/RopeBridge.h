#ifndef ROPEBRIDGE_H
#define ROPEBRIDGE_H
#include <set>
#include <tuple>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <vector>
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
    void showPosition();
    void testComparePlaces();
private:
    void moveRope();
    vector<place> rope;
    set<place> tailPlaces;
};
#endif
