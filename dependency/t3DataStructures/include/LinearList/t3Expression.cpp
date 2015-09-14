#include <LinearList/t3Expression.h>

// 左括号始终栈外优先级最高始终进栈 在栈内时始终允许其他符号进栈
// 栈内优先级
static int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
// 栈外优先级
static int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

t3Expression::t3Expression()
{
    exp = "";
}

// 给出中缀表达式
void t3Expression::create(std::string s)
{
    exp = s;
}

void t3Expression::toPostfix()
{
    std::string temp;
    int n = 0;
    t3Precedence token = getToken(n);
    while(token != eos)
    {
        if(token == operand)
            temp += getChar(n);
        else if(token == rparen)
        {
            // 直到遇到左括号
            while (!postfixStack.isEmpty() && postfixStack.get() != lparen)
                temp += getSymbol(postfixStack.pop());
            
            // 弹出左括号
            postfixStack.pop();
        }
        else
        {
            // 若栈顶优先级高于栈外符号引入优先级 出栈
            while(!postfixStack.isEmpty() && isp[postfixStack.get()] >= icp[token])
                temp += getSymbol(postfixStack.pop());
            
            postfixStack.push(token);
        }
        
        token = getToken(++n);
    }
    
    // 弹出剩余标记符
    while(!postfixStack.isEmpty() && (token = postfixStack.pop()) != eos)
        temp += getSymbol(postfixStack.pop());
    temp += " ";
    
    exp = temp;
    std::cout << "Infix to Postfix: " << exp << std::endl;
}

int t3Expression::evaluate()
{
    if(exp == "")
        return NULL;
    
    int n = 0, op1 = 0, op2 = 0;
    t3Precedence token = getToken(n);
    while(token != eos)
    {
        // 操作数
        if(token == operand)
        {
            int temp = getChar(n) - '0';
            valueStack.push(temp);
        }
        // 符号
        else
        {
            // 栈中必有两个以上操作数
            op2 = valueStack.pop();
            op1 = valueStack.pop();
            
            int result = 0;
            switch (token) {
                case plus:
                    result = op1+op2;
                    break;
                case minus:
                    result = op1-op2;
                    break;
                case times:
                    result = op1*op2;
                    break;
                case divide:
                    result = op1/op2;
                    break;
                case mod:
                    result = op1%op2;
                    break;
            }
            valueStack.push(result);
        }
        //t3Log("%d", n);
        token = getToken(++n);
    }
    
    return valueStack.pop();
}

t3Precedence t3Expression::getToken(int n)
{
    const char symbol = getChar(n);
    switch (symbol) {
        case '(':
            return lparen;
        case ')':
            return rparen;
        case '+':
            return plus;
        case '-':
            return minus;
        case '/':
            return divide;
        case '*':
            return times;
        case '%':
            return mod;
        case ' ':
            return eos;
        default:
            return operand;
    }
}

const char t3Expression::getChar(int n)
{
    return *exp.substr(n, 1).c_str();
}

const char t3Expression::getSymbol(t3Precedence p)
{
    switch (p) {
        case plus:
            return '+';
        case minus:
            return '-';
        case times:
            return '*';
        case divide:
            return '/';
        case mod:
            return '%';
        default:
            return NULL;
    }
}

void t3Expression::printToken(t3Precedence p)
{
    switch (p) {
        case plus:
            t3Log("+");
            break;
        case minus:
            t3Log("-");
            break;
        case times:
            t3Log("*");
            break;
        case divide:
            t3Log("/");
            break;
        case mod:
            t3Log("%");
            break;
        default:
            break;
    }
}