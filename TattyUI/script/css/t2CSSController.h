#ifndef T2_CSSCONTROLLER_H
#define T2_CSSCONTROLLER_H

#include <vector>
#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
    using namespace std;
    class t2CSSParser;

    // 完成css向divTable初始化的过程
    class t2CSSController
    {
    public:
        static t2CSSController* getInstance();

        // 加载并完成css对div的style初始化
        void loadCSS(vector<string> filePaths);

        vector<t2CSSParser*> parsers;

    private:

        t2CSSController();
        t2CSSController(const t2CSSController&) {}
        ~t2CSSController() {}
        t2CSSController& operator=(const t2CSSController& event) const {}
    };
}

#endif