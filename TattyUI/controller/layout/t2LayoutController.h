#ifndef T2_LAYOUTCONTROLLER_H
#define T2_LAYOUTCONTROLLER_H


namespace TattyUI
{
    enum T2Layout
    {
        // 线性布局
        T2_LINEAR_LAYOUT,
        // 列表布局
        T2_LIST_LAYOUT
    };

    class t2Div;
    class t2LayoutController
    {
    public:
        static t2LayoutController* getInstance();
        
        // 仅更新div当前状态布局
        void update();

        // div三种状态全局更新
        void updateAll();

    private:
        // 更新指定div的状态数量
        void updateDiv(t2Div* div, bool bCondition = false);

        // 根据div父节点类型将div更新为线性布局方式排列
        void linearLayout(t2Div* div, bool bCondition = false);

        // 根据div父节点类型将div更新为列表布局方式排列
        void listLayout(t2Div* div, bool bCondition = false);

        // 不可删除 不可复制 不可自己创建实例
        t2LayoutController();
        t2LayoutController(const t2LayoutController&) {}
        ~t2LayoutController() {}
        t2LayoutController& operator=(const t2LayoutController& event) const {}
    };
}

#endif