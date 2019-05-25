#include "Heap.h"
#include <iostream>

using namespace std;

template <class T>
Heap<T>::Heap(bool isMinHeap, int size)
{
    this->isMinHeap = isMinHeap;
    this->size = size;
    this->firstEmptyIdx = 0;
    this->arr = new T[size];
}

template <class T>
Heap<T>::~Heap()
{
    delete[] this->arr;
}

template <class T>
bool Heap<T>::siftUp(T data){
    bool canSiftUp = firstEmptyIdx < size;
    if(canSiftUp){
        arr[firstEmptyIdx] = data;
        firstEmptyIdx++;

        //swap until the element is in its proper place
        int idx = firstEmptyIdx - 1; //since we just incremented it
        int parentIdx = (idx - 1) / 2; //since the heap is technically a tree
        T temp;
        while(parentIdx >= 0 && idx != 0 && (
            (isMinHeap && arr[parentIdx] > arr[idx])
            || (!isMinHeap && arr[parentIdx] < arr[idx])
        )){
            temp = arr[idx];
            arr[idx] = arr[parentIdx];
            arr[parentIdx] = temp;
            idx = parentIdx;
            parentIdx = (idx - 1) / 2;
        }

    }
    return canSiftUp;
}

template <class T>
void Heap<T>::print(){
    int row = 0;
    int col = 0;
    int rowWidth = 1;
    cout << "HEAP: " << endl;
    cout << "   Row 0: " << endl;
    cout << "       ";
    for(int i = 0; i < firstEmptyIdx; i++){
        cout << arr[i] << " ";
        col++;
        if(col >= rowWidth && i < firstEmptyIdx - 1){
            row++;
            rowWidth *= 2;
            col = 0;
            cout << endl;
            cout << "   Row " << row << ": " << endl;
            cout << "       ";
        }
    }
    cout << endl;
}

template <class T>
int Heap<T>::test(){
    Heap<int>* minHeap = new Heap<int>(true, 7);
    Heap<int>* maxHeap = new Heap<int>(false, 7);
    int ip;
    bool b;
    do{
        cout << "===HEAP===" << endl;
        cout << "0: Print the min-heap" << endl;
        cout << "1: Print the max-heap" << endl;
        cout << "2: sift up a value to the min-heap" << endl;
        cout << "3: sift up a value to the max-heap" << endl;
        cout << "-1: quit" << endl;
        cout << "Choose an option: ";
        cin >> ip;
        switch(ip){
        case 0:
            minHeap->print();
            break;
        case 1:
            maxHeap->print();
            break;
        case 2:
            cout << "Enter a value to sift up: ";
            cin >> ip;
            b = minHeap->siftUp(ip);
            if(b){
                cout << ip << " was sifted up" << endl;
            } else {
                cout << "The heap is out of open slots. Couldn't sift up " << ip << endl;
            }
            ip = 2;
            break;
        case 3:
            cout << "Enter a value to sift up: ";
            cin >> ip;
            b = maxHeap->siftUp(ip);
            if(b){
                cout << ip << " was sifted up" << endl;
            } else {
                cout << "The heap is out of open slots. Couldn't sift up " << ip << endl;
            }
            ip = 3;
            break;
        }
    }while(ip >= 0);


    delete minHeap;
    return 0;
}
