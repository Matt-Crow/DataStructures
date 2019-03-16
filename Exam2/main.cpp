#include <iostream>

using namespace std;

void commaRecur(long long num);
int sumRecur(int num);
void radixSort(int a[], int length, bool ascending);
void print(int a[], int length);

int main()
{
    /*
    long long ip;
    do{
        cout << endl << "Enter a number: (negative number to quit)";
        cin >> ip;
        if(ip > 0){
            cout << endl << ip << ": " << endl;
            commaRecur(ip);
        }
    } while(ip > 0);*/
    /*
    int ip;
    do{
        cout << "Enter a number: (negative number to quit) ";
        cin >> ip;
        if(ip > 0){
            cout << "Sum of digits in " << ip << " is " << sumRecur(ip) << endl;
        }
    }while(ip > 0);
    */

    int a[] = {150, 1653, 2412, 111, 994};

    radixSort(a, 5, false);
    print(a, 5);

    return 0;
}
