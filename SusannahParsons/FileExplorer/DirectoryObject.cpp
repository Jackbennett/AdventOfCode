#include "DirectoryObject.h"

DirectoryObject::DirectoryObject(string name)
:m_name(name)
{}

string DirectoryObject::name()
{
    return m_name;
}

int DirectoryObject::getSize()
{
    return 0;
}
