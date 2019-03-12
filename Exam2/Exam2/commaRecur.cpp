#include <iostream>
using namespace std;

void commaRecur(long long num);

void commaRecur(long long num){
    if(num < 1000){
        cout << num;
    } else {
        commaRecur(num / 1000);
        cout << ',';
        if(num % 1000 < 10){
            cout << "00";
        } else if(num % 1000 < 100){
            cout << "0";
        }
        cout << num % 1000;
    }
}
