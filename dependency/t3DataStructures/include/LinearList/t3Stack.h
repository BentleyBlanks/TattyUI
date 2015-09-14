#ifndef T3_STACK_H
#define T3_STACK_H

#include <Common/t3DataStructuresSettings.h>
#include <Common/t3Test.h>
#include <iostream>

template <class T>
class t3Stack
{
public:
    t3Stack();

    ~t3Stack();
    
    // 放入给定值的拷贝
    void push(T &value);
    
    bool isEmpty();
    
    bool isFull();
    
    // 获取栈顶元素值
    T get();
    
    // 弹出栈顶元素并返回
    T pop();
    
    void print();
    
private:
    // 尽量不要扩建，效率很低
    void enlarge();
    
    // 栈头
    T *head;
    
    // 栈顶指针
    int top;
    
    // C/C++无法记住申请的指针指向的内存长度大小
    int length;
};

template <class T>
t3Stack<T>::t3Stack():head(NULL), length(0)
{
    enlarge();
}

template <class T>
t3Stack<T>::~t3Stack()
{
    delete head;
    head = NULL;
}

// 放入给定值的拷贝
template <class T>
void t3Stack<T>::push(T &value)
{
    if(isFull())
        enlarge();
    
    head[++top] = value;
    
    //t3Log("Number Of Elements: %d\n", top+1);
}

// 获取栈顶元素值
template <class T>
T t3Stack<T>::get()
{
    if(isEmpty())
    {
        t3PrintError("栈为空，无法获取元素");
        return T();
    }
    else
        return head[top];
}

// 弹出栈顶元素并返回
template <class T>
T t3Stack<T>::pop()
{
    if(isEmpty())
    {
        t3PrintError("栈为空，无法弹出元素");
        // --!未来应该更改为断言而不是T()
        return T();
    }
    else
    {
        // 实质内容没有被覆盖
        return head[top--];
    }
}

template <class T>
void t3Stack<T>::enlarge()
{
    if(head)
    {
        t3Log("t3Statck: enlarge!");
        
        int orignalLength = length;
        // 扩增两倍
        length = 2 * orignalLength;
        
        T *temp = new T[length]();
        
        // 数据迁移
        //        for(int i=0; i<orignalLength; i++)
        //        {
        //            temp[i] = head[i];
        //        }
        memcpy(temp, head, sizeof(T) * length);
        
        //        // test
        //        for(int i=0; i<orignalLength; i++)
        //        {
        //            t3Log("temp[%d]:%d", i, temp[i]);
        //        }
        
        // 销毁原数据内容
        delete head;
        head = temp;
    }
    else
    {
        // 初始化
        head = new T[T3_STACK_DEFAULT_LENGTH]();
        
        length = T3_STACK_DEFAULT_LENGTH;
        // 栈顶
        top = -1;
    }
}

template <class T>
bool t3Stack<T>::isEmpty()
{
    if(top < 0)
        return true;
    else
        return false;
}

template <class T>
bool t3Stack<T>::isFull()
{
    if(top >= length-1)
        return true;
    else
        return false;
}


template <class T>
void t3Stack<T>::print()
{
    t3Log("------------------------------------------\n");
    for(int i=0; i<=top; i++)
    {
        std::cout << "t3Stack[" << i << "]: " << head[i] << std::endl;
    }
    t3Log("\nMax Length: %d", length);
    t3Log("------------------------------------------\n");
}

#endif