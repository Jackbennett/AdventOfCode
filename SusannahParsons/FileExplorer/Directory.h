#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "FileObject.h"
#include <string>
#include <list>
#include "DirectoryObject.h"
#include <iostream>
#include <algorithm>
#include <optional>

using namespace std;

class Directory : public DirectoryObject{

public:
    Directory(){};
    Directory(string name);
    Directory(const Directory& rhs);
    void addSubObject(DirectoryObject* object);
    optional<Directory*> getDirectory(string dirName);
    list<Directory*> getSubDirectories();
    void listAll() const;
    void returnDirsOfSize(int sizeNeeded, list<Directory*>* dirs) const;
    int getSize() const override;
    list<DirectoryObject*> getObjects() const;
private:
    list<DirectoryObject*> objects;//Must be pointers, as you can't store child information in parent class
};
#endif
