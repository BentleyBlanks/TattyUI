#include <TattyUI/test/fangcun/fcQuadTree.h>
#include <TattyUI/test/fangcun/fcCircle.h>
using namespace std;

fcQuadTree::fcQuadTree(int depth, fcRectangle bounds) :depth(depth), bounds(bounds)
{
    nodes.resize(4);
    for(auto node : nodes)
        node = NULL;
}

void fcQuadTree::clear()
{
    vector<fcCircle*>::iterator it;
    for(it = objects.begin(); it != objects.end();)
    {
        it = objects.erase(it);
    }

    for(auto node : nodes)
    {
        if(node != NULL)
        {
            node->clear();
            node = NULL;
        }
    }
}

void fcQuadTree::split()
{
    fcQuadTree* node = NULL;

    int halfWidth = bounds.getWidth() / 2;
    int halfHeight = bounds.getHeight() / 2;
    int x = bounds.getX();
    int y = bounds.getY();

    node = new fcQuadTree(depth + 1, fcRectangle(x + halfWidth, y, halfWidth, halfHeight));
    nodes[FC_TOP_RIGHT] = node;

    node = new fcQuadTree(depth + 1, fcRectangle(x, y, halfWidth, halfHeight));
    nodes[FC_TOP_LEFT] = node;

    node = new fcQuadTree(depth + 1, fcRectangle(x, y + halfHeight, halfWidth, halfHeight));
    nodes[FC_BOTTOM_LEFT] = node;

    node = new fcQuadTree(depth + 1, fcRectangle(x + halfWidth, y + halfHeight, halfWidth, halfHeight));
    nodes[FC_BOTTOM_RIGHT] = node;
}

// 该对象在当前结点中划分的区号
// 
//       PARENT(-1)
//
//  TL(1)   |    TR(0)
//----------|-----------
//  BL(2)   |    BR(3)
int fcQuadTree::getIndex(fcCircle* circle)
{
    // -1代表该对象无法完全放入子空间中 存放于父节点中
    int index = FC_PARENT;

    int centerX = bounds.getX() + bounds.getWidth() / 2;
    int centerY = bounds.getY() + bounds.getHeight() / 2;

    bool bTop = circle->getY() + circle->getHeight() < centerY;
    bool bBottom = circle->getY() > centerY;

    // 对象完全处于左半边区域
    if(circle->getX() + circle->getWidth() < centerX)
    {
        // 上方
        if(bTop)
            index = FC_TOP_LEFT;
        // 下方
        else if(bBottom)
            index = FC_BOTTOM_LEFT;
    }
    else if(circle->getX() > centerX)
    {
        // 上方
        if(bTop)
            index = FC_TOP_RIGHT;
        // 下方
        else if(bBottom)
            index = FC_BOTTOM_RIGHT;
    }

    return index;
}

void fcQuadTree::insert(fcCircle* circle)
{
    // 已划分子空间
    if(objects.size() > 0)
    {
        int index = getIndex(circle);

        if(index != -1)
        {
            nodes[index]->insert(circle);
        }
    }

    objects.push_back(circle);

    // 超过最大存放量且不超过最大深度
    if(objects.size() > FC_QUADTREE_MAX_OBJECTS && depth < FC_QUADTREE_MAX_DEPTH)
    {
        // 未分割子空间
        if(nodes.size() == 0)
            split();

        // 将当前对象集划分给子空间
        vector<fcCircle*>::iterator it;
        for(it = objects.begin(); it != objects.end();)
        {
            int index = getIndex(*it);
            if(index != -1)
            {
                // 插入到子空间中
                nodes[index]->insert(*it);
                it = objects.erase(it);
            }
            else
                it++;
        }
    }
}

void fcQuadTree::retrieve(std::vector<fcCircle*>& circles, fcRay* ray)
{

}
