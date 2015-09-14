#include <TattyUI/TattyUI.h>
#include <regex> 

using namespace TattyUI;
//#define T2_CPPREGEX_TEST
#define T2_CSSPARSER_TEST

int main()
{

#ifdef T2_CPPREGEX_TEST

    std::string s("this subject has a submarine as a subsequence");
    std::smatch m;
    std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"  

    std::cout << "Target sequence: " << s << std::endl;
    std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
    std::cout << "The following matches and submatches were found:" << std::endl;

    while(std::regex_search(s, m, e))
    {
        for(auto x : m)
            std::cout << x.str() << " ";
        std::cout << "--> ([^ ]*) match " << m.format("$0") << std::endl;
        s = m.suffix().str();
    }

    //std::cmatch m;

    //std::regex_match("subject", m, std::regex("(sub)(.*)"));

    //std::cout << m.format("the expression matched [$0].\n");
    //std::cout << m.format("with sub-expressions [$1] and [$2].\n");

#endif

#ifdef T2_CSSPARSER_TEST
    t2CSSParser parser("../bin/script/css/test.css");
    //parser.set("\
    //    /*World*/\
    //    body, head, button, hello{\
    //        /****\
    //        * Common multi-line comment style.\
    //        ****/\
    //        /****\
    //        * Another common multi-line comment style.\
    //        */\
    //        background-color: #d0e4fe;\
    //    }\
    //    \
    //    h1, h2, h3, h4{\
    //        color: orange;\
    //        /*Whos*/\
    //        text-align: center;\
    //    }\
    //    \
    //    p{\
    //       font-family: \"Times New Roman\";\
    //       font-size: 20px;\
    //    }\
    //    \
    //    body{\
    //        background - color: #d0e4fe;\
    //    }\
    //    \
    //    h1{\
    //        color: orange;\
    //        text-align: center;\
    //    }\
    //    \
    //    p{\
    //        font-family: \"Times New Roman\";\
    //        \
    //        font-size: 20px;\
    //    }");

    parser.parse();

    cout << "-------------Comment-------------" << endl << endl;
    for(auto c : parser.commentList)
    {
        cout << c->text << endl;
    }

    cout << endl << "-------------Declaration-------------" << endl << endl;

    for(auto t : parser.ruleList)
    {
        for(auto a : t->classSelectors)
        {
            cout << a->classSelector;
            if(a->pseudoSelector != "")
                cout << ":" << a->pseudoSelector;

            cout << "  ";
        }

        for(auto b : t->elementSelectors)
        {
            cout << b->elementSelector;

            if(b->pseudoSelector != "")
                cout << ":" << b->pseudoSelector;

            cout << "  ";
        }

        cout << endl;

        for(auto x : t->declarations)
            cout << "property: " << x->attribute << ": " << x->value << endl;

        cout << endl;
    }

#endif

    getchar();
    return 0;
}