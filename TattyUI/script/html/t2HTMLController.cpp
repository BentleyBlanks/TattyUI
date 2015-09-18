#include <TattyUI/script/html/t2HTMLController.h>
#include <TattyUI/script/html/t2HTMLParser.h>
#include <TattyUI/script/css/t2CSSController.h>

namespace TattyUI
{
    t2HTMLController::t2HTMLController()
    {

    }

    t2HTMLController* t2HTMLController::getInstance()
    {
        static t2HTMLController temp;
        return &temp;
    }

    void t2HTMLController::loadHTML(vector<string> &htmlPath)
    {
        for(auto path : htmlPath)
        {
            t2HTMLParser* p = new t2HTMLParser();
            p->openFile(path);
            parser.push_back(p);
        }
    }

    void t2HTMLController::parse()
    {
        for(auto p : parser)
            p->parse();

        // 所有html初始化完毕后 初始化css
        for(auto a : parser)
            t2CSSController::getInstance()->loadCSS(a->cssFilePaths);
    }
}