#ifndef FILETREE_H
#define FILETREE_H
#include "Directory.h"
#include "FileObject.h"
#include <deque>
#include <string>
#include <iostream>
using namespace std;
class FileTree{
public:
    FileTree();
    void openDir(string dirName);
    void addDir(string dirName);
    void addFile(string fileName, int fileSize);
    void listAll() const;
    int getSize();
    void openTopDir();
    void upDir();
private:
    Directory* topDir;
    deque<Directory*> dirPath;
    Directory* currentDir;
};
#endif
