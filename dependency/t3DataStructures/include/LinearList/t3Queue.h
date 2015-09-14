#ifndef T3_QUEUE_H
#define T3_QUEUE_H

#include <Common/t3DataStructuresSettings.h>
#include <Common/t3Test.h>
#include <iostream>

template <class T>
class t3Queue
{
public:
    t3Queue();
    
    ~t3Queue();
    
    // 放入给定值的拷贝
    void push(T &value);
    
    bool isEmpty();
    
    bool isFull();
    
    // 获取栈顶元素值
    T get();
    
    // 弹出队列头部元素并返回
    T pop();
    
    void print();
    
private:
    // 尽量不要扩建，效率很低
    void enlarge();
    
    // 队列头
    T *head;
    
    // 首尾指针 front指向队列头部元素的前一个元素 rear指向队尾位置
    int front, rear;
    
    // C/C++无法记住申请的指针指向的内存长度大小
    int length;
};

template<class T>
t3Queue<T>::t3Queue():head(NULL), front(0), rear(0)
{
    enlarge();
}

template <class T>
t3Queue<T>::~t3Queue()
{
    delete head;
    head = NULL;
}

// 放入给定值的拷贝
template <class T>
void t3Queue<T>::push(T &value)
{
    if(isFull())
        enlarge();
    
    rear = (rear + 1) % length;
    head[rear] = value;
}

// 获取栈顶元素值
template <class T>
T t3Queue<T>::get()
{
    if(isEmpty())
    {
        t3PrintError("队列为空，无法获取元素");
        return NULL;
    }
    else
        return head[front];
}

// 弹出队列头部元素并返回
template <class T>
T t3Queue<T>::pop()
{
    if(isEmpty())
    {
        t3PrintError("队列为空，无法获取元素");
        return NULL;
    }
    else
    {
        front = (front + 1) % length;
        return head[front];
    }
}

template <class T>
void t3Queue<T>::enlarge()
{
    if(head)
    {
        t3Log("t3Queue: enlarge!");
        
        int orignalLength = length;
        // 扩增两倍
        length = 2 * orignalLength;
        
        T *temp = new T[length]();
        
        // 因为为循环队列的缘故 这里不能直接内存复制 不然中间会有隔断
        //memcpy(temp, head, sizeof(T) * length);
        for(int i = (front + 1) % orignalLength, j = 1; j<=orignalLength-1; i = (i + 1) % orignalLength, j++)
        {
            temp[j] = head[i];
        }
        
        // 销毁原数据内容
        delete head;
        head = temp;
        
        front = 0;
        rear = orignalLength-1;
    }
    else
    {
        // 初始化
        head = new T[T3_QUEUE_DEFAULT_LENGTH]();
        
        length = T3_QUEUE_DEFAULT_LENGTH;
        // 栈顶
        front = rear = 0;
    }
}

template <class T>
bool t3Queue<T>::isEmpty()
{
    if(front == rear)
        return true;
    else
        return false;
}

template <class T>
bool t3Queue<T>::isFull()
{
    // 规定环形队列最多容纳length-1个元素
    if(((rear + 1) % length) == front)
        return true;
    else
        return false;
}

template <class T>
void t3Queue<T>::print()
{
    t3Log("------------------------------------------\n");
//    for(int i = (front + 1) % length; i<=rear; i = (i + 1) % length)
//    {
//        std::cout << "t3Queue[" << i << "]: " << head[i] << std::endl;
//    }
    for(int i = 0; i<length; i++)
    {
        std::cout << "t3Queue[" << i << "]: " << head[i];
        
        if(i == front)
            std::cout << "  <----front";
        if(i == rear)
            std::cout << "  <----rear";
        
        std::cout << std::endl;
    }
    t3Log("\nMax Length: %d", length);
    t3Log("------------------------------------------\n");
}

#endif
