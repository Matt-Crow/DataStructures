#include <iostream>

using namespace std;

void ptrFnct(int* i){
    (*i)++;
}

void amperstanded(int &ampered){
    cout << "Amperstanded variable @" << &ampered << endl;
}
void unamperstanded(int unampered){
    cout << "Original variable     @" << &unampered << endl;
    amperstanded(unampered);
}

void arrayPtr(int* head, int length){
    for(int i = 0; i < length; i++){
        cout << *(head + i);
    }
    cout << endl;
}

void tdArrayPtr(int** head, int d1, int d2){
    for(int i = 0; i < d1; i++){
        for(int j = 0; j < d2; j++){
            cout << **(head + d1 + d2) << " ";
        }
        cout << endl;
    }
}

void allX(char* cString){
    int idx = 0;
    while(*(cString + idx) != '\0'){
        cout << *(cString + idx) << endl;
        *(cString + idx) = 'X';
        idx++;
    }
}

int main(){
    //Iraj streams now, so I can stay home
    int a = 0;
    ptrFnct(&a);
    cout << a << endl;

    char cstring[5] = {"What"};
    cout << cstring << endl;

    unamperstanded(5);

    int arr[] = {1, 2, 3};
    arrayPtr(arr, 3);

    int twoD[2][3];
    for(int td = 0; td < 6; td++){
        *(*twoD + td) = td;
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            cout << twoD[i][j];
        }
        cout << endl;
    }

    //tdArrayPtr(twoD, 2, 3);

    /*
    int (*twoDPtr)[2][3] = &twoD;
    for(int i = 0; i < 6; i++){
        cout << **(*twoDPtr + i) << " ";
    }
    cout << endl;
    */

    char alsoCString[] = "Hello? Does this thing work?";
    cout << "Before: " << alsoCString << endl;
    allX(alsoCString);
    cout << "After:  " << alsoCString << endl;

    return 0;
}
