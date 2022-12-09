#include "FileObject.h"

FileObject::FileObject(string name, int fs)
: DirectoryObject(name)
{
    type = FILE;
    fileSize = fs;
}

int FileObject::getSize() const
{
    return FileObject::fileSize;
}




