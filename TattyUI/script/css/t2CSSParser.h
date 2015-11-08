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

    // t2CSSSelector* + t2CSSNodeSpecifierList* + t2CSSDeclarationList*
    class t2CSSSSDList
    {
    public:
        t2CSSSSDList() :selector(NULL), specifierList(NULL), declarationList(NULL){}
        t2CSSSSDList(t2CSSSelector* selector, t2CSSNodeSpecifierList* sl, t2CSSDeclarationList* dl) :selector(selector), specifierList(sl), declarationList(dl) {}

        // selector后有结点时 specifierList指向使用空格隔开的选择器列表中的最后一个选择器
        t2CSSSelector* selector;
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

        // 查找所有css控制的指定className的AST枝干
        vector<t2CSSSSDList*> findByClass(const string& className);
        
        // 检查给定specifierList语法错误 并完成firstPart:secondPart部分初始化工作
        bool checkSpecifierList(t2CSSNodeSpecifierList* specifierList, t2CSSNodeSpecifier** firstPart, t2CSSNodeSpecifier** secondPart);

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
