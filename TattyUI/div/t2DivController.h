#ifndef T2_DIV_CONTROLLER_H
#define T2_DIV_CONTROLLER_H

#include <TattyUI/div/t2Div.h>
#include <map>

namespace TattyUI
{
    class t2DivController
    {
    public:
        static t2DivController* getInstance();

        void init();

        //void update();

        void draw();

        bool setRoot(string rootName);

        void addDiv(string id, t2Div* div);

        void deleteDiv(string id);

        // 确定id的div已被创建
        t2Div* operator[](string id);

        // 查询是否存在
        t2Div* find(string id);

        void onMousePressed(int x, int y, int px, int py, int button);

        void onMouseReleased(int x, int y, int px, int py, int button);

        void onMouseMoved(int x, int y, int px, int py);

        void onMouseScrolled(int x, int y, int px, int py);

        void onKeyPressed(int key);

        void onKeyReleased(int key);

    private:		
        // 非常严格的单例模式
        t2DivController();
        t2DivController(const t2DivController&) {}
        ~t2DivController() {}
        t2DivController& operator=(const t2DivController& event) const {}

        std::map<string, t2Div*> divTable;

        // 所有实际遍历开始位置
        t2Div* root;
    };
}

#endif
