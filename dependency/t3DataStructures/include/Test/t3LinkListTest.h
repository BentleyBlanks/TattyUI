#include <LinkList/t3LinkList.h>
#include <linkList/t3TypeList.h>

#include <Common/t3Test.h>
#include <Common/t3Timer.h>
#include <iostream>

//#define T3_TEST_TYPELIST
#define T3_TEST_LINKLIST

int main(int argc, char* argv[])
{
#ifdef T3_TEST_LINKLIST
    t3SingleLinkList<int> linkList;
    
    t3Log("-------------------------------\n");

    linkList.insert(20);
    linkList.insert(3);
    t3LinkListNode<int>* node = linkList.insert(2);
    linkList.insert(60);
    linkList.insert(28);
    
    linkList.print();
    
    linkList.deleteNode(node);
    
    t3Log("-------------------------------\n");
    linkList.print();
    
    linkList.invert();
    
    t3Log("-------------------------------\n");
    linkList.print();
    
#endif
    
#ifdef T3_TEST_TYPELIST

#endif
    getchar();
    return 0;
}