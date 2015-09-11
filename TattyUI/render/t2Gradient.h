#ifndef T2_GRADIENT_H
#define T2_GRADIENT_H

#include <TattyUI/common/t2Color.h>

#ifdef T2_RENDERER_NANOVG
// 矢量图形库
#include <TattyUI/render/nanovg/src/nanovg.h>
#endif

namespace TattyUI
{
    enum t2Solidity
    {
        T2_SOLID = 1,			// CCW
        T2_HOLE = 2,			// CW
    };

    enum t2GradientType
    {
        T2_BOX_GRADIENT = 0,
        T2_LINEAR_GRADIENT,
        T2_RADIAL_GRADIENT
    };

    class t2Gradient
    {
    public:
        t2Gradient();

        void setSize(int x, int y, int width, int height);

        void setWinding(int winding);

        virtual void drawInRect(int x, int y, int width, int height, bool bFill = true);

        virtual void drawInRounedRect(int x, int y, int width, int height, float radius, bool bFill = true);

        virtual void drawInCircle(int x, int y, float raidus, bool bFill = true);

        virtual void drawInEllipse(int x, int y, int rx, int ry, bool bFill = true);

    protected:
#ifdef T2_RENDERER_NANOVG
        NVGpaint paint;
#endif
        int type;

        int x, y, width, height;

        int solidity;
    };

    class t2BoxGradient :public t2Gradient
    {
    public:
        t2BoxGradient() {}

        t2BoxGradient(float x, float y, float width, float height, float radius, float feather, t2Color icol, t2Color ocol);

        t2BoxGradient(t2BoxGradient& b);
    
        virtual void drawInRounedRect(bool bFill = true);

        void set(float x, float y, float width, float height, float radius, float feather, t2Color icol, t2Color ocol);

        int radius, feather;
    };

    class t2LinearGradient :public t2Gradient
    {
    public:
        t2LinearGradient() {}

        // 创建渐变自(x, y) -> (ex, ey)
        t2LinearGradient(float x, float y, float ex, float ey, t2Color icol, t2Color ocol);

        void set(float x, float y, float ex, float ey, t2Color icol, t2Color ocol);
    };

    class t2RadialGradient :public t2Gradient
    {
    public:
        t2RadialGradient() {}

        t2RadialGradient(float x, float y, float inRadius, float outRadius, t2Color icol, t2Color ocol);

        void set(float x, float y, float inRadius, float outRadius, t2Color icol, t2Color ocol);
    };
}

#endif