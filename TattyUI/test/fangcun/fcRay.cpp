#include <TattyUI/test/fangcun/fcRay.h>
#include <TattyUI/render/t2Renderer.h>

// equation
//class ray::equation
//{
//public:
//    equation(float a, float b, float c);
//
//    float distance(int x, int y);
//
//    // 一般式直线方程
//    float a, b, c;
//};
//
//fcRay::equation::equation(float a, float b, float c) :a(a), b(b), c(c)
//{
//
//}
//
//float fcRay::equation::distance(int x, int y)
//{
//    
//}

// fcRay
fcRay::fcRay(int x1, int y1, int x2, int y2)
{
    set(x1, y1, x2, y2);
}

fcRay::fcRay(t2Vector2f p1, t2Vector2f p2)
{
    set(p1.x, p1.y, p2.x, p2.y);
}

fcRay::fcRay()
{
    set(0, 0, 0, 0);
}

//float fcRay::distance(int x, int y)
//{
//    return abs(a*x + b*y + c) / sqrtf(a*a + b*b);
//}

void fcRay::draw()
{
    t2Renderer* renderer = t2Renderer::getInstance();
    renderer->setStrokeColor(50, 50, 50);
    renderer->setStrokeWidth(1.0);
    renderer->drawLine(start.x, start.y, end.x, end.y);
}

void fcRay::set(int x1, int y1, int x2, int y2)
{
    //this->x1 = x1;
    //this->x2 = x2;
    //this->y1 = y1;
    //this->y2 = y2;

    //a = y1 - y2;
    //b = x2 - x1;
    //c = x1*y2 - x2*y1;

    start.set(x1, y1);
    end.set(x2, y2);

    direction.set(x2 - x1, y2 - y1);
    direction.normalize();
    //k = -a / b;
    //t = -c / b;
}

bool fcRay::parallel(t2Vector2f &v)
{
    if(v.x / direction.x == v.y / direction.y)
        return true;
    else
        return false;
}
