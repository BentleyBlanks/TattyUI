#ifndef FCQUADTREE_H
#define FCQUADTREE_H

#include <vector>
#include <TattyUI/test/fangcun/fcRectangle.h>

enum fcQuadTreeMax
{
    FC_QUADTREE_MAX_OBJECTS = 10,
    FC_QUADTREE_MAX_DEPTH = 5
};

enum fcQuadSubNode
{
    FC_TOP_RIGHT = 0,
    FC_TOP_LEFT = 1,
    FC_BOTTOM_LEFT = 2,
    FC_BOTTOM_RIGHT = 3,

    FC_PARENT = -1
};

// 借鉴于
// --!http://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
class fcRay;
class fcCircle;
class fcQuadTree
{
public:
    fcQuadTree(int depth, fcRectangle bounds);

    void clear();

    void split();

    int getIndex(fcCircle* circle);

    void insert(fcCircle* circle);

    // 在circles中存放检索到的对象集
    void retrieve(std::vector<fcCircle*>& circles, fcRay* ray);

    // 当前深度
    int depth;
    // 指向四个子节点的指针数组
    std::vector<fcQuadTree*> nodes;
    // 结点边界
    fcRectangle bounds;
    // 当前结点包含对象
    std::vector<fcCircle*> objects;
};

#endif