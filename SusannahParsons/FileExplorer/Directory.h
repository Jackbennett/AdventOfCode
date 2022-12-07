#include <string>
#include <list>
#include "DirectoryObject.h"
#include "FileObject.h"

using namespace std;

class Directory : public DirectoryObject{

public:
    void addSubObject(DirectoryObject object);
    Directory getDirectory(string dirName);
    void listAll();
    int getSize();
private:
    list<DirectoryObject> objects;
};
