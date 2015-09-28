#include <TattyUI/test/fangcun/fcController.h>
#include <TattyUI/test/fangcun/fcCircle.h>
#include <TattyUI/test/fangcun/fcRay.h>

float distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

fcController::fcController()
{

}

fcController* fcController::getInstace()
{
    static fcController c;
    return &c;
}

void fcController::addCircle(fcCircle* c)
{
    if(!c)
    {
        t2PrintError("不可添加空元素");
        return;
    }

    circles.push_back(c);
}

void fcController::deleteCircle(fcCircle* c)
{
    for(vector<fcCircle*>::iterator it = circles.begin(); it != circles.end();)
    {
        if(*it == c)
        {
            it = circles.erase(it);
            return;
        }
        else
            ++it;
    }

    t2Log("未能找到指定元素，无法删除\n");
}

void fcController::draw()
{
    for(auto c : circles)
        c->draw();
}

t2Vector2f* fcController::intersection(fcRay &r)
{
    t2Vector2f* intersect = new t2Vector2f();
    float d = FLT_MAX;
    bool hasIntersect = false;

    for(auto circle : circles)
    {
        // 向量无需考虑斜率
        // t2 + 2(m·d)t + (m·m) - r2 = 0
        t2Vector2f m = r.start - circle->pos;
        float b = m * r.direction;
        float c = m * m - circle->radius * circle->radius;
        float delta = b*b - c;
        float t = 0.0f;

        // 两个交点
        if(delta > 0)
        {
            t = -b - sqrt(delta);
            t2Vector2f temp1 = r.start + t * r.direction;
            t = -b + sqrt(delta);
            t2Vector2f temp2 = r.start + t * r.direction;

            // 距离最短
            float tempDistance = temp1.getDistance(r.start);
            if(tempDistance < d)
            {
                // 与射线同向 则交点有效 否则该交点在射线的负方向延长线上
                if((temp1 - r.start) * r.direction > 0)
                {
                    intersect->set(temp1);
                    d = tempDistance;
                    hasIntersect = true;
                }
            }
            tempDistance = temp2.getDistance(r.start);
            if(tempDistance < d)
            {
                // 与射线同向 则交点有效 否则该交点在射线的负方向延长线上
                if((temp2 - r.start) * r.direction > 0)
                {
                    intersect->set(temp2);
                    d = tempDistance;
                    hasIntersect = true;
                }
            }

            circle->status = COLLIDE;
        }
        // 一个交点
        else if(delta == 0)
        {
            t = -b - sqrt(delta);
            t2Vector2f temp = r.start + t * r.direction;
            // 距离最短
            float tempDistance = temp.getDistance(r.start);
            if(tempDistance < d)
            {
                // 与射线同向 则交点有效 否则该交点在射线的负方向延长线上
                if(temp.dot(r.start) > 0)
                {
                    intersect->set(temp);
                    d = tempDistance;
                    hasIntersect = true;
                }
            }

            circle->status = COLLIDE;
        }
        else
            circle->status = NORMAL;
    }

    if(hasIntersect)
        return intersect;
    else
    {
        delete intersect;
        intersect = NULL;
        return NULL;
    }
}

//t2Vector2f* fcController::intersection1(fcRay &r)
//{
//    t2Vector2f* intersect = new t2Vector2f();
//    int minX = -1, minY = -1;
//    float d = INT_MAX;
//    bool hasIntersect = false;
//
//    for(auto c : circles)
//    {
//        static t2Vector2f temp;
//        temp.set(c->x - r.x1, c->y - r.y1);
//
//        float k = -r.a / r.b, t = -r.c / r.b;
//
//        // 斜率为0 特殊讨论
//        if(r.b == 0.0)
//        {
//
//        }
//
//        // 圆与直线联立方程组
//        float A = k * k + 1.0f, B = 2 * k * t - 2 * c->y * k - 2 * c->x, C = c->x * c->x + t * t - 2 * c->y * t + c->y * c->y - c->radius * c->radius;
//        
//        // delta >= 0有交点
//        float delta = B * B - 4 * A * C;
//
//        if(delta >= 0)
//        {
//            hasIntersect = true;
//            if((temp.dot(r.direction) < 0 && distance(r.x1, r.y1, c->x, c->y) <= c->radius) || temp.dot(r.direction) >= 0)
//            {
//                // 取距离最短者
//                // 一个交点
//                if(delta == 0)
//                {
//                    int x = -B / (2 * A);
//                    int y = k*x + t;
//
//                    float temp0 = distance(x, y, r.x1, r.y1);
//                    if(temp0 < d)
//                    {
//                        minX = x;
//                        minY = y;
//                        d = temp0;
//                    }
//                }
//                // 两个交点
//                else
//                {
//                    float x1 = (-B + sqrt(delta)) / (2.0f * A);
//                    float y1 = k*x1 + t;
//
//                    int x2 = (-B - sqrt(delta)) / (2.0f * A);
//                    int y2 = k*x2 + t;
//
//                    float temp1 = distance(x1, y1, r.x1, r.y1), temp2 = distance(x2, y2, r.x1, r.y1);
//                    static t2Vector2f intersetctToLine;
//                    if(temp1 < d)
//                    {
//                        // 与射线同向平行 则交点有效 否则该交点在射线的负方向延长线上
//                        intersetctToLine.set(x1-r.x1, y1-r.y1);
//                        if(r.direction.dot(intersetctToLine) > 0)
//                        {
//                            minX = x1;
//                            minY = y1;
//                            d = temp1;
//                        }
//                    }
//                    if(temp2 < d)
//                    {
//                        // 与射线同向平行
//                        intersetctToLine.set(x2 - r.x1, y2 - r.y1);
//                        if(r.direction.dot(intersetctToLine) > 0)
//                        {
//                            minX = x2;
//                            minY = y2;
//                            d = temp2;
//                        }
//                    }
//                }
//
//                c->status = COLLIDE;
//            }
//        }
//        else
//        {
//            c->status = NORMAL;
//        }
//    }
//
//    if(hasIntersect)
//    {
//        intersect->set(minX, minY);
//        return intersect;
//    }
//    else
//    {
//        delete intersect;
//        intersect = NULL;
//        return NULL;
//    }
//}
