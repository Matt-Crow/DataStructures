#include <iostream>

using namespace std;

void commaRecur(long long num);
int sumRecur(int num);
int useRadixSort();
void print(int a[], int length);
void mergeSort(int a[], int length);

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

    //useRadixSort();

    int a[] = {8, 5, 3, 1, 9, 0, 2, 3};
    mergeSort(a, 8);
    print(a, 8);

    return 0;
}
