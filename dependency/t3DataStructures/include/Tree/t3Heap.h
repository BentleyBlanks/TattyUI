#ifndef T3_HEAP_H
#define T3_HEAP_H

#include <Tree/t3BinaryTree.h>
#include <stdio.h>

class t3HeapElement
{
public:
    t3HeapElement():key(0){}
    
    t3HeapElement(t3HeapElement& e){this->key = e.key;}
    
    int key;
};

// 使用数组完成的最大堆 而非链表形式
class t3HeapADT
{
public:
    t3HeapADT();
    
    //bool isFull();
    
    bool isEmpty();
    
    void insert(int data);
    
    // 删除堆中最大的元素
    t3TreeNode* remove();
    
    t3HeapElement *elements;
    
    // 当前堆中数量
    int n;
    
    // 当前可存放最大元素
    int length;
private:
    // 尽量不要扩建，效率很低
    void enlarge();
};

#endif
