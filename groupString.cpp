#include <iostream>
#include <fstream>

using namespace std;

//nd
void stringCopy(char* a, char* b){

}

//nd
bool stringCompare(char* a, char* b){
    bool ret = false;
    return ret;
}

//nd
void stringConcatenation(char* a, char* b){

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

int main(){
    char str[] = "Testing";
    char* ptr = cStrToPtr(str);
    cout << "Character 'i' is located at index " << stringPosition(ptr, 'i') << " in " << ptr << endl;
    cout << "Length: " << stringLength(ptr) << endl;
    cout << ptr << endl;
    return 0;
}
