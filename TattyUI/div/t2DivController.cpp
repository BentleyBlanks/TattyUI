#include <TattyUI/div/t2DivController.h>

namespace TattyUI
{
    t2DivController* t2DivController::getInstance()
    {
        static t2DivController temp;
        return &temp;
    }

    void t2DivController::draw()
    {
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
            it->second->draw();
        }
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

    t2DivController::t2DivController()
    {

    }

    t2Div* t2DivController::operator[](string id)
    {
        return divTable[id];
    }

    t2Div* t2DivController::find(string id)
    {
        std::map<string, t2Div*>::iterator it = divTable.find(id);

        if(it == divTable.end())
        {
            t2Log("未能找到指定id: %s的div", id.c_str());
            return NULL;
        }
        else
            return it->second;
    }

    void t2DivController::onMousePressed(int x, int y, int px, int py, int button)
    {
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
                it->second->onMousePressed(x, y, px, py, button);
        }
    }

    void t2DivController::onMouseReleased(int x, int y, int px, int py, int button)
    {
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
                it->second->onMouseReleased(x, y, px, py, button);
        }
    }

    void t2DivController::onMouseMoved(int x, int y, int px, int py)
    {
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
                it->second->onMouseMoved(x, y, px, py);
        }
    }

    void t2DivController::onMouseScrolled(int x, int y, int px, int py)
    {
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
                it->second->onMouseScrolled(x, y, px, py);
        }
    }

    void t2DivController::onKeyPressed(int key)
    {
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
                it->second->onKeyPressed(key);
        }
    }

    void t2DivController::onKeyReleased(int key)
    {
        for(std::map<string, t2Div*>::iterator it = divTable.begin(); it != divTable.end(); it++)
        {
                it->second->onKeyReleased(key);
        }
    }

}