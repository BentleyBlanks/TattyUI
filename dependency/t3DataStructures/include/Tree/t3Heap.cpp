#include <Tree/t3Heap.h>

#include <Common/t3DataStructuresSettings.h>

t3HeapADT::t3HeapADT():n(0), elements(NULL), length(T3_HEAP_DEFAULT_LENGTH)
{
    enlarge();
}

//bool t3HeapADT::isFull()
//{
//    
//}

bool t3HeapADT::isEmpty()
{
    return !n;
}

void t3HeapADT::insert(int data)
{
    n++;
    if(n > length)
        enlarge();
    
    // 缺省
}

// 删除堆中最大的元素
t3TreeNode* t3HeapADT::remove()
{
    // 缺省
    return NULL;
}

void t3HeapADT::enlarge()
{
    if(elements)
    {
        t3Log("t3HeapADT: enlarge!");
        
        int orignalLength = length;
        // 扩增两倍
        length = 2 * orignalLength;
        
        t3HeapElement *temp = new t3HeapElement[length]();
        
        // 数据迁移
        for(int i=0; i<orignalLength; i++)
        {
            temp[i] = elements[i];
        }
        
        // 销毁原数据内容
        delete elements;
        elements = temp;
    }
    else
    {
        // 初始化
        elements = new t3HeapElement[T3_HEAP_DEFAULT_LENGTH]();
        
        length = T3_HEAP_DEFAULT_LENGTH;
    }
}