#include <iostream>
#include <fstream>

using namespace std;

bool containsDelete(string s){
    bool ret = false;
    string checking = "delete";
    int onChar = 0;

    if(s.length() < checking.length()){
        return false;
    }

    //                 something is going wrong with this part
    for(int i = 0; i < s.length() - checking.length() && !ret; i++){
        if(s[i] == checking[0]){
            ret = true;
            for(int j = i; j < s.length() && onChar < checking.length() && ret; j++){
                ret = s[j] == checking[onChar];
                onChar++;
            }
        }
    }

    return ret;
}

bool containsNum(string s){
    bool ret = false;
    for(int i = 0; i < s.length() && !ret; i++){
        ret = isdigit(s[i]);
    }
    return ret;
}

int extractNum(string s){
    int ret = 0;
    for(int i = 0; i < s.length(); i++){
        if(isdigit(s[i])){
            ret *= 10;
            ret += s[i] - 48; //account for ASCII conversion
        }
    }
    return ret;
}

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

int sumRecur(int num, int digits){
    if(digits == 0){
        return num;
    } else {
        return num % 10 + sumRecur(num / 10, digits - 1);
    }
}

int sumRecur(int num){
    int numDigits = 0;
    int absNum = (num >= 0) ? num : -num;
    int divNum = absNum;
    while(divNum > 0){
        numDigits++;
        divNum /= 10;
    }

    //      preserves sign (+-) of original number
    return (num / absNum) * sumRecur(absNum, numDigits);
}

int numIntsInFile(string fileName){
    int ret = 0;
    int dummy;
    ifstream in = ifstream(fileName);
    while(in >> dummy){
        ret++;
    }
    in.close();
    return ret;
}

//convert this to just change a number to a char pointer
int stringLength(char* &a){
    int length = 0;
    char* newStr;

    while(*(a + length) != '\0'){
        length++;
    }

    int digits = 0; //the number of digits in the length of the string
    int remainder = length;
    int tenPow = 1;
    while(remainder > 0){
        remainder /= 10;
        tenPow *= 10;
        digits++;
    }

    newStr = (char*)malloc(sizeof(char) * (length + digits + 1));

    int idx = 0;
    while(idx < digits){
        tenPow /= 10;
        *(newStr + idx) = (char)(length / tenPow % 10 + 48);
        idx++;
    }


    while(*(a + idx - digits) != '\0'){
        *(newStr + idx) = *(a + idx - digits);
        idx++;
    }
    *(newStr + length + digits) = '\0';

    a = newStr;

    return length;
}

/*
Big O: worst case scenario for how many lines of code are run

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
*/
