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

    ofstream out = ofstream("quickSortIp.txt");
    for(int i = 0; i < length; i++){
        out << a[i] << " ";
    }

    return 0;
}



void quickSort(int a[], int start, int end){
    if(start < end){
        int mid = partition(a, start, end);
        quickSort(a, start, mid - 1);
        quickSort(a, mid + 1, end);
    }
}
int partition(int a[], int start, int end){
    int pivotValue = a[end];
    int i = start - 1;
    int temp;
    for(int j = start; j <= end - 1; j++){
        if(a[j] >= pivotValue){
            i++;
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
    }
    temp = a[i + 1];
    a[i + 1] = a[end];
    a[end] = temp;
    return i + 1;
}

void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << "#" << i + 1 << ": " << a[i] << endl;
    }
}
