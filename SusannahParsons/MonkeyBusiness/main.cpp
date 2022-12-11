#include <string>
#include "KeepAway.h"
using namespace std;

int main()
{
//    string file("testInput.txt");
    string file("monkeyInput.txt");
    KeepAway ka(file);
    for(int i=0; i<20; i++){
        ka.playRound();
    }
    ka.showState();
    return 0;
}
