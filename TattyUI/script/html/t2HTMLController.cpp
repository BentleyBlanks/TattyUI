#include <TattyUI/script/html/t2HTMLController.h>
#include <TattyUI/script/html/t2HTMLParser.h>

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
    }
}