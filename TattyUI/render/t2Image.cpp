#include <TattyUI/render/t2Image.h>

#ifdef T2_RENDERER_NANOVG
// 矢量图形库
#include <TattyUI/render/nanovg/src/nanovg.h>
#endif

#include <TattyUI/render/t2Renderer.h>

#define t2GetContext t2Renderer::getInstance()->getContext

namespace TattyUI
{
    t2Image::t2Image() :width(0), height(0), bLoaded(false), strokeWidth(1)
    {

    }

    t2Image::t2Image(t2Image &image) : 
        img(image.img), 
        width(image.width), height(image.height), 
        strokeWidth(image.strokeWidth),
        bLoaded(image.bLoaded)
    {
        
    }

    bool t2Image::loadImage(string path)
    {
        img = nvgCreateImage(t2GetContext(), path.c_str(), 0);

        if(!img)
        {
            bLoaded = false;
            t2PrintError("图片读取失败,可能是路径有误");
            return false;
        }
        else
        {
            bLoaded = true;
            nvgImageSize(t2GetContext(), img, &width, &height);
            return true;
        }
    }

    void t2Image::drawInRect(int x, int y, int width, int height, int angle /*= 0*/, int alpha /*= 255*/, bool bFill /*= true*/)
    {
        NVGpaint imgPaint = nvgImagePattern(t2GetContext(), x, y, width, height, angle / 255.0f, img, alpha / 255.0f);

        nvgBeginPath(t2GetContext());

        nvgRect(t2GetContext(), x, y, width, height);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), imgPaint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), imgPaint);
            nvgStroke(t2GetContext());
        }
    }

    void t2Image::drawInRounedRect(int x, int y, int width, int height, float radius, int angle /*= 0*/, int alpha /*= 255*/, bool bFill /*= true*/)
    {
        NVGpaint imgPaint = nvgImagePattern(t2GetContext(), x, y, width, height, angle / 255.0f, img, alpha / 255.0f);

        nvgBeginPath(t2GetContext());
        
        if(!bFill)
            nvgStrokeWidth(t2GetContext(), strokeWidth);

        nvgRoundedRect(t2GetContext(), x, y, width, height, radius);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), imgPaint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), imgPaint);
            nvgStroke(t2GetContext());
        }
    }

    void t2Image::drawInCircle(int x, int y, float radius, int angle /*= 0*/, int alpha /*= 255*/, bool bFill /*= true*/)
    {
        NVGpaint imgPaint = nvgImagePattern(t2GetContext(), x, y, width, height, angle / 255.0f, img, alpha / 255.0f);

        nvgBeginPath(t2GetContext());
        nvgCircle(t2GetContext(), x, y, radius);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), imgPaint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), imgPaint);
            nvgStroke(t2GetContext());
        }
    }

    void t2Image::drawInEllipse(int x, int y, int rx, int ry, int angle /*= 0*/, int alpha /*= 255*/, bool bFill /*= true*/)
    {
        NVGpaint imgPaint = nvgImagePattern(t2GetContext(), x, y, width, height, angle / 255.0f, img, alpha / 255.0f);

        nvgBeginPath(t2GetContext());
        nvgEllipse(t2GetContext(), x, y, rx, ry);

        if(bFill)
        {
            nvgFillPaint(t2GetContext(), imgPaint);
            nvgFill(t2GetContext());
        }
        else
        {
            nvgStrokePaint(t2GetContext(), imgPaint);
            nvgStroke(t2GetContext());
        }
    }

    int t2Image::getWidth()
    {
        return width;
    }

    int t2Image::getHeight()
    {
        return height;
    }

    void t2Image::setStrokeWidth(int wigth)
    {
        strokeWidth = width;
    }

    bool t2Image::isLoaded()
    {
        return bLoaded;
    }

}
