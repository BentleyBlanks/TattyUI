#include <LinkList/t3LinkList.h>
#include <LinearList/t3Stack.h>
#include <Common/t3Test.h>
#include <Common/t3Timer.h>
#include <iostream>

#define MAX_SIZE 24

class t3Equivalence
{
public:
    t3Equivalence(int n):n(n)
    {
        for(int i=0; i<n; i++)
        {
            outs[i] = false;
            seq[i] = new t3LinkListNode<int>();
            seq[i]->next = NULL;
        }
    }
    
    void addPair(int data1, int data2)
    {
        if(data1 >= n || data1 < 0 || data2 >= n)
        {
            t3PrintError("给定位置大小有误, 需在[0, MAX_SIZE)范围内");
            return;
        }
        
        t3LinkListNode<int>* x = new t3LinkListNode<int>();
        // 前缀插入
        x->data = data1;
        x->next = seq[data2];
        seq[data2] = x;
        
        t3LinkListNode<int>* y = new t3LinkListNode<int>();
        // 前缀插入
        y->data = data2;
        y->next = seq[data1];
        seq[data1] = y;
    }
    
    void output()
    {
        for(int i=0; i<n; i++)
        {
            if(outs[i])
                continue;
            
            t3Log("New Class: %d", i);
            outs[i] = true;
            
            // y记录上次循环到的结点
            t3LinkListNode<int> *x = seq[i];
            
            while(1)
            {
                while(x)
                {
                    // 未被输出
                    if(!outs[x->data])
                    {
                        t3Log(", %d", x->data);
                        outs[x->data] = true;
                        
                        // 入栈
                        stack.push(x);
                    }
                    
                    x = x->next;
                }
                
                if(stack.isEmpty())
                    break;
                
                x = seq[stack.pop()->data];
            }
        }
    }
    
    void print()
    {
        for(int i=0; i<n; i++)
        {
            if(!seq[i])
                continue;
            
            t3Log("Seq[%d]: %d", i, seq[i]->data);
            t3LinkListNode<int>* temp = seq[i]->next;
            while(temp)
            {
                t3Log(", %d", temp->data);
                temp = temp->next;
            }
            //t3Log("\n", seq[i]->data);
        }
    }
    
    int n;
    bool outs[MAX_SIZE];
    t3LinkListNode<int>* seq[MAX_SIZE];
    t3Stack<t3LinkListNode<int>*> stack;
};

// P108页寻找等价类
int main(int argc, char* argv[])
{
    t3Equivalence equ(12);
    equ.addPair(0, 4);
    equ.addPair(3, 1);
    equ.addPair(6, 10);
    equ.addPair(8, 9);
    equ.addPair(7, 4);
    equ.addPair(6, 8);
    equ.addPair(3, 5);
    equ.addPair(2, 11);
    equ.addPair(11, 0);
    
    equ.print();
    
    equ.output();
    
    getchar();

    return 0;
}