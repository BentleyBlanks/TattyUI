#ifndef T2_CSSCONTROLLER_H
#define T2_CSSCONTROLLER_H

#include <vector>
#include <TattyUI/common/t2Settings.h>

class t2CSSDeclaration;

namespace TattyUI
{
    using namespace std;
	class t2ClassSelector;
    class t2Style;
    class t2CSSParser;
    class t2Div;

    // 完成css向divTable初始化的过程
    class t2CSSController
    {
    public:
        static t2CSSController* getInstance();

        // 加载并完成css对div的style初始化
        void loadCSS(vector<string> filePaths);

        vector<t2CSSParser*> parsers;

    private:
        // 应用样式给所有div的普通三状态
        void toDiv();

        void toDivCondition();

		// 应用样式(normal / hover active)至给定div
        void normalStyle(t2Div* div, bool isNormal = true);

        // 应用样式(condition)至给定div
        void conditionStyle(t2Div* div, bool isNormal = true);

        // 应用css至样式
        void toStyle(t2CSSDeclaration* decl, t2Style& css);

        // 应用样式至所有子节点
        // 所需应用的样式是否为Condition
        void toChild(t2CSSDeclaration* decl, t2Div* div, bool isCondition = false);

        // 将样式应用至还未赋值的状态样式
        void toStatus(t2CSSDeclaration* decl, t2Div* div, bool isCondition = false);

        t2CSSController();
        t2CSSController(const t2CSSController&) {}
        ~t2CSSController() {}
        t2CSSController& operator=(const t2CSSController& event) const {}
    };
}

#endif