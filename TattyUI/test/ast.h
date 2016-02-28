#include <TattyUI/TattyUI.h>
#include <iostream>
#include <fstream>  

using namespace TattyUI;

int main(int argc, char* argv[])
{
    t2CSSParser parser;
    parser.openFile("../bin/script/css/demo.css");
    
    parser.parse();
    if(parser.ast)
        parser.ast->saveAsDot();

    return 0;
}