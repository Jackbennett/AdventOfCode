#ifndef TREEQUAD_H
#define TREEQUAD_H
#include "Tree.h"
#include <deque>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;
class TreeQuad{
public:
    TreeQuad();
    void initColumns(int rowSize);
    void addTree(int treeSize, bool newRow, int col);
    void markVisibility();
    list<Tree*>* getVisibleTrees();
private:
    vector<deque<Tree*>*> columns;
    vector<deque<Tree*>*> rows;
    void markVisibilityInLine(deque<Tree*>* line);
};
#endif
