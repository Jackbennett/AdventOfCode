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
                string dirName = fileContent.substr(openDirPos+5);
                if(dirName=="/"){
                    ft.openTopDir();
                }else if(dirName==".."){
                    ft.upDir();
                }else{
                    ft.openDir(dirName);
                }
            }
            size_t lsDirPos = fileContent.find("$ ls");
            if(lsDirPos != string::npos){
                //This is a list command
                lastCommand = "ls";
            }
        }else{
            //Display output
            if(fileContent.substr(0,3)=="dir"){
                //This is a directory
                string dirName = fileContent.substr(4);
                ft.addDir(dirName);
            }else{
                //It's a file
                size_t spacePos = fileContent.find(" ");
                int fileSize = stoi(fileContent.substr(0, spacePos));
                string fileName = fileContent.substr(spacePos+1);
                ft.addFile(fileName, fileSize);
            }
        }
    }
    cout << "File system initialized\n";
    ft.openTopDir();
    ft.listAll();
    return 0;
}
int main()
{
    string fileContent;
    // Read from the text file
//    ifstream inputFile("testInput.txt");
    ifstream inputFile("dirInput.txt");
    runFileProcessor(inputFile, fileContent);
    // Close the file
    inputFile.close();
    return 0;
}
