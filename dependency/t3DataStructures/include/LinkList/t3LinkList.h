#ifndef T3_LINKLIST_H
#define T3_LINKLIST_H

#include <Common/t3Test.h>
#include <iostream>

template <class T>
class t3LinkListNode
{
public:
    t3LinkListNode():next(NULL){}
    
    void print()
    {
        std::cout << "t3LinkListNode's data:"<< data << std:: endl;
    }
    
    t3LinkListNode* next;
    
    T data;
};

template <class T>
class t3SingleLinkList {
public:
    t3SingleLinkList();
    
    void insert(t3LinkListNode<T> *front, t3LinkListNode<T> *node);
    
    t3LinkListNode<T>* insert(const T &data);
    
    void deleteNode(t3LinkListNode<T> *node);
    
    //O(n)复杂度的单链表翻转
    void invert();
    
    void print();
    
    // 头指针
    t3LinkListNode<T> *head;
};

template <class T>
t3SingleLinkList<T>::t3SingleLinkList():head(NULL)
{

}

//O(n)复杂度的单链表翻转
template <class T>
void t3SingleLinkList<T>::invert()
{
    t3LinkListNode<T> *middle = NULL, *trail, *now = head;
    while(now)
    {
        trail = middle;
        middle = now;
        now = now->next;
        middle->next = trail;
    }
    
    head = middle;
}

template <class T>
t3LinkListNode<T>* t3SingleLinkList<T>::insert(const T &data)
{
    t3LinkListNode<T> *temp = new t3LinkListNode<T>();
    temp->data = data;
    
    if(head)
    {
        insert(head, temp);
    }
    else
    {
        head = temp;
        temp->next = NULL;
    }
    
    return temp;
}

template <class T>
void t3SingleLinkList<T>::insert(t3LinkListNode<T> *front, t3LinkListNode<T> *node)
{
    if(!node || !front)
    {
        t3PrintError("链表待插入结点为空");
        return;
    }
    
    node->next = front->next;
    front->next = node;
}

template <class T>
void t3SingleLinkList<T>::deleteNode(t3LinkListNode<T> *node)
{
    if(!node)
    {
        t3PrintError("链表无法删除空节点");
        return;
    }
    
    t3LinkListNode<T> *front = NULL, *now = head;
    
    while(now && now != node)
    {
        front = now;
        now = now->next;
    }
    
    if(now)
    {
        if(now == node)
        {
            front->next = now->next;
            // 可选不释放这块内存 继续由node保存
            delete now;
            now = NULL;
            node = NULL;
        }
        else
            t3PrintErrorArg("node", node, "无法在链表中找到指定结点");
    }
    else
        t3PrintError("链表为空");
}

template <class T>
void t3SingleLinkList<T>::print()
{
    t3LinkListNode<T> *temp = head;
    while(temp != NULL)
    {
        temp->print();
        temp = temp->next;
    }
}

#endif
