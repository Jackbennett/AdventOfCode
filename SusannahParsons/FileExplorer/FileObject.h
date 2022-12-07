#include <string>
#include "DirectoryObject.h"
using namespace std;

class FileObject: public DirectoryObject{
public:
    FileObject(string name, int fs);
    int getSize();
private:
    int fileSize;
