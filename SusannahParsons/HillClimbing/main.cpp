#include <iostream>
#include "HeatMap.h"
using namespace std;

int main()
{
    HeatMap h("testInput.txt");
//    HeatMap h("heatmapInput.txt");
    h.calculateReverseJourney();
    return 0;
}
