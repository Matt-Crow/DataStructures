#include <iostream>
#include "Heap.h"

int useStack();
int useQueue();
int useLinkedList();
int useAvlTree();
int useFindPath();
int useSearchSort();

using namespace std;


int main()
{
    //useStack();
    //useQueue();
    //useLinkedList();
    //useAvlTree();
    //useFindPath();
    //useSearchSort();
    Heap<int>::test();
    return 0;
}
