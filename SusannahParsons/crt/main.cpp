#include <iostream>
#include "crt.h"
using namespace std;

runFileProcessor(string file){
    CathodeRayTube mycrt(file);
    mycrt.runProgram();
    return 0;
}
int main()
{
    string fileContent;

    // Read from the text file
//    runFileProcessor("testInput.txt");
    runFileProcessor("crtInput.txt");
    return 0;
}
