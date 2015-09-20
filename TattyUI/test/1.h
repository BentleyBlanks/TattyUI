#include <TattyUI/TattyUI.h>
#include <regex>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("C:/Users/Bingo/Desktop/1.txt");
    string s, txt;
    while(getline(fin, s))
        txt += s;

    string temp = txt;
    regex re(R"raw(\w+(?=;))raw"), re2(R"raw(\#\w{6})raw");
    smatch m, m2;
    while(regex_search(temp, m, re))
    {
        string x = m[0];

        string y = "else if(!strcmp(value.c_str(), \"";
        y += x;
        y += "\"){";

        cout << y << endl;

        temp = m.suffix().str();
    }

    getchar();
    return 0;
}