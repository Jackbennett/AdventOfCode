#include "FileTree.h"

FileTree::FileTree()
{
    topDir = newDirectory("/");
    currentDir = topDir;
}

void FileTree::openDir(string dirName)
{
    Directory newDir = currentDir.getDirectory(dirName);
    dirPath.push_front(currentDir);
    currentDir = newDir;
}

void FileTree::addDir(string dirName)
{
    currentDir.addSubObject(new Directory(dirName));
}

void FileTree::addFile(string fileName, fileSize)
{
    currentDir.addSubObject(new File(fileName, fileSize));
}

int FileTree::getSize()
{
    return currentDir.getSize();
}
void FileTree::listAll()
{
    currentDir.listAll();
}
