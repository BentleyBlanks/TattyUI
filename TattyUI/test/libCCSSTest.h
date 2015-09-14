#include <TattyUI/TattyUI.h>
#include <memory>
#include <TattyUI/script/css/css.h>
#include <random>

int main()
{
    string test = 
        "{\
            background-color: #d0e4fe;\
            color: orange; \
            text-align: center; \
        }";

    StyleSheet ss;

    StyleSheet::NodeList temp = ss.parse_style(test);
    
    for(StyleSheet::NodeList::iterator it = temp.begin(); it != temp.end(); it++)
    {
        StyleSheet::Node* a = it->get();
        cout << dynamic_cast<StyleSheet::Declaration*>(a)->name_ << ":" << dynamic_cast<StyleSheet::Declaration*>(a)->value_ << endl;
    }

    cout << "-----------------------------" << endl;

    string test2 = 
    "body{\
        background-color: #d0e4fe;\
    }\
    \
    h1{\
        color: orange;\
        text-align: center;\
    }\
    \
    p{\
        font-family: \"Times New Roman\";\
        font-size: 20px;\
    }";
    StyleSheet aa;
    cout << aa.parse(test2) << endl;

    for(StyleSheet::NodePtr b : aa.rules_)
    {
        StyleSheet::Node* bTemp = b.get();
        for(auto selector : ((StyleSheet::Rule*)bTemp)->selectors_)
        {
            cout << selector << endl;
        }

        StyleSheet::NodeList cTemp = ((StyleSheet::Rule*)bTemp)->declarations_;
        for(StyleSheet::NodeList::iterator it = cTemp.begin(); it != cTemp.end(); it++)
        {
            StyleSheet::Node* a = it->get();
            cout << dynamic_cast<StyleSheet::Declaration*>(a)->name_ << ":" << dynamic_cast<StyleSheet::Declaration*>(a)->value_ << endl;
        }
    }

    cout << "-----------------------------" << endl;
    for(auto dTemp : aa.rules_)
    {
        StyleSheet::Node* ddTemp = dTemp.get();
        cout << ((StyleSheet::Rule*)ddTemp)->to_string(&aa) << endl;
    }

    getchar();
    return 0;
}