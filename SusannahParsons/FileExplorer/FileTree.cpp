#include "FileTree.h"

FileTree::FileTree()
{
    string topDirName = "/";
    topDir = new Directory(topDirName);
    currentDir = topDir;
}

void FileTree::openDir(string dirName)
{
    auto dir = currentDir->getDirectory(dirName);
    if ( dir){
        Directory* newDir = dir.value();
        dirPath.push_front(currentDir);
        currentDir = newDir;
    }
}

void FileTree::addDir(string dirName)
{
    Directory* dir = new Directory(dirName);
    DirectoryObject* dirO = static_cast<DirectoryObject*>(dir);
    currentDir->addSubObject(dirO);
}

void FileTree::addFile(string fileName, int fileSize)
{
    FileObject* file = new FileObject(fileName, fileSize);
    DirectoryObject* dirO = static_cast<DirectoryObject*>(file);
    currentDir->addSubObject(dirO);
}

int FileTree::getSize()
{
    return currentDir->getSize();
}
void FileTree::listAll() const
{
    int fileSystemSize = 70000000;
    int requiredForUpdate = 30000000;
    int unusedSpace = fileSystemSize - topDir->getSize();
    int spaceNeeded = requiredForUpdate-unusedSpace;
    cout << "Top directory size\t" << topDir->getSize() << "\n";
    cout << "Unused space\t" << unusedSpace << "\n";
    cout << "Space needed\t" << spaceNeeded << "\n";
    Directory* bestToDelete = new Directory("Empty");
    cout << "Listing all files and directories in " << currentDir->name() << "\n";
    currentDir->listAll();
    list<Directory*> dirList;
    currentDir->returnDirsOfSize(spaceNeeded, &dirList);
    for_each(dirList.begin(), dirList.end(), [&bestToDelete, spaceNeeded](Directory* o) mutable {
             if(bestToDelete->getSize()==0){
                bestToDelete = o;
             }else{
                 int newDiff = o->getSize()-spaceNeeded;
                 int oldDiff = bestToDelete->getSize()-spaceNeeded;
                 if(newDiff<oldDiff){
                    bestToDelete = o;
                 }
             }
     });
     cout << "Best directory to delete is: " << bestToDelete->name() << "\tsize: " << bestToDelete->getSize();
}
void FileTree::openTopDir()
{
    //Empty dir path
    dirPath.erase(dirPath.begin(), dirPath.end());
    currentDir = topDir;
}

void FileTree::upDir()
{
    Directory* parent = dirPath.front();
    dirPath.pop_front();
    currentDir = parent;
}
