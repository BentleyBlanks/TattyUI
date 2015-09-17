#ifndef T2_HTMLCOMTROLLER_H
#define T2_HTMLCOMTROLLER_H

#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
    class t2HTMLParser;
    class t2HTMLController
    {
    public:
        static t2HTMLController* getInstance();

        void loadHTML(vector<string> &htmlPath);

        void parse();

    private:
        // 为未来支持多页面做好预留
        vector<t2HTMLParser*> parser;

        t2HTMLController();
        t2HTMLController(const t2HTMLController&) {}
        ~t2HTMLController() {}
        t2HTMLController& operator=(const t2HTMLController& event) const {}
    };
}

#endif
