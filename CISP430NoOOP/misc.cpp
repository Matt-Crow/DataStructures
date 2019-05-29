#include "misc.h"
#include <iostream>

using namespace std;

void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

bool isPrime(int num){
    bool ret = true;
    ret = !(num%2 == 0); //get rid of evens
    //doesn't enter loop with 1, but defaults to true
    for(int i = 3; ret && i < num; i+=2){
        ret = !(num%i == 0);
    }
    return ret;
}

int prevPrime(int num){
    int ret = num - 1;
    while(ret > 1){
        if(isPrime(ret)){
            break;
        } else {
            ret--;
        }
    }
    return ret;
}

char toChar(int i){
    //supports hexadecimal
    char ret = (char)(48 + i);
    if(i >= 10){
        ret = (char)(65 + i - 10);
    }
    return ret;
}
