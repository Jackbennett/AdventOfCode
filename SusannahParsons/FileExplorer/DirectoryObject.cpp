#include "DirectoryObject.h"

DirectoryObject::DirectoryObject(string name)
:m_name(name)
{}

string DirectoryObject::name() const
{
    return m_name;
}

int DirectoryObject::getSize() const
{
    return 0;
}
DirectoryObject::TYPE DirectoryObject::getType() const
{
    return type;
}
