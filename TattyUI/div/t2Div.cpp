#include <TattyUI/div/t2Div.h>
#include <TattyUI/render/t2Renderer.h>
#include <TattyUI/controller/layout/t2LayoutController.h>

#include <TattyUI/common/t2Math.h>
#include <LinearList/t3Queue.h>

#include <TattyUI/common/t2Window.h>

#define renderer t2Renderer::getInstance()

namespace TattyUI
{
    // 委托构造函数
    t2Div::t2Div() :t2Div(0, 0, "", "")
    {

    }

    t2Div::t2Div(int width, int height, string fontName, string fontPath) :status(T2_NORMAL), parent(NULL), next(NULL), child(NULL),
        bDrawMarginAABB(false), bDrawPaddingAABB(false), bHover(false), bNormal(false), bActive(false), layout(T2_LINEAR_LAYOUT)
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
        t2Window* window = t2Window::getInstance();

        for(int i = T2_NORMAL; i <= T2_ACTIVE; i++)
        {
            setStatus(i);
            //updateContent();
            t2Style& css = getCSS();

            // normal
            // 渐变阴影
            css.boxGradient.set(css.contentSize.x + css.hBoxShadow,
                                css.contentSize.y + css.vBoxShadow + window->getTitleBarHeight(),
                                css.contentSize.width, css.contentSize.height,
                                css.borderRadius,
                                css.boxShadowBlur,
                                css.boxShadowInColor, css.boxShadowOutColor);
            // dimension 
            css.maxWidth = css.contentSize.width;
            css.maxHeight = css.contentSize.height;
            css.minWidth = css.contentSize.width;
            css.minHeight = css.contentSize.height;

            // 假定fontName直接与fontFamily同名
            renderer->loadFont(css.fontFamily.c_str(), css.fontFamily.c_str());
        }

        setStatus(T2_NORMAL);
    }

    t2Style& t2Div::getCSS()
    {
        switch(status)
        {
        case T2_NORMAL:
            return normal;
        
        case T2_ACTIVE:
            return active;

        case T2_HOVER:
            return hover;
        }
    }

    void t2Div::draw()
    {
        t2Style& css = getCSS();

        if(css.display == T2_DISPLAY_NONE)
            return;

        // 全权由LayoutController管理
        //updateContent();

        // div阴影
        if(css.displayShadow)
            css.boxGradient.drawInRounedRect();

        // div主体
        renderer->setColor(css.backgroundColor);
        renderer->drawRoundRect(css.contentSize.x, css.contentSize.y, css.contentSize.width, css.contentSize.height, css.borderRadius);

        // backgroundImage
        if(css.backgroundImage.isLoaded())
            // --!目前background-position不起作用
            css.backgroundImage.drawInRounedRect(css.contentSize.x, css.contentSize.y, css.contentSize.width, css.contentSize.height, css.borderRadius, 0, css.opacity * 255, true);

        // text
        renderer->setTextColor(css.textColor);
        renderer->setFont(css.fontFamily.c_str());
        int align, textX = css.contentSize.x + css.contentSize.width / 2, textY = css.contentSize.y + css.contentSize.height / 2;

        if(css.textAlign & T2_TEXT_LEFT)
        {
            textX -= css.contentSize.width / 2;
            align = T2_ALIGN_LEFT;
        }
        else if(css.textAlign & T2_TEXT_RIGHT)
        {
            textX += css.contentSize.width / 2;
            align = T2_ALIGN_RIGHT;
        }
        else if(css.textAlign & T2_TEXT_CENTER)
            align = T2_ALIGN_CENTER;

        if(css.textAlign & T2_ALIGN_TOP)
        {
            textY -= css.contentSize.height / 2;
            align |= T2_ALIGN_TOP;
        }
        else if(css.textAlign & T2_TEXT_BOTTOM)
        {
            textY += css.contentSize.height / 2;
            align |= T2_ALIGN_BOTTOM;
        }
        else if(css.textAlign & T2_TEXT_MIDDLE)
            align |= T2_ALIGN_MIDDLE;

        renderer->drawText(textX, textY, css.fontSize, css.text, 0, align);

        // --!debug
        if(bDrawMarginAABB)
        {
            renderer->setStrokeWidth(1.0);
            renderer->setStrokeColor(0, 0, 0, 200);
            renderer->drawRect(css.contentSize.x - css.marginLeft - css.paddingLeft, css.contentSize.y - css.marginTop - css.paddingTop,
                               css.width + css.marginLeft + css.marginRight, css.height + css.marginTop + css.marginBottom, false);
        }

        if(bDrawPaddingAABB)
        {
            renderer->setStrokeWidth(1.0);
            renderer->setStrokeColor(255, 255, 255, 200);
            renderer->drawRect(css.contentSize.x - css.paddingLeft, css.contentSize.y - css.paddingTop, css.width, css.height, false);
        }
    }

    //void t2Div::updateContent()
    //{
    //    t2Window* window = t2Window::getInstance();
    //    // --!这里的内容可以由layoutController完成
    //    t2Style& css = getCSS();
    //
    //    // 根节点
    //    if(!parent)
    //    {
    //        css.x = css.marginLeft;
    //        css.y = css.marginTop + window->getTitleBarHeight();
    //
    //        css.contentSize.x = css.marginLeft + css.paddingLeft;
    //        css.contentSize.y = css.marginTop + css.paddingTop + window->getTitleBarHeight();
    //
    //        int tempWidth = css.width - css.paddingLeft - css.paddingRight;
    //        css.contentSize.width = (tempWidth > 0) ? tempWidth : 0;
    //
    //        int tempHeight = css.height - css.paddingTop - css.paddingBottom;
    //        css.contentSize.height = (tempHeight > 0) ? tempHeight : 0;
    //
    //        return;
    //    }
    //        
    //    // 内外边距更新
    //    // 以下属性全为实际显示时大小
    //    // content-x = parent.marginLeft + parent.x + parent.paddingLeft + all[child.marginLeft + child.width + child.marginRight] +
    //    //             marginLeft + border(暂不支持) + paddingLeft决定
    //    // content-y = parent.marginTop + parent.y + parent.paddingTop + all.max[child.marginBottom + child.height + child.marginTop] +
    //    //             marginTop + border(暂不支持) + paddingTop决定
    //    // content-width = div-width - paddingLeft - paddingRight
    //    // content-height = div-height - paddingTop - paddingBottom
    //    
    //    // 列表布局
    //
    //    // 通用布局 
    //    t2Style& parentCSS = parent->getCSS();
    //
    //    int allChildWidth = 0, allChildHeight = 0;
    //    int nowChildWidth = 0, nowChildHeight = 0, nowMaxHeight = 0;
    //
    //    // 从头遍历所有自身之前的所有兄弟结点
    //    for(t2Div* childptr = parent->child; childptr != this; childptr = childptr->next)
    //    {
    //        t2Style& childCSS = childptr->getCSS();
    //        
    //        // x
    //        nowChildWidth = childCSS.marginLeft + childCSS.width + childCSS.marginRight;
    //        
    //        // 当前行的起始位置
    //        allChildWidth += nowChildWidth;
    //
    //        // y
    //        nowChildHeight = childCSS.marginTop + childCSS.height + childCSS.marginBottom;
    //        // 记录当前行最大高度
    //        if(nowChildHeight > nowMaxHeight)
    //            nowMaxHeight = nowChildHeight;
    //
    //        // 超出父节点可容纳的最大显示宽度(去除内边距)自动换行
    //        if(childptr->next != this)
    //        {
    //            t2Style& x = childptr->next->getCSS();
    //            if(allChildWidth + x.width + x.marginLeft + x.marginRight > parentCSS.width - parentCSS.paddingLeft - parentCSS.paddingRight)
    //            {
    //                allChildWidth = 0;
    //
    //                // 累积y值
    //                allChildHeight += nowMaxHeight;
    //
    //                nowMaxHeight = 0;
    //            }
    //
    //            // 超出区域直接裁剪不显示
    //            if(allChildHeight + x.height + x.marginTop + x.marginBottom > parentCSS.height - parentCSS.paddingTop - parentCSS.paddingBottom)
    //                x.display = T2_DISPLAY_NONE;
    //        }
    //        else
    //        {
    //            // 最后一个结点
    //            if(allChildWidth + css.width + css.marginLeft + css.marginRight > parentCSS.width - parentCSS.paddingLeft - parentCSS.paddingRight)
    //            {
    //                allChildWidth = 0;
    //
    //                // 累积y值
    //                allChildHeight += nowMaxHeight;
    //
    //                nowMaxHeight = 0;
    //            }
    //
    //            // 超出区域直接裁剪不显示
    //            if(allChildHeight + css.height + css.marginTop + css.marginBottom > parentCSS.height - parentCSS.paddingTop - parentCSS.paddingBottom)
    //                css.display = T2_DISPLAY_NONE;
    //        }
    //    }
    //
    //    css.x = parentCSS.x + parentCSS.paddingLeft + allChildWidth;
    //
    //    css.y = parentCSS.y + parentCSS.paddingTop + allChildHeight;
    //
    //    css.contentSize.x = parentCSS.x + parentCSS.paddingLeft + allChildWidth + 
    //                         css.marginLeft + css.paddingLeft;
    //
    //    css.contentSize.y = parentCSS.y + parentCSS.paddingTop + allChildHeight +
    //                         css.marginTop + css.paddingTop;
    //
    //    // 防止过大内边距以至于出现负值content-Size
    //    int tempWidth = css.width - css.paddingLeft - css.paddingRight;
    //    css.contentSize.width = (tempWidth) > 0 ? tempWidth : 0;
    //    
    //    int tempHeight = css.height - css.paddingTop - css.paddingBottom;
    //    css.contentSize.height = (tempHeight) > 0 ? tempHeight : 0;
    //
    //}

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

        if(inDiv(x, y))
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

        if(inDiv(x, y))
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

        if(mouseMoved && inDiv(x, y))
            mouseMoved(x, y, px, py);

        if(!inDiv(x, y) && inDiv(px, py))
        {    
            // 鼠标移出
            setStatus(T2_NORMAL);

            if(mouseMovedOut)
                mouseMovedOut(x, y, px, py);
        }

        if(inDiv(x, y) && !inDiv(px, py))
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

        if(mouseScrolled && inDiv(x, y))
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

    bool t2Div::inDiv(int x, int y)
    {
        t2Style css = getCSS();

        if(pointInsideRect(css.contentSize.x, css.contentSize.y, css.contentSize.width, css.contentSize.height, x, y))
           return true;
        else
            return false;
    }

    bool t2Div::inDiv(t2Point2i p)
    {
        return inDiv(p.x, p.y);
    }

    bool t2Div::inChild(t2Point2i pos)
    {
        return inChild(pos.x, pos.y);
    }

    bool t2Div::inChild(int x, int y)
    {
        // --!层序遍历
        t3Queue<t2Div*> queue;
        if(!child) return false;
        // 将所有兄弟结点入队列
        for(t2Div* c = child; c != NULL; c = c->next)
            queue.push(c);

        for(;;)
        {
            t2Div* temp;

            if(queue.isEmpty()) temp = NULL;
            else temp = queue.pop();

            if(temp)
            {
                // 子节点符合
                if(temp->inDiv(x, y))
                    return true;

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else break;
        }

        return false;
    }

}