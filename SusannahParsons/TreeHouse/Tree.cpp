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
