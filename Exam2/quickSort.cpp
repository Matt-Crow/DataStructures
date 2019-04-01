#include<iostream>
#include<fstream>

using namespace std;

void quickSort(int a[], int start, int end);
int partition(int a[], int start, int end);
void print(int a[], int length);

int useQuickSort(){
    int length = 0;
    int i;
    int idx = 0;
    ifstream ip = ifstream("quickSortIp.txt");
    while(ip >> i){
        length++;
    }
    ip.close();

    int a[length];
    ip = ifstream("quickSortIp.txt");
    while(ip >> i){
        a[idx] = i;
        idx++;
    }

    cout << "Before: " << endl;
    print(a, length);
    quickSort(a, 0, length - 1);
    cout << "After: " << endl;
    print(a, length);

    return 0;
}



void quickSort(int a[], int start, int end){
    if(start < end){
        int mid = partition(a, start, end);
        quickSort(a, start, mid - 1);
        quickSort(a, mid + 1, end);
    }
}

/*
Moves a[end], the PIVOT, to its proper place
in the array, and sorts it so everything to
its left is smaller than it, and everything
to its right is larger.
*/
int partition(int a[], int start, int end){
    int pivotValue = a[end];
    int i = start;
    int temp;
    cout << "Pivot is " << pivotValue << endl;
    for(int j = start; j < end; j++){
        cout << "Checking index " << j << endl;
        if(a[j] <= pivotValue){
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
            i++;
        }
        cout << "Pivot should be moved to " << i << endl;
        print(a, 5);
    }
    temp = a[i];
    a[i] = a[end];
    a[end] = temp;
    return i;
}
/*
void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << "#" << i + 1 << ": " << a[i] << endl;
    }
}*/
