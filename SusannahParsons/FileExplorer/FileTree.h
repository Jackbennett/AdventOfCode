#include "Directory.h"
#include "FileObject.h"
#include <deque>
using namespace std;

class FileTree{
public:
    FileTree();
    void openDir(string dirName);
    void addDir(string dirName);
    void addFile(string fileName, fileSize);
    void listAll();
    int getSize();
private:
    Directory topDir;
    deque<Directory> dirPath;
    Directory currentDir;
}
