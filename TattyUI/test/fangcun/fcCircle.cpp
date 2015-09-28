#include <TattyUI/test/fangcun/fcCircle.h>
#include <TattyUI/render/t2Renderer.h>

fcCircle::fcCircle(int x, int y, float radius) :fcRectangle(x - radius, y - radius, 2 * radius, 2 * radius), bDawAABB(true)
{
    set(x, y, radius);
}

fcCircle::fcCircle(const t2Vector2f& pos, float radius) :fcCircle(pos.x, pos.y, radius)
{

}

void fcCircle::set(int x, int y, float radius)
{
    status = NORMAL;
    
    pos.set(x, y);
    //this->x = x;
    //this->y = y;
    this->radius = radius;

    //pos.set(x, y);
}

void fcCircle::draw()
{
    t2Renderer* renderer = t2Renderer::getInstance();
    switch(status)
    {
    case NORMAL:
        renderer->setColor(50, 50, 50, 100);
        renderer->setStrokeColor(50, 50, 50, 100);

        if(bDawAABB)
            fcRectangle::draw();
        break;

    case COLLIDE:
        renderer->setColor(210, 50, 50, 255);
        renderer->setStrokeColor(210, 50, 50, 255);
        
        if(bDawAABB)
            fcRectangle::draw();
        break;
    }

    renderer->setStrokeWidth(1.0);
    renderer->drawCircle(pos.x, pos.y, radius, false);
    renderer->drawRect(pos.x, pos.y, 2, 2, true);

    
}
