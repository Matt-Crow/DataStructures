#include <iostream>
#include <cstring>

using namespace std;

void print(int a[], int length);
void bubbleSort(int a[], int length);
void selectSort(int a[], int length);
void gappedSort(int a[], int length, int gapSize);
void insertionSort(int a[], int length);
void shellSort(int a[], int length);

int binarySearch(int a[], int length, int searchFor);



int useSearchSort(){
    int a[] = {3, 2, 7, 8, 1, 9, 4, 5, 0, 6};
    int backup[10];
    int ip;
    bool sorted = false;
    memcpy(backup, a, 10 * sizeof(int));

    do {
        cout << "Choose an option:" << endl;
        cout << "0: Print the original array" << endl;
        cout << "1: Reset the array" << endl;
        cout << "2: use bubble sort" << endl;
        cout << "3: use select sort" << endl;
        cout << "4: use insertion sort" << endl;
        cout << "5: use shell sort" << endl;
        cout << "6: use binary search" << endl;
        cout << "-1: quit" << endl;
        cin >> ip;

        switch(ip){
        case 0:
            print(a, 10);
            break;
        case 1:
            memcpy(a, backup, 10 * sizeof(int));
            sorted = false;
            break;
        case 2:
            bubbleSort(a, 10);
            sorted = true;
            cout << "After bubble sort: ";
            print(a, 10);
            break;
        case 3:
            selectSort(a, 10);
            sorted = true;
            cout << "After select sort: ";
            print(a, 10);
            break;
        case 4:
            insertionSort(a, 10);
            sorted = true;
            cout << "After insertion sort: ";
            print(a, 10);
            break;
        case 5:
            shellSort(a, 10);
            sorted = true;
            cout << "After shell sort: ";
            print(a, 10);
            break;
        case 6:
            if(!sorted){
                cout << "Array must be sorted to perform binary search" << endl;
                break;
            }
            cout << "Enter the value to search for: ";
            cin >> ip;
            int idx = binarySearch(a, 10, ip);
            if(idx != -1){
                cout << ip << " is located at index " << idx << endl;
            } else {
                cout << ip << " is not in the array" << endl;
            }
            ip = 6;
        }
    }while(ip >= 0);



    return 0;
}



void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

/*
Pushes largest ints to the top first,
then makes its way down.
Thus, the largest "bubble" to the top
*/
void bubbleSort(int a[], int length){
    int temp;
    for(int i = 0; i < length - 1; i++){
        //at the end of the i'th pass, the i+1
        //largest will be at the end,
        //so no need to check them
        for(int j = 0; j < length - i - 1; j++){
            if(a[j] > a[j + 1]){
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
                print(a, length);
            }
        }
    }
}

/*
finds the smallest element in an array, then puts it
at the beginning.
*/
void selectSort(int a[], int length){
    int temp;
    int idxOfSmallest;
    for(int i = 0; i < length; i++){
        idxOfSmallest = i;
        for(int j = i + 1; j < length; j++){
            if(a[idxOfSmallest] > a[j]){
                idxOfSmallest = j;
            }
        }
        temp = a[idxOfSmallest];
        a[idxOfSmallest] = a[i];
        a[i] = temp;
        print(a, length);
    }
}

void gappedSort(int a[], int length, int gap){
    int temp;
    for( ; gap >= 1; gap /= 2){
        for(int i = gap; i < length; i++){
            for(int j = i; j >= gap && a[j - gap] > a[j]; j -= gap){
                temp = a[j];
                a[j] = a[j - gap];
                a[j - gap] = temp;
                print(a, length);
            }
        }
    }
}

/*
Goes through each element in the array, and shoves it back
until the item to its left is less than it
*/
void insertionSort(int a[], int length){
    gappedSort(a, length, 1);
}

/*
Same as insertion sort, except is compares elements
a set distance, or gap, apart.
This gap keeps shrinking with every pass.
*/
void shellSort(int a[], int length){
    gappedSort(a, length, length / 2);
}

/*
Starts at the middle, keeps cutting in half and choosing
which partition to search next based on whether or not
the middle was less than or greater than searchFor
*/
int binarySearch(int a[], int length, int searchFor){
    int ret = -1;
    int minIdx = 0;
    int maxIdx = length - 1;
    int midIdx;

    while(minIdx <= maxIdx && ret == -1){
        midIdx = (maxIdx + minIdx) / 2;
        if(a[midIdx] == searchFor){
            ret = midIdx;
        } else if(a[midIdx] < searchFor){
            minIdx = midIdx + 1;
        } else {
            maxIdx = midIdx - 1;
        }
    }

    return ret;
}
