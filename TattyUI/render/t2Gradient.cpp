#include <TattyUI/render/t2Gradient.h>

#include <TattyUI/render/t2Renderer.h>

#define t2GetContext t2Renderer::getInstance()->getContext

namespace TattyUI
{
    t2Gradient::t2Gradient() :x(0), y(0), width(0), height(0)
    {
        type = T2_BOX_GRADIENT;
    }

    void t2Gradient::setSize(int x, int y, int width, int height/*, int radius*/)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        //this->radius = radius;
    }

    void t2Gradient::setWinding(int winding)
    {
        solidity = winding;
    }

    void t2Gradient::drawInRect(int x, int y, int width, int height, bool bFill /*= true*/)
    {
        nvgBeginPath(t2GetContext());

        nvgRect(t2GetContext(), x, y, width, height);
        nvgPathWinding(t2GetContext(), solidity);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), paint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), paint);
            nvgStroke(t2GetContext());
        }
    }

    void t2Gradient::drawInRounedRect(int x, int y, int width, int height, float radius, bool bFill /*= true*/)
    {
        nvgBeginPath(t2GetContext());

        nvgRoundedRect(t2GetContext(), x, y, width, height, radius);
        nvgPathWinding(t2GetContext(), solidity);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), paint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), paint);
            nvgStroke(t2GetContext());
        }
    }

    void t2Gradient::drawInCircle(int x, int y, float radius, bool bFill /*= true*/)
    {
        nvgBeginPath(t2GetContext());
        nvgCircle(t2GetContext(), x, y, radius);
        nvgPathWinding(t2GetContext(), solidity);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), paint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), paint);
            nvgStroke(t2GetContext());
        }

    }

    void t2Gradient::drawInEllipse(int x, int y, int rx, int ry, bool bFill /*= true*/)
    {
        nvgBeginPath(t2GetContext());
        nvgEllipse(t2GetContext(), x, y, rx, ry);
        nvgPathWinding(t2GetContext(), solidity);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), paint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), paint);
            nvgStroke(t2GetContext());
        }
    }

    t2BoxGradient::t2BoxGradient(float x, float y, float width, float height, float radius, float feather, t2Color icol, t2Color ocol)
    {
        paint = nvgBoxGradient(t2GetContext(), x, y, width, height, radius, feather, nvgRGBA(icol.r, icol.g, icol.b, icol.a), nvgRGBA(ocol.r, ocol.g, ocol.b, ocol.a));
    
        setSize(x, y, width, height);

        this->radius = radius;
        this->feather = feather;
    }

    t2BoxGradient::t2BoxGradient(t2BoxGradient& b) :
        radius(b.radius), feather(b.feather)
    {
        type = b.type;
        x = b.x;
        y = b.y;
        width = b.width;
        height = b.height;
        solidity = b.solidity;

        // paint copy
        paint.radius = b.paint.radius;
        paint.feather = b.paint.feather;
        paint.innerColor = b.paint.innerColor;
        paint.outerColor = b.paint.outerColor;
        paint.image = b.paint.image;
        for(int i = 0; i < 6; i++)
            paint.xform[i] = b.paint.xform[i];
        for(int i = 0; i < 2; i++)
            paint.extent[i] = b.paint.extent[i];
    }

    void t2BoxGradient::set(float x, float y, float width, float height, float radius, float feather, t2Color icol, t2Color ocol)
    {
        paint = nvgBoxGradient(t2GetContext(), x, y, width, height, radius, feather, nvgRGBA(icol.r, icol.g, icol.b, icol.a), nvgRGBA(ocol.r, ocol.g, ocol.b, ocol.a));
        
        setSize(x, y, width, height);

        this->radius = radius;
        this->feather = feather;
    }

    void t2BoxGradient::drawInRounedRect(bool bFill/* = true*/)
    {
        nvgBeginPath(t2GetContext());

        nvgRoundedRect(t2GetContext(), x - feather, y - feather, width + 2 * feather, height + 2 * feather, radius);
        nvgPathWinding(t2GetContext(), solidity);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), paint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), paint);
            nvgStroke(t2GetContext());
        }
    }

    t2LinearGradient::t2LinearGradient(float x, float y, float ex, float ey, t2Color icol, t2Color ocol)
    {
        paint = nvgLinearGradient(t2GetContext(), x, y, ex, ey, nvgRGBA(icol.r, icol.g, icol.b, icol.a), nvgRGBA(ocol.r, ocol.g, ocol.b, ocol.a));
    
        setSize(x, y, width, height);
    }

    void t2LinearGradient::set(float x, float y, float ex, float ey, t2Color icol, t2Color ocol)
    {
        paint = nvgLinearGradient(t2GetContext(), x, y, ex, ey, nvgRGBA(icol.r, icol.g, icol.b, icol.a), nvgRGBA(ocol.r, ocol.g, ocol.b, ocol.a));
        
        setSize(x, y, width, height);
    }

    t2RadialGradient::t2RadialGradient(float x, float y, float inRadius, float outRadius, t2Color icol, t2Color ocol)
    {
        paint = nvgRadialGradient(t2GetContext(), x, y, inRadius, outRadius, nvgRGBA(icol.r, icol.g, icol.b, icol.a), nvgRGBA(ocol.r, ocol.g, ocol.b, ocol.a));
    
        setSize(x, y, width, height);
    }

    void t2RadialGradient::set(float x, float y, float inRadius, float outRadius, t2Color icol, t2Color ocol)
    {
        paint = nvgRadialGradient(t2GetContext(), x, y, inRadius, outRadius, nvgRGBA(icol.r, icol.g, icol.b, icol.a), nvgRGBA(ocol.r, ocol.g, ocol.b, ocol.a));
    
        setSize(x, y, width, height);
    }
}