#include <iostream>
#include <fstream>

using namespace std;

int length(char cStr[]);
void stringCopy(char* &a, char* b);

//nd
bool stringCompare(char* a, char* b){
    bool ret = false;
    return ret;
}

//nd
void stringConcatenation(char* a, char* b){

}

int stringPosition(char* a, char b);
int stringLength(char* &a);
char* cStrToPtr(char cStr[]);

ifstream in = ifstream("input.txt");

int main(){
    char str[] = "Testing";
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
        cout << "Read in " << input[ipIdx] << endl;
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

    newStr = (char*)malloc(sizeof(char) * (length + 2));

    char lenChar = (char) (48 + length); //ASCII character index. Note that this breaks for lengths > 9

    *(newStr) = lenChar;

    int idx = 0;
    while(*(a + idx) != '\0'){
        *(newStr + idx + 1) = *(a + idx);
        idx++;
    }
    *(newStr + length + 1) = '\0';
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
