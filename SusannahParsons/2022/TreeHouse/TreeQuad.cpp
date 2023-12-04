#include "TreeQuad.h"

TreeQuad::TreeQuad()
{
    cout << "Instantiated tree quad\n";
}
void TreeQuad::initColumns(int rowSize)
{
    //Initialise columns
    for(int count =0; count<rowSize; count++){
        deque<Tree*>* column = new deque<Tree*>();
        columns.insert(columns.begin(),column);
    }
}

void TreeQuad::addTree(int treeSize, bool newRow, int col)
{
    deque<Tree*>* row;
    if(newRow){
        row = new deque<Tree*>();
        rows.insert(rows.end(),row);
    }
    row = rows.back();
    Tree* tree = new Tree(treeSize);
    row->push_back(tree);
    columns[col]->push_back(tree);
}

void TreeQuad::markVisibility()
{
    for_each(rows.begin(), rows.end(), [this](deque<Tree*>* row) mutable {
             markVisibilityInLine(row);
    });
    for_each(columns.begin(), columns.end(), [this](deque<Tree*>* column) mutable {
             markVisibilityInLine(column);
    });
}

list<Tree*>* TreeQuad::getVisibleTrees()
{
    list<Tree*>* visibleTrees = new list<Tree*>();
    for_each(rows.begin(), rows.end(), [visibleTrees,this](deque<Tree*>* row) mutable {
        for_each(row->begin(), row->end(), [visibleTrees](Tree* tree) mutable {
                 if(tree->getVisible()){
                    visibleTrees->insert(visibleTrees->begin(),tree);
                 }
        });
    });
    return visibleTrees;
}

void TreeQuad::markVisibilityInLine(deque<Tree*>* linePointer)
{
    //Iterate forwards and then backwards
    deque<Tree*> line = *linePointer;
    int highestTree = -1;
    for (int i = 0; i < line.size(); i++) {
        Tree* tree = line[i];
        if(tree->getHeight()>highestTree){
            tree->setVisible(true);
            highestTree = tree->getHeight();
        }
    }
    highestTree = -1;
    for (int i = line.size() - 1; i >= 0; i--) {
        Tree* tree = line[i];
        if(tree->getHeight()>highestTree){
            tree->setVisible(true);
            highestTree = tree->getHeight();
        }
    }
}

void TreeQuad::calculateScenicScores()
{
    int totalRows = rows.size();
    int totalColumns = columns.size();
    int greatestScenicScore = 0;
    //Iterate rows
    for(int rowIndex = 0; rowIndex<totalRows; rowIndex++){
        //Iterate columns
        for(int colIndex = 0; colIndex<totalColumns; colIndex++){
            //Now we have rowIndex, colIndex to identify a tree.
            deque<Tree*> row = *rows[rowIndex];
            deque<Tree*> col = *columns[colIndex];
            Tree* mainTree = row[colIndex];
            int viewDistanceLeft = getViewDistance(row,colIndex-1,-1,mainTree);
            int viewDistanceRight = getViewDistance(row,colIndex+1,columns.size(),mainTree);
            int viewDistanceUp = getViewDistance(col, rowIndex-1, -1, mainTree);
            int viewDistanceDown = getViewDistance(col, rowIndex+1, rows.size(), mainTree);
            mainTree->setViewingDistances(viewDistanceLeft, viewDistanceRight, viewDistanceUp, viewDistanceDown);
            int scenicScore = mainTree->getScenicScore();
            if(scenicScore>greatestScenicScore){
                greatestScenicScore = scenicScore;
            }
        }
    }
    cout << "Greatest scenic score\t" << greatestScenicScore << "\n";
}

Tree* TreeQuad::getTree(int rowIndex, int colIndex)
{
    deque<Tree*> row = *rows[rowIndex];
    return row[colIndex];
}


int TreeQuad::getViewDistance(deque<Tree*> line, int startIndex, int endIndex, Tree* mainTree)
{
    int viewDistance = 0;
    bool backwards = startIndex>endIndex;
    for(int countLeft = startIndex; backwards ? countLeft>endIndex : countLeft<endIndex; backwards ? countLeft-- : countLeft++){
        Tree* tree = line[countLeft];
        if(tree->getHeight()<mainTree->getHeight()){
            viewDistance++;
        }else{
            viewDistance++;
            break;
        }
    }
    return viewDistance;
}
