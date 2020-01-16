#include <iostream>
#include "stack.h"
#include "queue.h"
#include "linkedList.h"

int main(){
    int ip = 0;
    do{
        std::cout << "1: test stack" << std::endl;
        std::cout << "2: test queue" << std::endl;
        std::cout << "3: test linked list" << std::endl;
        std::cout << "-1: Quit" << std::endl;
        std::cout << "Please choose an option: ";
        std::cin >> ip;
        switch(ip){
            case 1:
                Stack<int>::test();
                break;
            case 2:
                Queue<int>::test();
                break;
            case 3:
                LinkedList<int>::test();
                break;
        }
    } while(ip != -1);
}
