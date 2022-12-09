#ifndef TREE_H
#define TREE_H
class Tree{
public:
    Tree(int height);
    bool getVisible();
    void setVisible(bool visible);
    int getHeight();
    void setViewingDistances(int l, int r, int u, int d);
    int getScenicScore();
private:
    int height;
    bool visible;
    int viewingLeft;
    int viewingRight;
    int viewingUp;
    int viewingDown;
};
#endif
