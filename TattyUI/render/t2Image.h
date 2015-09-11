#ifndef T2_IMAGE_H
#define T2_IMAGE_H

#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
    class t2Image
    {
    public:
        t2Image();

        t2Image(t2Image &image);

        bool isLoaded();

        bool loadImage(const char* path);
        
        void drawInRect(int x, int y, int width, int height, int angle = 0, int alpha = 255, bool bFill = true);

        void drawInRounedRect(int x, int y, int width, int height, float radius, int angle = 0, int alpha = 255, bool bFill = true);

        void drawInCircle(int x, int y, float raidus, int angle = 0, int alpha = 255, bool bFill = true);

        void drawInEllipse(int x, int y, int rx, int ry, int angle = 0, int alpha = 255, bool bFill = true);

        void setStrokeWidth(int wigth);

        int getWidth();

        int getHeight();

    private:
        //void begin();

        //void end();

        // id
        int img;

        int width, height, strokeWidth;

        bool bLoaded;
    };
}

#endif
