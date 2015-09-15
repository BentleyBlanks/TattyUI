#ifndef T2_CSSCONTROLLER_H
#define T2_CSSCONTROLLER_H

#include <vector>
#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
    using namespace std;
	class t2ClassSelector;
    class t2Style;
    class t2Declaration;
    class t2CSSParser;
    class t2Div;

    // 完成css向divTable初始化的过程
    class t2CSSController
    {
    public:
        static t2CSSController* getInstance();

        // 加载并完成css对div的style初始化
        void loadCSS(vector<string> filePaths);

		bool findByClass(vector<t2ClassSelector*> names, const string& className);

        vector<t2CSSParser*> parsers;

    private:
		// 
		void toDiv(t2Div* div);

        // 应用样式至所有子节点
        void toChild(t2Declaration* decl, t2Div* div);

        // 应用css至样式
        void toStyle(t2Declaration* decl, t2Style& css);

        // 将样式应用至还未赋值的状态样式
        void toStatus(t2Declaration* decl, t2Div* div);

        t2CSSController();
        t2CSSController(const t2CSSController&) {}
        ~t2CSSController() {}
        t2CSSController& operator=(const t2CSSController& event) const {}
    };
}

#endif