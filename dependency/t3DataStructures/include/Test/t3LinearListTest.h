#include <LinearList/t3Stack.h>
#include <LinearList/t3Queue.h>

#include <Common/t3Test.h>
#include <Common/t3Timer.h>

#include <iostream>
#include <string>

//#define T3_TEST_MAZE
#define T3_TEST_STACK
//#define T3_TEST_QUEUE

int main(int argc, char* argv[])
{
    t3Timer timer;
    
    std::string command;

    int i;
    
#ifdef T3_TEST_STACK
    t3Stack<int> stack;
    while(1)
    {
        std::cout << "Tatty Console:~dataStructure$ ";
        // 非直接读入一个单词 而为一整个句子
        //std::getline(std::cin, command);
        std::cin >> command;
        
        if(command == "quit")
            break;
        else if(command == "print")
            stack.print();
        else if(command == "push")
        {
            std::cout << "Input push data: ";
            std::cin >> i;
            stack.push(i);
        }
        else if(command == "pop")
            std::cout << "Pop Stack: " << stack.pop() << std::endl;
        else if(command == "get")
            std::cout << "Stack's Top Element: " << stack.get() << std::endl;
        else if(command == "Who's Your Daddy?")
            // 反正cin这辈子也不可能输出这玩意
            std::cout << "I'm Your Father" << std::endl;
        else
            std::cout << "Error Command." << command << std::endl;
    }
#endif
    
#ifdef T3_TEST_QUEUE
    t3Queue<int> queue;
    while(1)
    {
        std::cout << "Tatty Console:~dataStructure$ ";
        // 非直接读入一个单词 而为一整个句子
        //std::getline(std::cin, command);
        std::cin >> command;
        
        if(command == "quit")
            break;
        else if(command == "print")
            queue.print();
        else if(command == "push")
        {
            std::cout << "Input push data: ";
            std::cin >> i;
            queue.push(i);
        }
        else if(command == "pop")
            std::cout << "Pop Queue: " << queue.pop() << std::endl;
        else if(command == "get")
            std::cout << "Queue's Top Element: " << queue.get() << std::endl;
        else
            std::cout << "Error Command." << command << std::endl;
    }
#endif
    getchar();
    return 0;
}