#include <iostream>
using namespace std;

const int ROWS = 5;
const int COLS = 4;

void reset(int a[ROWS][COLS]);

void bubbleSort(int a[ROWS][COLS], int col, bool ascending);
void selectSort(int a[ROWS][COLS], int col, bool ascending);


int useSearchSort();
void switchRows(int arr[ROWS][COLS], int a, int b);
void print(int a[ROWS][COLS]);




int useSearchSort(){
    int a[5][4];

    reset(a);
    print(a);
    cout << "Bubble sort" << endl;
    bubbleSort(a, 0, true);
    print(a);
    reset(a);
    cout << "Select sort" << endl;
    selectSort(a, 1, false);
    print(a);

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
    int temp[COLS];
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
