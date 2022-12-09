#include "Tree.h";

Tree::Tree(int height)
:height(height), visible(false)
{

}

bool Tree::getVisible()
{
    return visible;
}

void Tree::setVisible(bool vis)
{
    visible = vis;
}
int Tree::getHeight()
{
    return height;
}
void Tree::setViewingDistances(int l, int r, int u, int d)
{
    viewingLeft = l;
    viewingRight = r;
    viewingDown = d;
    viewingUp = u;
}
int Tree::getScenicScore()
{
    return viewingLeft * viewingRight * viewingDown * viewingUp;
}

