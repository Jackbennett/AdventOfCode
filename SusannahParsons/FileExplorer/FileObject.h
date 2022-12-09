#ifndef FILEOBJECT_H
#define FILEOBJECT_H
#include <string>
#include "DirectoryObject.h"
using namespace std;

class FileObject: public DirectoryObject{
public:
    FileObject(){};
    FileObject(string name);
    FileObject(string name, int fs);
    ~FileObject(){};
    int getSize() const override;
private:
    int fileSize;
};
#endif
