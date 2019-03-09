#include <iostream>
using namespace std;

const int ROWS = 5;
const int COLS = 4;

void reset(int a[ROWS][COLS]);

void bubbleSort(int a[ROWS][COLS], int col, bool ascending);
void gappedSort(int a[ROWS][COLS], int col, bool ascending, int gap);
void shellSort(int a[ROWS][COLS], int col, bool ascending);
void insertionSort(int a[ROWS][COLS], int col, bool ascending);
void selectSort(int a[ROWS][COLS], int col, bool ascending);

int binarySearch(int a[ROWS][COLS], int col, int searchFor);

int useSearchSort();
void switchRows(int arr[ROWS][COLS], int a, int b);
void print(int a[ROWS][COLS]);




int useSearchSort(){
    int a[5][4];
    int ip;
    int idx;

    reset(a);
    cout << "Original" << endl;
    print(a);
    cout << "Bubble sort" << endl;
    bubbleSort(a, 0, true);
    print(a);
    reset(a);
    cout << "Select sort" << endl;
    selectSort(a, 1, false);
    print(a);
    reset(a);
    cout << "Shell sort" << endl;
    shellSort(a, 2, true);
    print(a);
    reset(a);

    cout << "Insertion sort" << endl;
    insertionSort(a, 3, true);
    print(a);

    cout << "Last column: ";
    for(int i = 0; i < ROWS; i++){
        cout << a[i][3] << " ";
    }
    cout << endl;

    cout << "Enter a number to search for in the last column: ";
    cin >> ip;
    idx = binarySearch(a, 3, ip);
    cout << ip << ((idx == -1) ? " is not in the last column." : " is located at index " + idx) << endl;
    return 0;
}

void reset(int a[ROWS][COLS]){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            a[i][j] = (i + COLS) * (j + ROWS) % 10;
        }
    }
}

void bubbleSort(int a[ROWS][COLS], int col, bool ascending){
    for(int i = 0; i < ROWS - 1; i++){
        for(int j = 0; j < ROWS - i - 1; j++){
            if(
               (ascending && a[j][col] > a[j + 1][col]) ||
               (!ascending && a[j][col] < a[j + 1][col])
               ){
                switchRows(a, j, j + 1);
            }
        }

    }
}

void gappedSort(int a[ROWS][COLS], int col, bool ascending, int gap){
    for( ; gap >= 1; gap /= 2){
        for(int i = gap; i < ROWS; i++){
            for(int j = i; j >= gap && a[(ascending) ? j - gap : j][col] > a[(ascending) ? j : j - gap][col]; j -= gap){
                switchRows(a, j - gap, j);
                //print(a);
                //uncomment this to see it in action
            }
        }
    }
}

void shellSort(int a[ROWS][COLS], int col, bool ascending){
    gappedSort(a, col, ascending, ROWS / 2);
}

void insertionSort(int a[ROWS][COLS], int col, bool ascending){
    gappedSort(a, col, ascending, 1);
}

void selectSort(int a[ROWS][COLS], int col, bool ascending){
    int idxOfSmallest;
    for(int i = 0; i < ROWS; i++){
        idxOfSmallest = i;
        for(int j = i + 1; j < ROWS; j++){
            if(
               (ascending && a[idxOfSmallest][col] > a[j][col]) ||
                (!ascending && a[idxOfSmallest][col] < a[j][col])
            ){
                idxOfSmallest = j;
            }
        }
        switchRows(a, idxOfSmallest, i);
    }
}

//only works for ascending order
int binarySearch(int a[ROWS][COLS], int col, int searchFor){
    int ret = -1;
    int minIdx = 0;
    int maxIdx = ROWS - 1;
    int midIdx;

    while(minIdx <= maxIdx && ret == -1){
        midIdx = (maxIdx + minIdx) / 2;
        if(a[midIdx][col] == searchFor){
            ret = midIdx;
        } else if(a[midIdx][col] < searchFor){
            minIdx = midIdx + 1;
        } else {
            maxIdx = midIdx - 1;
        }
    }

    return ret;
}

void switchRows(int arr[ROWS][COLS], int a, int b){
    int temp;
    for(int i = 0; i < COLS; i++){
        temp = arr[a][i];
        arr[a][i] = arr[b][i];
        arr[b][i] = temp;
    }
}

void print(int a[ROWS][COLS]){
    cout << "=============" << endl;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << "=============" << endl;
}
