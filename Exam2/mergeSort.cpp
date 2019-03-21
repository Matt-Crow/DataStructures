#include <iostream>

using namespace std;

void print(int a[], int length);

void merge(int a[], int start, int end, int origLength){
    int middle = (end - start) / 2;

    int b[origLength];
    for(int i = start; i < end; i++){
        b[i] = a[i];
    }
    int i = start; //start of "first array"
    int j = middle + 1; //start of "second array"
    int k = start; //current index of "merged array"

    while(i <= middle && j <= end){
        if(a[i] <= a[j]){
            b[k] = a[j];
            j++;
        } else {
            b[k] = a[i];
            i++;
        }
        k++;
    }

    for(int i = start; i < end; i++){
        a[i] = b[i];
    }
}

void mergeSort(int a[], int start, int end, int origLength){
    if(start < end){
        int mid = (end - start) / 2;
        cout << start << " " << end << endl;
        mergeSort(a, start, mid, origLength);
        //mergeSort(a, mid + 1, end, origLength);
        //the second mergeSort is causing problems
        merge(a, start, end, origLength);
    }
}
