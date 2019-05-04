#include <iostream>
#include <fstream>

using namespace std;

void siftUp(int heap[], int length, int firstEmptyIdx, int i);
void breadthPrint(int heap[], int length, int idx, ostream &output);
//temp
void print(int a[], int len);


int main(){
    int heap[10] = {0};
    for(int i = 1; i < 13; i++){
        siftUp(heap, 10, i - 1, 11 - i);
        print(heap, 10);
    }
    //Insert 10 values into a min-heap from a file.
    //Display the data, level by level.
    //Then delete 5 items.
    //After each delete, display the heap, level by level.
    return 0;
}

void siftUp(int heap[], int length, int firstEmptyIdx, int i){
    //insert into the heap, keep moving up so that the new element is in its proper place
    if(firstEmptyIdx < length){
        heap[firstEmptyIdx] = i;
        int idx = firstEmptyIdx;
        int parentIdx = (idx - 1) / 2;
        int temp;

        //min heap, so each element's children are larger than it
        while(parentIdx >= 0 && idx != 0 && heap[parentIdx] > heap[idx]){
            temp = heap[idx];
            heap[idx] = heap[parentIdx];
            heap[parentIdx] = temp;
            idx = parentIdx;
            parentIdx = (idx - 1) / 2;
            //print(heap, length);
        }
    } else {
        cout << "Invalid index: " << firstEmptyIdx << endl;
    }
}

void breadthPrint(int heap[], int length, int idx, ostream &output){

}

//temp
void print(int a[], int len){
    for(int i = 0; i < len; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}
