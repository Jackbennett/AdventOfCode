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
    cout << "Listing all files and directories in " << currentDir->name() << "\n";
    list<Directory*> smallDirs;
    currentDir->listAll(&smallDirs);
    cout << "The small directories are:\n";
    int  totalSmallDirSize = 0;
    for_each(smallDirs.begin(), smallDirs.end(), [&totalSmallDirSize](Directory* o) mutable {
             cout << o->name() << "\t\t\tsize: " << o->getSize() << "\n";
             totalSmallDirSize += o->getSize();
     });
     cout << "Total small dir size: " << totalSmallDirSize;
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
