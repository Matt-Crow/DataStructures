#include <iostream>
#include <assert.h>
using namespace std;

int divide(int a, int b);

int main(){
    int ip1 = 0;
    int ip2 = 0;
    /*
    while(ip1 != -1 && ip2 != -1){
        cin >> ip1 >> ip2;
        cout << divide(ip1, ip2) << endl;
    }*/

    int n = 10;

    //       1     n + 1  n
    for(int i = 0; i < n; i++){
        cout << i << endl; // n
    }
    // big O = 3n + 2 -> n

    //       1     n + 1  n
    for(int i = 0; i < n; i++){

        //                           inner loop run n times
        //      1      n + 1  n
        for(int j = 0; j < n; j++){
            cout << i << " " << j << endl; //n
        }
    }
    //big O = 3n + 2 + n(3n + 2) = 3n^2 + 5n + 2 -> n^2

    return 0;
}

int divide(int a, int b){
    //assert("Cannot divide by 0!", b != 0);
    return a / b;
}
