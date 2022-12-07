#include <string>

using namespace std;

class DirectoryObject{
public:
    DirectoryObject(string name);
    int getSize();
    string name();
private:
    string m_name;
};
