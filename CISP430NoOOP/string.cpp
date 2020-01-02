#include <iostream>

using namespace std;

char* cStrToPtr(char cStr[]);
int cStrLen(char* ptr);
int findChar(char* ptr, char c);
char* copy(char* ptr);
bool equals(char* ptr1, char* ptr2);
char* concat(char* str1, char* str2);
void print(char* ptr);

int useString(){
    char strIp[100];
    char* ptr = 0;
    int ip = 0;
    char c = ' ';
    bool b = false;

    do{
        cout << "===STRING===" << endl;
        cout << "0: Print the string" << endl;
        cout << "1: Convert a string to a pointer" << endl;
        cout << "2: Find a character in a string" << endl;
        cout << "3: Copy the string" << endl;
        cout << "4: Test for equality" << endl;
        cout << "5: Add to the string" << endl;
        cout << "-1: Quit" << endl;
        cout << "Choose an option: ";
        cin >> ip;
        switch(ip){
        case 0:
            if(!ptr){
                cout << "No string to output" << endl;
            } else {
                print(ptr);
            }
            break;
        case 1:
            cout << "Enter a string: ";
            cin.ignore();
            cin.getline(strIp, 100);
            cout << "You entered: " << strIp << endl;
            delete ptr;
            ptr = cStrToPtr(strIp);
            break;
        case 2:
            if(!ptr){
                cout << "No string to search" << endl;
            } else {
                cout << "Enter a character to search for: ";
                cin >> c;
                ip = findChar(ptr, c);
                if(ip == -1){
                    cout << c << " is not in the string" << endl;
                } else {
                    cout << c << " is located at index " << ip << endl;
                }
                ip = 2;
            }
            break;
        case 3:
            if(!ptr){
                cout << "No string to copy" << endl;
            }else{
                char* dupe = copy(ptr);
                cout << "Original: " << endl;
                print(ptr);
                cout << "Copy: " << endl;
                print(dupe);
                delete dupe;
            }
            break;
        case 4:
            if(!ptr){
                cout << "No string to compare" << endl;
            } else {
                char* c = 0;
                cout << "Enter a string: ";
                cin.ignore();
                cin.getline(strIp, 100);
                cout << "You entered: " << strIp << endl;
                c = cStrToPtr(strIp);
                b = equals(ptr, c);
                if(b){
                    cout << "They are equal" << endl;
                } else {
                    cout << "They are not equal" << endl;
                }
                delete c;
            }
            break;
        case 5:
            if(!ptr){
                cout << "No string to add to" << endl;
            } else {
                char* c = 0;
                char* temp = ptr;
                cout << "Enter a string: ";
                cin.ignore();
                cin.getline(strIp, 100);
                cout << "You entered: " << strIp << endl;
                c = cStrToPtr(strIp);
                ptr = concat(ptr, c);
                delete temp;
                delete c;
            }
            break;
        }
    }while(ip >= 0);

    return 0;
}

char* cStrToPtr(char cStr[]){
    char* ret = 0;
    int letters = cStrLen(cStr);
    ret = (char*)malloc(sizeof(char) * (letters + 1));
    for(int i = 0; i < letters; i++){
        ret[i] = cStr[i];
    }
    ret[letters] = '\0';

    return ret;
}

int findChar(char* ptr, char c){
    int ret = -1;
    int len = cStrLen(ptr);
    for(int i = 0; i < len && ret == -1; i++){
        if(*(ptr + i) == c){
            ret = i;
        }
    }
    return ret;
}

char* copy(char* ptr){
    int len = cStrLen(ptr);
    char* ret = (char*)malloc(sizeof(char) * (len + 1));
    for(int i = 0; i < len; i++){
        ret[i] = ptr[i];
    }
    ret[len] = '\0';
    return ret;
}

bool equals(char* ptr1, char* ptr2){
    bool ret = true;
    if(ptr1 && ptr2){
        int len1 = cStrLen(ptr1);
        int len2 = cStrLen(ptr2);
        if(len1 != len2){
            ret = false;
        }

        for(int i = 0; i < len1 && ret; i++){
            if(*(ptr1 + i) != *(ptr2 + i)){
                ret = false;
            }
        }
    }
    return ret;
}

char* concat(char* str1, char* str2){
    int len1 = cStrLen(str1);
    int len2 = cStrLen(str2);
    char* ret = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
    int idx = 0;
    while(idx < len1){
        ret[idx] = str1[idx];
        idx++;
    }
    while(idx < len1 + len2){
        ret[idx] = str2[idx - len1];
        idx++;
    }
    ret[len1 + len2] = '\0';
    return ret;
}

int cStrLen(char* ptr){
    int len = 0;
    if(ptr){
        while(*(ptr + len) != '\0'){
            len++;
        }
    }
    return len;
}

void print(char* ptr){
    int len = cStrLen(ptr);
    for(int i = 0; i < len; i++){
        cout << "a[" << i << "]: " << (int*)(ptr + i) << " " << *(ptr + i) << endl;
    }
}
