#include "misc.h"
#include <iostream>

using namespace std;

void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

char toChar(int i){
    //supports hexadecimal
    char ret = (char)(48 + i);
    if(i >= 10){
        ret = (char)(65 + i - 10);
    }
    return ret;
}
