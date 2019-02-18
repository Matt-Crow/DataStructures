#include <iostream>

using namespace std;

int main(){
    int i = 0;

    int* stackPointer = &i;
    int* heapPointer = (int*)malloc(sizeof(int));
    *heapPointer = 1;

    for(int s = 0; s < 100; s++){
        cout << "At stack address " << (stackPointer + s) << ": " << *(stackPointer + s) << endl;
    }

    for(int h = 0; h < 100; h++){
        cout << "At heap address " << (heapPointer - h) << ": " << *(heapPointer - h) << endl;
    }
}
