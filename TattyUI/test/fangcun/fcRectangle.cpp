#include <TattyUI/test/fangcun/fcRectangle.h>
#include <TattyUI/render/t2Renderer.h>
using namespace TattyUI;

fcRectangle::fcRectangle() :x(0), y(0), width(0), height(0)
{

}

fcRectangle::fcRectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
{

}

fcRectangle::fcRectangle(fcRectangle& rect) : x(rect.x), y(rect.y), width(rect.width), height(rect.height)
{

}

void fcRectangle::set(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int fcRectangle::getX()
{
    return x;
}

int fcRectangle::getY()
{
    return y;
}

int fcRectangle::getWidth()
{
    return width;
}

int fcRectangle::getHeight()
{
    return height;
}

void fcRectangle::draw()
{
    t2Renderer* renderer = t2Renderer::getInstance();

    //renderer->setStrokeColor(33, 33, 33);
    //renderer->setStrokeWidth(0.5);
    renderer->drawRect(x, y, width, height, false);
}
