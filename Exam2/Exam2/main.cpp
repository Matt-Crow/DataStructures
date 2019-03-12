#include <iostream>

using namespace std;

void commaRecur(long long num);

int main()
{
    long long ip;
    do{
        cout << endl << "Enter a number: (negative number to quit)";
        cin >> ip;
        if(ip > 0){
            cout << endl << ip << ": " << endl;
            commaRecur(ip);
        }
    } while(ip > 0);
    return 0;
}
