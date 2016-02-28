#include <TattyUI/TattyUI.h>
#include <regex> 

using namespace TattyUI;
//#define T2_CPPREGEX_TEST
//#define T2_CSSPARSER_TEST
#define T2_CSSDIV_TEST

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

#ifdef T2_CSSDIV_TEST
    // TattyUI
    //t2WindowBase *window = new t2WindowBase();
    //window->setResizable(true);
    //window->setMode(T2_WINDOW_WINDOWED);
    //window->setup(960, 960);
    //window->setPosition(50, 50);
    //window->setTitle("TattyUI");
    //window->initCallBack();
    //window->setVeticalSync(false);
    t2Window *w = t2Window::getInstance();
    w->setWindowRadius(7);
    w->setTitleBarHeight(48);
    w->init("TattyUI", "../resources/font/Roboto-Regular.ttf", 1280, 800, 200, 200);

    t2Div root(800, 800, "mono", "../resources/font/Roboto-Regular.ttf"),
        div1(300, 120, "mono", "../resources/font/Roboto-Regular.ttf"),
        div2(300, 120, "mono", "../resources/font/Roboto-Regular.ttf"),
        div3(300, 120, "mono", "../resources/font/Roboto-Regular.ttf");

    root.className = "root";
    div1.className = "div1";
    div2.className = "div2";
    div3.className = "div3";

    root.normal.text = "Root";
    div1.normal.text = "Div1";
    div2.normal.text = "Div2";
    div3.normal.text = "Div3";

	root.hover.text = "Root";
	div1.hover.text = "Div1";
	div2.hover.text = "Div2";
    div3.hover.text = "Div3";

	root.active.text = "Root";
	div1.active.text = "Div1";
	div2.active.text = "Div2";
    div3.active.text = "Div3";

    div1.parent = &root;
    div2.parent = &root;
    div3.parent = &root;

    div1.next = &div2;
    div2.next = &div3;

    root.child = &div1;

    root.mouseMovedIn = [](int x, int y, int px, int py)
    {
        t2Log("Root MovedIn\n");
    };

    root.mouseMovedOut = [](int x, int y, int px, int py)
    {
        t2Log("Root MovedOut\n");
    };

    div1.mouseMovedIn = [](int x, int y, int px, int py)
    {
        t2Log("Div1 MovedIn\n");
    };

    div1.mouseMovedOut = [](int x, int y, int px, int py)
    {
        t2Log("Div1 MovedOut\n");
    };

    div2.mouseMovedIn = [](int x, int y, int px, int py)
    {
        t2Log("Div2 MovedIn\n");
    };

    div2.mouseMovedOut = [](int x, int y, int px, int py)
    {
        t2Log("Div2 MovedOut\n");
    };

    div3.mouseMovedIn = [](int x, int y, int px, int py)
    {
        t2Log("Div3 MovedIn\n");
    };

    div3.mouseMovedOut = [](int x, int y, int px, int py)
    {
        t2Log("Div3 MovedOut\n");
    };

    t2Renderer *renderer = t2Renderer::getInstance();
    renderer->setFont("mono");

    t2DivController *divController = t2DivController::getInstance();
    divController->addDiv("div2", &div2);
    divController->addDiv("div1", &div1);
    divController->addDiv("root", &root);
    divController->addDiv("div3", &div3);

    divController->setRoot("root");

    t2CSSController *cssCon = t2CSSController::getInstance();
    vector<string> files;
    files.push_back("../bin/script/css/test2.css");
    cssCon->loadCSS(files);

    divController->init();

    while(1)
    {
        renderer->clear(210, 210, 210);

        renderer->begin();

        divController->draw();

        w->draw();

        renderer->end();

        w->window->swapBuffer();

        w->window->processEvents();
    }
#endif

    getchar();
    return 0;
}