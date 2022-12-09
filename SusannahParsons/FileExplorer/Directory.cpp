#include "Directory.h"

Directory::Directory(string name)
:DirectoryObject(name)
{
    type = DIRECTORY;
}

Directory::Directory(const Directory& dir)
:DirectoryObject(dir.name())
{
    type = DIRECTORY;
    list<DirectoryObject*> orig = dir.getObjects();
    for (list<DirectoryObject*>::const_iterator it = orig.begin(); it != orig.end(); ++it){
        objects.insert(objects.end(),*it);
    }
}

void Directory::addSubObject(DirectoryObject* object)
{
    //Add file or directory to the list
    objects.insert(objects.begin(),object);
}

int Directory::getSize() const
{
    int totalSize = 0;
    for (list<DirectoryObject*>::const_iterator it = objects.begin(); it != objects.end(); ++it){
        DirectoryObject* o = *it;
        totalSize += o->getSize();
    }
     return totalSize;
}
optional<Directory*> Directory::getDirectory(string dirName)
{
    for (list<DirectoryObject*>::iterator it = objects.begin(); it != objects.end(); ++it){
        DirectoryObject* o = *it;
        if(o->name()==dirName){
            Directory* responsePointer = static_cast<Directory*>(o);
            return responsePointer;
        }
    }
    return nullopt;
}

void Directory::listAll(list<Directory*>* smallDirs) const
{
    for_each(objects.begin(), objects.end(), [smallDirs](DirectoryObject* o)mutable {
             cout << o->name() << "\t\t\tsize: " << o->getSize() << "\n";
             if(o->getType()==DIRECTORY){
                if(static_cast<Directory*>(o)->getSize()<=100000){
                    smallDirs->insert(smallDirs->begin(),static_cast<Directory*>(o));
                }
                static_cast<Directory*>(o)->listAll(smallDirs);
             }
     });
}
list<DirectoryObject*> Directory::getObjects() const
{
    return objects;
}
list<Directory*> Directory::getSubDirectories()
{
    list<Directory*> result;
    for (list<DirectoryObject*>::const_iterator it = objects.begin(); it != objects.end(); ++it){
        DirectoryObject* o = *it;
        if(o->getType()==DIRECTORY){
            result.insert(result.begin(), static_cast<Directory*>(o));
        }
    }
}
