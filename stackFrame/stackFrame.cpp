#include <iostream>

using namespace std;

int* prevAddr = 0;

int factorial(int factor, int sum){
    cout << "Stack frame takes up " << prevAddr - &factor << endl;
    prevAddr = &factor;
    cout << "Inside factorial, factor: " << &factor << " sum: " << &sum << endl;
    if(factor > 1){
        return factor * factorial(factor - 1, sum);
    }
}

int main(){
    factorial(5, 0);
    return 0;
}
