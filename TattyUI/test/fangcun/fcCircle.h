#ifndef FCCIRCLE_H
#define FCCIRCLE_H

#include <TattyUI/common/t2Vector2.h>
#include <TattyUI/test/fangcun/fcRectangle.h>
using namespace TattyUI;

enum fcCircleStatus
{
    NORMAL,
    COLLIDE
};

class fcCircle :public fcRectangle
{
public:
    fcCircle(int x, int y, float radius);

    fcCircle(const t2Vector2f& pos, float radius);

    void set(int x, int y, float radius);

    // test
    void draw();

    t2Vector2f pos;

    float radius;

    int status;

    bool bDawAABB;
};

#endif