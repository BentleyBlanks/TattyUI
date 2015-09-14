#include <TattyUI/script/css/t2CSSController.h>
#include <TattyUI/script/css/t2CSSParser.h>
#include <TattyUI/div/t2DivController.h>

namespace TattyUI
{
    t2DivController *controller = t2DivController::getInstance();

    t2CSSController::t2CSSController()
    {

    }

    t2CSSController* t2CSSController::getInstance()
    {
        static t2CSSController temp;
        return &temp;
    }

    void t2CSSController::loadCSS(vector<string> filePaths)
    {
        // 加载所有css文件
        for(auto file : filePaths)
        {
            t2CSSParser *parser = new t2CSSParser(file);

            parser->parse();

            parsers.push_back(parser);
        }

        // div挂钩css
        for(auto parser : parsers)
        {
            for(auto rule : parser->ruleList)
            {
                for(auto selector : rule->classSelectors)
                {
                    // 类选择器
                    string classSelector;

                    // 伪类
                    string pseudo;

                    t2Div *div = controller->find(selector->classSelector);
                    if(!div)
                        continue;

                    // 属性赋值
                    
                }
            }
        }
    }
}