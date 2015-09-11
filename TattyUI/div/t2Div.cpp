#include <TattyUI/div/t2Div.h>
#include <TattyUI/render/t2Renderer.h>

#include <TattyUI/common/t2Math.h>

#define renderer t2Renderer::getInstance()

namespace TattyUI
{
    t2Div::t2Div(int width, int height, string fontName, string fontPath) :status(T2_NORAML)
    {
        // 3状态
        normal.width = width;
        normal.height = height;
        normal.fontFamily = fontPath;
        normal.fontName = fontName;

        active.width = width;
        active.height = height;
        active.fontFamily = fontPath;
        active.fontName = fontName;

        hover.width = width;
        hover.height = height;
        hover.fontFamily = fontPath;
        hover.fontName = fontName;
    }

    void t2Div::init()
    {
        // normal
        normal.boxGradient.set(normal.x + normal.hBoxShadow, normal.y + normal.vBoxShadow, normal.width, normal.height,
                        normal.borderRadius, normal.boxShadowBlur,
                        normal.boxShadowColor, t2Color(0, 0, 0, 0));

        normal.maxWidth = normal.width;
        normal.maxHeight = normal.height;
        normal.minWidth = normal.width;
        normal.minHeight = normal.height;

        renderer->loadFont(normal.fontName.c_str(), normal.fontFamily.c_str());

        // hover
        hover.boxGradient.set(hover.x + hover.hBoxShadow, hover.y + hover.vBoxShadow, hover.width, hover.height,
                        hover.borderRadius, hover.boxShadowBlur,
                        hover.boxShadowColor, t2Color(0, 0, 0, 0));

        hover.maxWidth = hover.width;
        hover.maxHeight = hover.height;
        hover.minWidth = hover.width;
        hover.minHeight = hover.height;

        renderer->loadFont(hover.fontName.c_str(), hover.fontFamily.c_str());

        // active
        active.boxGradient.set(active.x + active.hBoxShadow, active.y + active.vBoxShadow, active.width, active.height,
                        active.borderRadius, active.boxShadowBlur,
                        active.boxShadowColor, t2Color(0, 0, 0, 0));

        active.maxWidth = active.width;
        active.maxHeight = active.height;
        active.minWidth = active.width;
        active.minHeight = active.height;

        renderer->loadFont(active.fontName.c_str(), active.fontFamily.c_str());
    }

    t2Style& t2Div::getCSS()
    {
        switch(status)
        {
        case T2_NORAML:
            return normal;
        
        case T2_ACTIVE:
            return active;

        case T2_HOVER:
            return hover;
        }
    }

    void t2Div::draw()
    {
        t2Style css = getCSS();

        // div阴影
        css.boxGradient.drawInRounedRect();

        // div主体
        renderer->setColor(css.backgroundColor);
        renderer->drawRoundRect(css.x, css.y, css.width, css.height, css.borderRadius);

        // backgroundImage
        if(css.backgroundImage.isLoaded())
            css.backgroundImage.drawInRounedRect(css.x, css.y, css.width, css.height, css.borderRadius, 0, css.opacity * 255, true);

        // text
        renderer->setTextColor(css.textColor);
        renderer->setFont(css.fontName.c_str());
        int align, textX = css.x + css.width / 2, textY = css.y + css.height / 2;

        if(css.textAlign & T2_TEXT_LEFT)
        {
            textX -= css.width / 2;
            align = T2_ALIGN_LEFT;
        }
        else if(css.textAlign & T2_TEXT_RIGHT)
        {
            textX += css.width / 2;
            align = T2_ALIGN_RIGHT;
        }
        else if(css.textAlign & T2_TEXT_CENTER)
            align = T2_ALIGN_CENTER;

        if(css.textAlign & T2_ALIGN_TOP)
        {
            textY -= css.height / 2;
            align |= T2_ALIGN_TOP;
        }
        else if(css.textAlign & T2_TEXT_BOTTOM)
        {
            textY += css.height / 2;
            align |= T2_ALIGN_BOTTOM;
        }
        else if(css.textAlign & T2_TEXT_MIDDLE)
            align |= T2_ALIGN_MIDDLE;

        renderer->drawText(textX, textY, css.fontSize, css.text, 0, align);
    }

    void t2Div::setStatus(int status)
    {
        this->status = status;
    }

    int t2Div::getStatus()
    {
        return status;
    }

    void t2Div::onMousePressed(int x, int y, int px, int py, int button)
    {
        // not used <px, py>
        t2Style css = getCSS();

        if(pointInsideRect(css.x, css.y, css.width, css.height, x, y))
        {
            setStatus(T2_ACTIVE);

            if(mousePressed)
                mousePressed(x, y, px, py, button);
        }
    }

    void t2Div::onMouseReleased(int x, int y, int px, int py, int button)
    {
        // not used <px, py>
        t2Style css = getCSS();

        if(pointInsideRect(css.x, css.y, css.width, css.height, x, y))
        {
            setStatus(T2_HOVER);

            if(mouseReleased)
                mouseReleased(x, y, px, py, button);
        }
    }

    void t2Div::onMouseMoved(int x, int y, int px, int py)
    {
        // not used <px, py>
        t2Style css = getCSS();

        if(mouseMoved && pointInsideRect(css.x, css.y, css.width, css.height, x, y))
            mouseMoved(x, y, px, py);

        if(!pointInsideRect(css.x, css.y, css.width, css.height, x, y) && pointInsideRect(css.x, css.y, css.width, css.height, px, py))
        {    
            // 鼠标移出
            setStatus(T2_NORAML);
            if(mouseMovedOut)
                mouseMovedOut(x, y, px, py);
        }

        if(pointInsideRect(css.x, css.y, css.width, css.height, x, y) && !pointInsideRect(css.x, css.y, css.width, css.height, px, py))
        {
            // 鼠标移入
            setStatus(T2_HOVER);

            if(mouseMovedIn)
                mouseMovedIn(x, y, px, py);
        }
    }

    void t2Div::onMouseScrolled(int x, int y, int px, int py)
    {
        // not used <px, py>
        t2Style css = getCSS();

        if(mouseScrolled && pointInsideRect(css.x, css.y, css.width, css.height, x, y))
            mouseScrolled(x, y, px, py);
    }

    void t2Div::onKeyPressed(int key)
    {
        if(keyPressed)
            keyPressed(key);
    }

    void t2Div::onKeyReleased(int key)
    {
        if(keyReleased)
            keyReleased(key);
    }

}