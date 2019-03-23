#include <iostream>

using namespace std;

void print(int a[], int length);

void merge(int a[], int start, int end, int origLength){
    int middle = (end - start) / 2 + start;
    // if I did (start + end) / 2, this could excede max int size

    int b[origLength];
    for(int i = 0; i < origLength; i++){
        b[i] = a[i];
    }
    int i = start; //start of "first array"
    int j = middle + 1; //start of "second array"
    int k = start; //current index of "merged array"

    cout << "Merging " << i << " " << j << " " << k << endl;
    print(a, origLength);
    while(i <= middle && j <= end){

        if(a[i] <= a[j]){
            b[k] = a[i];
            i++;
        } else {
            b[k] = a[j];
            j++;
        }
        k++;
        print(b, origLength);
    }
    while(i <= middle){
        b[k] = a[i];
        i++;
        k++;
    }
    while(j <= end){
        b[k] = a[j];
        j++;
        k++;
    }


    for(int i = start; i < end; i++){
        a[i] = b[i];
    }
}

void mergeSort(int a[], int start, int end, int origLength){
    if(start < end){
        int mid = (end - start) / 2 + start;
        cout << start << " " << end << endl;
        mergeSort(a, start, mid, origLength);
        mergeSort(a, mid + 1, end, origLength);
        merge(a, start, end, origLength);
    }
}

void mergeSort(int a[], int length){
    mergeSort(a, 0, length - 1, length);
}
