#include "File.h"

FileObject::FileObject(string name, int fs)
: DirectoryObject(name)
{
    fileSize = fs;
}

int FileObject::getSize()
{
    return fileSize;
}

