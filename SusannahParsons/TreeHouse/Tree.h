#ifndef TREE_H
#define TREE_H
class Tree{
public:
    Tree(int height);
    bool getVisible();
    void setVisible(bool visible);
    int getHeight();
private:
    int height;
    bool visible;
};
#endif
