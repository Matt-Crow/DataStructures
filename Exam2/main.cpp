#include <iostream>

using namespace std;

void commaRecur(long long num);
int sumRecur(int num);
int useRadixSort();
int useMergeSort();
int useQuickSort();
int useSearchSort();

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

    //useMergeSort();
    useQuickSort();
    //useSearchSort();

    return 0;
}
