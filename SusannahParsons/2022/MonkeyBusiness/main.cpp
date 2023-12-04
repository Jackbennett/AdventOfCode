#include <string>
#include "KeepAway.h"
#include <iostream>
using namespace std;

int main()
{
//    string file("testInput.txt");
    string file("monkeyInput.txt");
    KeepAway ka(file);
    for(int i=0; i<10000; i++){
//            cout << "Round: " << i << "\n";
        ka.playRound();
    }
    ka.showState();
    return 0;
}
