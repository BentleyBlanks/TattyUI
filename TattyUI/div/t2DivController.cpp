#include <TattyUI/div/t2DivController.h>
#include <TattyUI/controller/layout/t2LayoutController.h>
#include <LinearList/t3Queue.h>

namespace TattyUI
{
    t2DivController* t2DivController::getInstance()
    {
        static t2DivController temp;
        return &temp;
    }

    //void t2DivController::update()
    //{        
    //    // 更新各自布局
    //    if(!root)
    //    {
    //        t2PrintError("未指定根节点，根节点为空");
    //        return;
    //    }

    //    // not finished
    //}

    void t2DivController::draw()
    {
        if(!root)
        {
            t2PrintError("未指定根节点，根节点为空");
            return;
        }

        //for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        //{
        //    // --!未来更新为从根节点进入遍历渲染
        //    it->second->draw();
        //}
        //
        //root->draw();

        // --!层序遍历
        static t3Queue<t2Div*> queue;
        if(!root) return;
        queue.push(root);

        for(;;)
        {
            t2Div* temp;

            if(queue.isEmpty())
                temp = NULL;
            else
                temp = queue.pop();

            if(temp)
            {
                temp->draw();

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }
    }

    void t2DivController::init()
    {
        //for(auto it : divTable)
        //    if(it.first != getRootDivGlobalID())
        //        it.second->init();

        // --!层序遍历
        static t3Queue<t2Div*> queue;
        if(!root) return;
        queue.push(root);

        for(;;)
        {
            t2Div* temp;

            if(queue.isEmpty())
                temp = NULL;
            else
                temp = queue.pop();

            if(temp)
            {
                if(temp != root)
                    temp->init();

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }
    }

    bool t2DivController::setRoot(string rootName)
    {
        std::map<string, t2Div*>::iterator it = divTable.find(rootName);
        if(it != divTable.end())
        {
            this->root = it->second;
            return true;
        }
        else
        {
            t2PrintErrorArg(rootName, root, "根节点不在指定div表中，请先调用addDiv()添加至表内");
            return false;
        }
    }

	t2Div* t2DivController::getRoot()
	{
		if (root)
			return root;
		else
			return NULL;
	}

    void t2DivController::addDiv(string id, t2Div* div)
    {
        if(!div)
        {
            t2PrintError("插入的div不得为空");
            return;
        }

        divTable.insert(std::map<string, t2Div*>::value_type(id, div));
    }

    void t2DivController::deleteDiv(string id)
    {
        divTable.erase(id);
    }

    t2DivController::t2DivController() :root(NULL)
    {

    }

    t2Div* t2DivController::operator[](const string& divName)
    {
        return find(divName);
    }

    t2Div* t2DivController::findByID(string id)
    {
        std::map<string, t2Div*>::iterator it = divTable.find(id);

        if(it == divTable.end())
        {
            t2Log("Warning: 未能找到指定id: %s的div", id.c_str());
            return NULL;
        }
        else
            return it->second;
    }

    t2Div* t2DivController::find(string divName)
    {
        for(map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
            if(it->second->className == divName)
                return it->second;
        }
        return NULL;
    }

    void t2DivController::onMousePressed(int x, int y, int px, int py, int button)
    {
        //for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        //{
        //    it->second->onMousePressed(x, y, px, py, button);
        //}

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
                // 只有当鼠标能够触发当前结点 且 无法触发子节点时才触发当前结点
                if(temp->inDiv(x, y) && !temp->inChild(x, y))
                    temp->onMousePressed(x, y, px, py, button);

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else break;
        }
    }

    void t2DivController::onMouseReleased(int x, int y, int px, int py, int button)
    {
        //for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        //{
        //    it->second->onMouseReleased(x, y, px, py, button);
        //}

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
                // 只有当鼠标能够触发当前结点 且 无法触发子节点时才触发当前结点
                if(temp->inDiv(x, y) && !temp->inChild(x, y))
                    temp->onMouseReleased(x, y, px, py, button);

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else break;
        }
    }

    void t2DivController::onMouseMoved(int x, int y, int px, int py)
    {
        //for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        //{
        //    it->second->onMouseMoved(x, y, px, py);
        //}

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
                if(temp->inDiv(x, y) || temp->inDiv(px, py))
                {
                    // 当前结点无子节点 且 鼠标不在子节点内移进移出
                    if(!temp->inChild(x, y) && !temp->inChild(px, py))
                        temp->onMouseMoved(x, y, px, py);
                }

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else break;
        }
    }

    void t2DivController::onMouseScrolled(int x, int y, int px, int py)
    {
        // --!未来更新为焦点输入
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
            it->second->onMouseScrolled(x, y, px, py);
        }
    }

    void t2DivController::onKeyPressed(int key)
    {
        // --!未来更新为焦点输入
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
            it->second->onKeyPressed(key);
        }
    }

    void t2DivController::onKeyReleased(int key)
    {
        // --!未来更新为焦点输入
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
            it->second->onKeyReleased(key);
        }
    }

    void t2DivController::print()
    {
        for(auto x : divTable)
        {
            std::cout << "t2Div id: " << x.first;
            std::cout << ", class: " << x.second->className;
            std::cout << ", text: " << x.second->getCSS().text << endl;
        }

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
                std::cout << "class: " << temp->className;
                std::cout << ", text: " << temp->getCSS().text << endl;

                // 将所有兄弟结点入队列
                for(t2Div* c = temp->child; c != NULL; c = c->next)
                    queue.push(c);
            }
            else
                break;
        }

    }
}