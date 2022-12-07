#include <iostream>
#include <fstream>
#include "FileTree.h"

using namespace std;

runFileProcessor(ifstream & inputFile, string fileContent){
    FileTree ft;
    string lastCommand;
    while (getline (inputFile, fileContent)) {
        size_t commandPos = fileContent.find("$");
        if(commandPos != string::npos){
            //Iterate the command output
            size_t openDirPos = fileContent.find("$ cd ");
            if(openDirPos != string::npos){
                //This is an open directory command.
                lastCommand = "cd";
                string dirName = fileContent.substr(openDirPos);
                cout << "Directory to open: " << dirName << "\n";
            }
            size_t lsDirPos = fileContent.find("$ ls");
            if(lsDirPos != string::npos){
                //This is a list command
                lastCommand = "ls";
            }
        }else{
            //Display output
            if(fileContent.substr(0,2)=="dir"){
                //This is a directory

            }
        }
    }
    return 0;
}
int main()
{
    string fileContent;
    // Read from the text file
    ifstream inputFile("dirInput.txt");
    runFileProcessor(inputFile, fileContent);
    // Close the file
    inputFile.close();
    return 0;
}
