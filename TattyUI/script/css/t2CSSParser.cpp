#include <TattyUI/script/css/t2CSSParser.h>
#include <TattyUI/common/t2Settings.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <TattyUI/script/css/t2CSSBison.hpp>
#include <TattyUI/script/css/t2CSSLex.h>

extern int yyparse(t2CSSAST* ast);

namespace TattyUI
{
    t2CSSParser::t2CSSParser() :bLoaded(false)
    {
        ast = new t2CSSAST();

        if(yylex_init_extra(ast, &ast->scaninfo))
            t2PrintError("Inti alloc failed");
    }

    // 委托构造函数
    t2CSSParser::t2CSSParser(const string& cssPath) :t2CSSParser()
    {
        openFile(cssPath);
    }

    bool t2CSSParser::openFile(const string& cssPath)
    {
        FILE *f = fopen(cssPath.c_str(), "r");
        if(!f)
        {
            printf("Error: open file %s failed!\n", cssPath.c_str());
            bLoaded = false;
            return false;
        }

        yyset_in(f, ast->scaninfo);

        bLoaded = true;
        return true;
    }

    void t2CSSParser::parse()
    {
        if(!bLoaded)
        {
            t2PrintError("file.css haven't loaded yet, can't parse!\n");
            return;
        }

        yyparse(ast);

        preprocessAST();
    }

    void t2CSSParser::preprocessAST()
    {
        if(!ast)
        {
            t2PrintError("Parsing file.css failed.\n");
            return;
        }

        // 完成Node RTTI的初始化工作
        ast->traversal();

        if(ast->root && ast->root->nodeName == "RuleList")
        {
            t2CSSRuleList* root = (t2CSSRuleList*) (ast->root);
            while(root)
            {
                if(root->ruleset)
                    ruleSets.push_back(root->ruleset);

                root = root->ruleList;
            }
        }
        else
            t2Log("Warning: 解析完毕出的AST为空");
    }

    vector<t2CSSSDList*> t2CSSParser::findByClass(const string& className)
    {
        // 根据指定类选择器名查找到的规则集
        vector<t2CSSSDList*> temp;

        for(auto ruleset : ruleSets)
        {
            // selectorList支线
            t2CSSSelectorList* selectorList = ruleset->selectorList;
            while(selectorList)
            {
                // selector支线
                t2CSSSelector* selector = selectorList->selector;
                // .class {}的写法是不被允许的--ver 0.0.8
                // 这里只查找非conditionStatus样式控制下的div 即selector下无第二个selector结点的情况
                if(selector && !selector->selector && selector->simpleSelector)
                {
                    // specifierList支线
                    // 此处不需要使用到simpleSelector中的elementName 目前不支持id选择器
                    // 这里认定选择器书写类型为 .class(:pseudo)->secondPart(:firstPart)
                    // 规定specifierList最多不超过两个子对象 且不支持如下语法 .a.b.c
                    t2CSSNodeSpecifierList *specifierList = NULL;
                    t2CSSNodeSpecifier *slFirstPart = NULL, *slSecondPart = NULL;

                    if(specifierList = selector->simpleSelector->specifierList)
                        slFirstPart = specifierList->specifier;
                    else
                    {
                        t2PrintError("选择器为空的写法存在语法错误");
                        continue;
                    }

                    if(slFirstPart)
                    {
                        if(specifierList = specifierList->specifierList)
                        {
                            if(slSecondPart = specifierList->specifier)
                            {
                                // 保证返回的ruleset中不会包含任何错误语法出现
                                if((slFirstPart->type == T2CSS_CLASS) && (slSecondPart->type == T2CSS_CLASS))
                                {
                                    t2Log("Unsupported: <div class = \"a \"b>中的空格是不允许的\n");
                                    continue;
                                }
                                else if((slFirstPart->type == T2CSS_PSEUDO) && (slSecondPart->type == T2CSS_PSEUDO))
                                {
                                    t2PrintError("\":pseudoA:pseudoB\"的写法存在语法错误");
                                    continue;
                                }
                                else if((slFirstPart->type == T2CSS_CLASS) && (slSecondPart->type == T2CSS_PSEUDO))
                                {
                                    t2PrintError("\":pseudoA.classB\"的写法存在语法错误");
                                    continue;
                                }
                                else
                                {
                                    if(className == slSecondPart->selectorName)
                                        // 标准.class:pseudo{}模式
                                        temp.push_back(new t2CSSSDList(selector->simpleSelector->specifierList, ruleset->declarationList));
                                }
                            }
                            else
                            {
                                t2Log("Unsupported: 未知的语法\n");
                                continue;
                            }
                        }
                        else
                        {
                            // 缺省伪类选择器部分
                            if(slFirstPart->type == T2CSS_CLASS)
                            {
                                // 标准.class{}模式
                                if(className == slFirstPart->selectorName)
                                    temp.push_back(new t2CSSSDList(selector->simpleSelector->specifierList, ruleset->declarationList));
                            }
                            else
                                t2Log("Unsupported: 未知的语法\n");
                        }
                    }
                    else
                    {
                        t2PrintError("选择器为空的写法存在语法错误");
                        continue;
                    }

                    //selector = selector->selector;
                }

                selectorList = selectorList->selectorList;
            }
        }

        return temp;
    }

    bool t2CSSParser::checkDeclaration(t2CSSDeclaration* decl)
    {
        return true;
    }

}