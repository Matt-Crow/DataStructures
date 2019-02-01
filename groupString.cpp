#include <iostream>
#include <fstream>

using namespace std;

int length(char cStr[]);
void stringCopy(char* &a, char* b);
bool stringCompare(char* a, char* b);

//nd
void stringConcatenation(char* a, char* b){

}

int stringPosition(char* a, char b);
int stringLength(char* &a);
char* cStrToPtr(char cStr[]);

ifstream in = ifstream("input.txt");

int main(){
    char str[] = "Testing for an absurdly long string for 2 digits";
    char* ptr = cStrToPtr(str);
    cout << "Character 'i' is located at index " << stringPosition(ptr, 'i') << " in " << ptr << endl;
    cout << "Length: " << stringLength(ptr) << endl;
    cout << ptr << endl;

    char input[10][100];
    char* ptrs[10];

    int ipIdx = 0;
    while(in.good()){
        in >> input[ipIdx];
        ptrs[ipIdx] = cStrToPtr(input[ipIdx]);
        ipIdx++;
    }
    in.close();

    if(ipIdx >= 2){
        //make sure at least two strings read
        cout << "stringCopy(" << ptrs[0] << ", " << ptrs[1] << ");" << endl;
        cout << ptrs[0] << " becomes ";
        stringCopy(ptrs[0], ptrs[1]);
        cout << ptrs[0] << endl;
    }
    if(ipIdx >= 4){
        cout << "stringCompare(" << ptrs[2] << ", " << ptrs[3] << ");" << endl;
        cout << ptrs[2] << ((stringCompare(ptrs[2], ptrs[3])) ? " is " : " is not ") << ptrs[3] << endl;
    }

    return 0;
}

void stringCopy(char* &a, char* b){
    if(length(a) < length(b)){
        //need to reallocate
        char* newPtr = (char*)malloc(sizeof(char) * (length(b) + 1));
        //delete[] a;
        a = newPtr;
    }
    for(int i = 0; i < length(b) + 1; i++){
        *(a + i) = *(b + i);
    }
}

bool stringCompare(char* a, char* b){
    bool ret = true;

    int idx = 0;
    while(*(a + idx) != '\0' && *(b + idx) != '\0' && ret){
        ret = *(a + idx) == *(b + idx);
        idx++;
    }

    return ret;
}

int stringPosition(char* a, char b){
    int pos = -1;

    for(int i = 0; *(a + i) != '\0' && pos == -1; i++){
        if(*(a + i) == b){
            pos = i;
        }
    }

    return pos;
}

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
    *(newStr + length + digits + 1) = '\0';
    a = newStr;

    return length;
}

//just helper functions I used to write this program
int length(char cStr[]){
    int length = 0;
    while(*(cStr + length) != '\0'){
        length++;
    }
    return length;
}

char* cStrToPtr(char cStr[]){
    char* ret = (char*)malloc(sizeof(char) * (length(cStr) + 1));

    for(int i = 0; i < length(cStr); i++){
        *(ret + i) = *(cStr + i);
    }
    *(ret + length(cStr)) = '\0';

    return ret;
}
