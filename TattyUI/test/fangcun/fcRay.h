#ifndef FCRAY_H
#define FCRAY_H

#include <TattyUI/common/t2Vector2.h>
using namespace TattyUI;

class fcRay
{
public:
    fcRay();
    // 起始点 终止方向
    fcRay(int x1, int y1, int x2, int y2);

    fcRay(t2Vector2f p1, t2Vector2f p2);

    void set(int x1, int y1, int x2, int y2);

    // 点到直线距离
    //float distance(int x, int y);

    // 是否与给定向量平行
    bool parallel(t2Vector2f& v);

    // test
    void draw();

//private:
    //class equation;
    //equation *e;
    //
    // 一般式直线方程
    // y = ax + by + c
    //float a, b, c;
    //
    // 直线方程辅助量
    // y = kx + t
    //float k, t;
    //
    //int x1, y1, x2, y2;

    t2Vector2f start, end;

    // 方向向量
    t2Vector2f direction;

};

#endif