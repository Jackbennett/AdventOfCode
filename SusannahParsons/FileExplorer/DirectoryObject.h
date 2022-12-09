#ifndef DIRECTORYOBJECT_H
#define DIRECTORYOBJECT_H
#include <string>

using namespace std;

class DirectoryObject{
public:
    DirectoryObject(){};
    DirectoryObject(string name);
    ~DirectoryObject(){};
    enum TYPE{
        FILE,
        DIRECTORY
    };
    virtual int getSize() const;
    virtual TYPE getType() const;
    string name() const;
private:
    string m_name;
protected:
    TYPE type;
};
#endif
