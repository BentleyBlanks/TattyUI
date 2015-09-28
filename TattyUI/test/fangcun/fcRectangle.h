#ifndef FCRECTANGLE_H
#define FCRECTANGLE_H

class fcRectangle
{
public:
    fcRectangle();

    fcRectangle(int x, int y, int width, int height);

    fcRectangle(fcRectangle& rect);

    void set(int x, int y, int width, int height);

    int getX();

    int getY();

    int getWidth();

    int getHeight();

    void draw();

protected:
    int x, y;
    int width, height;
};

#endif