#include <TattyUI/controller/layout/t2LayoutController.h>
#include <TattyUI/div/t2DivController.h>
#include <LinearList/t3Queue.h>
#include <TattyUI/render/t2Renderer.h>

namespace TattyUI
{
    enum t2UpdateStatus
    {
        T2_UPDATESTATUS_ONE = 1,
        T2_UPDATESTATUS_ALL = 3
    };

    t2LayoutController::t2LayoutController()
    {

    }

    t2LayoutController* t2LayoutController::getInstance()
    {
        static t2LayoutController temp;
        return &temp;
    }

    void t2LayoutController::update()
    {
        t2DivController* divController = t2DivController::getInstance();
        t2Div* root = divController->getRoot();

        // --!层序遍历
        static t3Queue<t2Div*> queue;
        if(!root) return;
        queue.push(root);

        for(;;)
        {
            t2Div* temp;

            if(queue.isEmpty()) temp = NULL;
            else temp = queue.pop();

            if(temp)
            {
                int restoreStatus = temp->getStatus();

                // 三种状态全权更新
                for(int i = T2_NORMAL; i <= T2_ACTIVE; i++)
                {
                    temp->setStatus(i);
                    updateDiv(temp, false);

                    //if(temp->hasCondition())
                    updateDiv(temp, true);
                }

                temp->setStatus(restoreStatus);

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else break;
        }
    }

    void t2LayoutController::updateAll()
    {
        t2DivController* divController = t2DivController::getInstance();
        t2Div* root = divController->getRoot();

        // --!层序遍历
        t3Queue<t2Div*> queue;
        if(!root) return;
        queue.push(root);

        for(;;)
        {
            t2Div* temp;

            if(queue.isEmpty()) temp = NULL;
            else temp = queue.pop();

            if(temp)
            {
                int restoreStatus = temp->getStatus();

                // 三种状态全权更新
                for(int i = T2_NORMAL; i <= T2_ACTIVE; i++)
                {
                    temp->setStatus(i);
                    updateDiv(temp, false);

                    //if(temp->hasCondition())
                        updateDiv(temp, true);
                }

                temp->setStatus(restoreStatus);

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else break;
        }
    }

    void t2LayoutController::updateDiv(t2Div* div, bool bCondition)
    {
        if(div->parent)
        {
            switch(div->parent->layout)
            {
            case T2_LINEAR_LAYOUT:
                linearLayout(div, bCondition);
                break;
            case T2_LIST_LAYOUT:
                listLayout(div, bCondition);
                break;

            default:
                t2PrintError("错误布局代码");
                break;
            }
        }
        // 根节点默认为线性布局
        else
            linearLayout(div);
    }

    void t2LayoutController::linearLayout(t2Div* div, bool bCondition)
    {
        t2Div *parent = div->parent;

        t2Style& css = bCondition ? div->getConditionCSS() : div->getCSS();

        // 根节点
        if(!parent)
        {
            css.x = css.marginLeft;
            css.y = css.marginTop + t2GetWindowTitleBarHeight();

            css.contentSize.x = css.marginLeft + css.paddingLeft;
            css.contentSize.y = css.marginTop + css.paddingTop + t2GetWindowTitleBarHeight();

            int tempWidth = css.width - css.paddingLeft - css.paddingRight;
            css.contentSize.width = (tempWidth > 0) ? tempWidth : 0;

            int tempHeight = css.height - css.paddingTop - css.paddingBottom;
            css.contentSize.height = (tempHeight > 0) ? tempHeight : 0;

            return;
        }

        // 通用布局 
        t2Style& parentCSS = bCondition ? parent->getConditionCSS() : parent->getCSS();

        int allChildWidth = 0, allChildHeight = 0;
        int nowChildWidth = 0, nowChildHeight = 0, nowMaxHeight = 0;

        // 从头遍历所有自身之前的所有兄弟结点
        for(t2Div* childptr = parent->child; childptr != div; childptr = childptr->next)
        {
            t2Style& childCSS = bCondition ? childptr->getConditionCSS() : childptr->getCSS();

            // x
            nowChildWidth = childCSS.marginLeft + childCSS.width + childCSS.marginRight;

            // 当前行的起始位置
            allChildWidth += nowChildWidth;

            // y
            nowChildHeight = childCSS.marginTop + childCSS.height + childCSS.marginBottom;
            // 记录当前行最大高度
            if(nowChildHeight > nowMaxHeight)
                nowMaxHeight = nowChildHeight;

            // 超出父节点可容纳的最大显示宽度(去除内边距)自动换行
            if(childptr->next != div)
            {
                t2Style& x = bCondition ? childptr->next->getConditionCSS() : childptr->next->getCSS();
                if(allChildWidth + x.width + x.marginLeft + x.marginRight > parentCSS.width - parentCSS.paddingLeft - parentCSS.paddingRight)
                {
                    allChildWidth = 0;

                    // 累积y值
                    allChildHeight += nowMaxHeight;

                    nowMaxHeight = 0;
                }

                // 超出区域直接裁剪不显示
                if(allChildHeight + x.height + x.marginTop + x.marginBottom > parentCSS.height - parentCSS.paddingTop - parentCSS.paddingBottom)
                    x.display = T2_DISPLAY_NONE;
            }
            else
            {
                // 最后一个结点
                if(allChildWidth + css.width + css.marginLeft + css.marginRight > parentCSS.width - parentCSS.paddingLeft - parentCSS.paddingRight)
                {
                    allChildWidth = 0;

                    // 累积y值
                    allChildHeight += nowMaxHeight;

                    nowMaxHeight = 0;
                }

                // 超出区域直接裁剪不显示
                if(allChildHeight + css.height + css.marginTop + css.marginBottom > parentCSS.height - parentCSS.paddingTop - parentCSS.paddingBottom)
                    css.display = T2_DISPLAY_NONE;
            }
        }

        css.x = parentCSS.x + parentCSS.paddingLeft + allChildWidth;

        css.y = parentCSS.y + parentCSS.paddingTop + allChildHeight;

        css.contentSize.x = parentCSS.x + parentCSS.paddingLeft + allChildWidth +
            css.marginLeft + css.paddingLeft;

        css.contentSize.y = parentCSS.y + parentCSS.paddingTop + allChildHeight +
            css.marginTop + css.paddingTop;

        // 防止过大内边距以至于出现负值content-Size
        int tempWidth = css.width - css.paddingLeft - css.paddingRight;
        css.contentSize.width = (tempWidth) > 0 ? tempWidth : 0;

        int tempHeight = css.height - css.paddingTop - css.paddingBottom;
        css.contentSize.height = (tempHeight) > 0 ? tempHeight : 0;
    }

    // 根据div父节点类型将div更新为列表布局方式排列
    void t2LayoutController::listLayout(t2Div* div, bool bCondition)
    {

    }
}