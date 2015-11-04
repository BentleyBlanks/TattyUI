#ifndef T2_CSSNODE_H
#define T2_CSSNODE_H

#include <iostream>
#include <string>

#define ENABLE_PRINT_TEST

enum t2CSSSpecifierType
{
	// 元素选择器
	T2CSS_ELEMENT,
	// id选择器
	T2CSS_ID,
	// 类选择器
	T2CSS_CLASS,
	// 属性选择器
	T2CSS_ATTRIB,
	// 伪类选择器
	T2CSS_PSEUDO
};

enum t2CSSTermType
{
	T2CSS_INTERGER,
	T2CSS_FLOAT,
	T2CSS_PERCENTAGE,
	// 带一元运算符term
	T2CSS_UNARY_OPERATOR_INTERGER,
	T2CSS_UNARY_OPERATOR_FLOAT,
	T2CSS_STRING,
	T2CSS_IDENT,
	// 无符号dimen
	T2CSS_DIMEN,
	// 带一元运算符dimen
	T2CSS_UNARY_OPERATOR_UNARY_DIMEN,
	// url("")/url('')
	T2CSS_URI,
	T2CSS_UNICODERANGE,
	// 十六进制
	T2CSS_HEX,
	// #term
	T2CSS_POUND_TERM,
	// %term
	T2CSS_PERCENT_TERM
};

class t2CSSNode
{
public:
    t2CSSNode() { nodeName = "Node"; }

	virtual t2CSSNode* leftChild(){ return NULL; }
	virtual t2CSSNode* rightChild(){ return NULL; }
	virtual void node(){ 
#ifdef ENABLE_PRINT_TEST
		// std::cout << nodeName << std::endl; 
#endif
	}

	// --!Debug:结点名
	std::string nodeName;
};

// 选择器
class t2CSSNodeSpecifier : public t2CSSNode
{
public:
	t2CSSNodeSpecifier():type(T2CSS_ELEMENT){ nodeName = "Specifier"; }

	virtual t2CSSNode* leftChild(){ 
#ifdef ENABLE_PRINT_TEST
		//// std::cout << selectorName << std::endl; 
#endif
		return NULL; 
	}

	virtual t2CSSNode* rightChild(){ return NULL; }
	virtual void node(){ 
#ifdef ENABLE_PRINT_TEST
		// std::cout << nodeName << std::endl; 

		// std::cout << "---->Type:";
		switch(type)
		{
			// 元素选择器
			case T2CSS_ELEMENT:
				nodeName = "SpecifierElement";
				// std::cout << "Element" << std::endl;
				break;
			// id选择器
			case T2CSS_ID:
				nodeName = "SpecifierID";
				// std::cout << "ID" << std::endl;
				break;
			// 类选择器
			case T2CSS_CLASS:
				nodeName = "SpecifierClass";
				// std::cout << "Class" << std::endl;
				break;
			// 属性选择器
			case T2CSS_ATTRIB:
				nodeName = "SpecifierAttribute";
				// std::cout << "Attribute" << std::endl;
				break;
			// 伪类选择器
			case T2CSS_PSEUDO:
				nodeName = "SpecifierPseudo";
				// std::cout << "Pseudo" << std::endl;
				break;
		}	
#endif
	}

	// 选择器类型
	t2CSSSpecifierType type;

	// 具体选择器名
	std::string selectorName;
};

class t2CSSNodeSpecifierList : public t2CSSNode
{
public:
	t2CSSNodeSpecifierList():specifier(NULL), specifierList(NULL){ nodeName = "SpecifierList"; }

	virtual t2CSSNode* leftChild(){ return specifier; }
	virtual t2CSSNode* rightChild(){ return specifierList; }

	// 这里默认specifierList = NULL TattyUI不支持.a.b{}此类写法
	t2CSSNodeSpecifier* specifier;
	t2CSSNodeSpecifierList* specifierList;
};

class t2CSSSimpleSelector : public t2CSSNode
{
public:
	t2CSSSimpleSelector():specifierList(NULL){ nodeName = "SimpleSelector"; }

	virtual t2CSSNode* leftChild(){ 
#ifdef ENABLE_PRINT_TEST
		//// std::cout << elementName << std::endl; 
#endif
		return NULL; 
	}

	virtual t2CSSNode* rightChild(){ return specifierList; }

	// 元素名 大多数情况下为空
	std::string elementName;
	t2CSSNodeSpecifierList* specifierList;
};

class t2CSSSelector : public t2CSSNode
{
public:
	t2CSSSelector():selector(NULL), simpleSelector(NULL){ nodeName = "Selector"; }

	virtual t2CSSNode* leftChild(){ return simpleSelector; }
	virtual t2CSSNode* rightChild(){ return selector; }

	// 为支持.a .b{}这种层序选择器
	t2CSSSelector* selector;
	t2CSSSimpleSelector* simpleSelector;
};

class t2CSSSelectorList : public t2CSSNode
{
public:
	t2CSSSelectorList():selectorList(NULL), selector(NULL){ nodeName = "SelectorList"; }

	virtual t2CSSNode* leftChild(){ return selectorList; }
	virtual t2CSSNode* rightChild(){ return selector; }

	// 若当前规则只有一个选择器.a{} 那么selectorList为空
	t2CSSSelectorList* selectorList;
	t2CSSSelector* selector;
};

// 声明
class t2CSSTerm : public t2CSSNode
{
public:
	t2CSSTerm():termType(T2CSS_INTERGER){ nodeName = "Term"; }

    bool isNumber(){
        if(termType == T2CSS_INTERGER || termType == T2CSS_FLOAT)
            return true;
        else
            return false;
    }
    
    bool isString(){ return (termType == T2CSS_STRING); }

    bool isColor() { 
        if(termType == T2CSS_IDENT || termType == T2CSS_HEX)
            return true;
        else
            return false;
    }

    bool isKeyword() { return (termType == T2CSS_IDENT); }

	virtual t2CSSNode* leftChild(){ return NULL; }
	virtual t2CSSNode* rightChild(){ return NULL; }
	virtual void node(){ 
#ifdef ENABLE_PRINT_TEST
		// std::cout << nodeName << std::endl;

		// std::cout << "---->Type:";
		switch(termType)
		{
			case T2CSS_INTERGER:
				nodeName = "TermInteger";
				// std::cout << "Integer" << std::endl;
				break;

			case T2CSS_FLOAT:
				nodeName = "TermFloat";
				// std::cout << "Float" << std::endl;
				break;

			case T2CSS_PERCENTAGE:
				nodeName = "TermPercentage";
				// std::cout << "Percentage" << std::endl;
				break;

			// 带一元运算符term
			case T2CSS_UNARY_OPERATOR_INTERGER:
				nodeName = "TermUnary Operator Interger";
				// std::cout << "Unary Operator Interger" << std::endl;
				break;

			case T2CSS_UNARY_OPERATOR_FLOAT:
				nodeName = "TermUnary Operator Float";
				// std::cout << "Unary Operator Float" << std::endl;
				break;

			case T2CSS_STRING:
				nodeName = "TermString";
				// std::cout << "String" << std::endl;
				break;

			case T2CSS_IDENT:
				nodeName = "TermIndent";
				// std::cout << "Indent" << std::endl;
				break;

			// 无符号dimen
			case T2CSS_DIMEN:
				nodeName = "TermDimen";
				// std::cout << "Dimen" << std::endl;
				break;

			// 带一元运算符dimen
			case T2CSS_UNARY_OPERATOR_UNARY_DIMEN:
				nodeName = "TermUnary Operator Unary Dimen";
				// std::cout << "Unary Operator Unary Dimen" << std::endl;
				break;

			// url("")/url('')
			case T2CSS_URI:
				nodeName = "TermUrl";
				// std::cout << "Url" << std::endl;
				break;

			case T2CSS_UNICODERANGE:
				nodeName = "TermUnicoderange";
				// std::cout << "Unicoderange" << std::endl;
				break;

			// 十六进制
			case T2CSS_HEX:
				nodeName = "TermHex";
				// std::cout << "Hex" << std::endl;
				break;

			// #term
			case T2CSS_POUND_TERM:
				nodeName = "TermPound Term";
				// std::cout << "Pound Term" << std::endl;
				break;

			// %term
			case T2CSS_PERCENT_TERM:
				nodeName = "TermPercent Term";
				// std::cout << "Percent Term" << std::endl;
				break;
		}
#endif
	}

	// term类型
	t2CSSTermType termType;

	// term名
	std::string termName;
	// value
	float value;
};

class t2CSSExpression : public t2CSSNode
{
public:
	t2CSSExpression():expression(NULL), term(NULL){ nodeName = "Expression"; }

	virtual t2CSSNode* leftChild(){ return expression; }
	virtual t2CSSNode* rightChild(){ return term; }

	// 只有为margin: 1, 2, 3, 4;这类表达式集 那么expr非空
	t2CSSExpression* expression;
	t2CSSTerm* term;
};

class t2CSSDeclaration : public t2CSSNode
{
public:
	t2CSSDeclaration():expression(NULL){ nodeName = "Declaration"; }

	virtual t2CSSNode* leftChild(){ 
#ifdef ENABLE_PRINT_TEST
		//// std::cout << property << std::endl; 
#endif
		return NULL; }
	virtual t2CSSNode* rightChild(){ return expression; }

	// 属性名
	std::string property;
	t2CSSExpression* expression;
};

class t2CSSDeclarationList : public t2CSSNode
{
public:
	t2CSSDeclarationList():declarationList(NULL), declaration(NULL){ nodeName = "DeclarationList"; }

	virtual t2CSSNode* leftChild(){ return declarationList; }
	virtual t2CSSNode* rightChild(){ return declaration; }

	// 只有声明不止一个时 declarationList才不为空
	t2CSSDeclarationList* declarationList;
	t2CSSDeclaration* declaration;
};

// 规则
class t2CSSRuleset : public t2CSSNode
{
public:
	t2CSSRuleset():selectorList(NULL), declarationList(NULL){ nodeName = "Ruleset"; }

	virtual t2CSSNode* leftChild(){ return selectorList; }
	virtual t2CSSNode* rightChild(){ return declarationList; }

	t2CSSSelectorList* selectorList;
	t2CSSDeclarationList* declarationList;
};

class t2CSSRuleList : public t2CSSNode
{
public:
	t2CSSRuleList():ruleList(NULL), ruleset(NULL){ nodeName = "RuleList"; }

	virtual t2CSSNode* leftChild(){ return ruleList; }
	virtual t2CSSNode* rightChild(){ return ruleset; }

	// 只有当规则不止一条时 ruleList才不为空
	t2CSSRuleList* ruleList;
	t2CSSRuleset* ruleset;
};

#endif
