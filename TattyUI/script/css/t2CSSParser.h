#ifndef T2_CSSPARSER_H
#define T2_CSSPARSER_H

#include <string>
#include <vector>
#include <TattyUI/script/css/t2CSSAST.h>

// 给定css文件输出AST
class t2CSSAST;

namespace TattyUI
{
    using namespace std;

    // t2CSSNodeSpecifierList* + t2CSSDeclarationList*
    class t2CSSSDList
    {
    public:
        t2CSSSDList() :specifierList(NULL), declarationList(NULL){}
        t2CSSSDList(t2CSSNodeSpecifierList* sl, t2CSSDeclarationList* dl) :specifierList(sl), declarationList(dl) {}

        t2CSSNodeSpecifierList* specifierList;
        t2CSSDeclarationList* declarationList;
    };

    class t2CSSParser
    {
    public:
        t2CSSParser();

        t2CSSParser(const string& cssPath);

        bool openFile(const string& cssPath);

        void parse();

        // 查找非conditionStatus下的div样式控制
        vector<t2CSSSDList*> findByClass(const string& className);

        // 检查给定声明是否有语法错误
        bool checkDeclaration(t2CSSDeclaration* decl);

        bool bLoaded;

        t2CSSAST *ast;

        // 实际解析使用剖析AST过后的数据集
        vector<t2CSSRuleset*> ruleSets;

    protected:
        void preprocessAST();
    };
}

#endif
