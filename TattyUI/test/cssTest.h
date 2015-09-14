#include <TattyUI/TattyUI.h>
#include <regex> 

#define T2_CPPREGEX_TEST

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

#endif // T2_CPPREGEX_TEST

    getchar();
    return 0;
}