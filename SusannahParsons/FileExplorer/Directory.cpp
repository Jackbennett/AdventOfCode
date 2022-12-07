#include "Directory.h"
void Directory::addSubObject(DirectoryObject object)
{
    if (dynamic_cast<FileObject*>(object) != nullptr){
        //Must be a file
        FileObject f = dynamic_cast<FileObject*>(object);
        int currentSize = getSize();
        setSize(currentSize + f.getSize());
    }
    //Add file or directory to the list
    objects.insert(object);
}

int Directory::getSize()
{
    int totalSize = 0;
    for_each(objects.begin(), objects.end(), [](const DirectoryObject o) {
                totalSize += o.getSize();
             });
     return totalSize;
}
Directory Directory::getDirectory(string dirName)
{
    for_each(objects.begin(), objects.end(), [](const DirectoryObject o) {
        if (dynamic_cast<Directory*>(o) != nullptr){
                Directory d = dynamic_cast<Directory*>(o);
                if(d.name()==dirName){
                    return d;
                }
             }
     });
}
void Directory::listAll()
{
    for_each(objects.begin(), objects.end(), [](const DirectoryObject o) {
             cout << o.name() << "\n";
     });
}
