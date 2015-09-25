#ifndef T2_DIV_CONTROLLER_H
#define T2_DIV_CONTROLLER_H

#include <TattyUI/div/t2Div.h>
#include <map>

// --!此处应注意耦合
#include <TattyUI/script/css/t2CSSParser.h>

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

		t2Div* getRoot();

        void addDiv(string id, t2Div* div);

        void deleteDiv(string id);

        // 确定id的div已被创建
        t2Div* operator[](string id);

        // 查询是否存在
        t2Div* find(string id);

        t2Div* findByClass(string className);

        void onMousePressed(int x, int y, int px, int py, int button);

        void onMouseReleased(int x, int y, int px, int py, int button);

        void onMouseMoved(int x, int y, int px, int py);

        void onMouseScrolled(int x, int y, int px, int py);

        void onKeyPressed(int key);

        void onKeyReleased(int key);

        void print();

    private:		
        friend class t2CSSController;

        friend class t2LayoutController;

        // 非常严格的单例模式
        t2DivController();
        t2DivController(const t2DivController&) {}
        ~t2DivController() {}
        t2DivController& operator=(const t2DivController& event) const {}

        // string代表id id可以为手动指定也可以是系统指定
        // 外部无法获取非手动指定的div
        std::map<string, t2Div*> divTable;

        // 所有实际遍历开始位置
        t2Div* root;
    };
}

#endif
