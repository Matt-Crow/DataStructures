#include "HashArray.h"
#include <iostream>
#include <cstring>

using namespace std;

template <class T>
HashArray<T>::HashArray(int size)
{
    this->size = size;
    this->a = (T**)(malloc(sizeof(T*) * size));
    memset(a, 0, size);
}

template <class T>
HashArray<T>::~HashArray()
{
    //dtor
}

template <class T>
searchResult* HashArray<T>::put(T val){
    searchResult* ret = new searchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;



    return ret;
}

template <class T>
void HashArray<T>::print(){
    for(int i = 0; i < size; i++){
        cout << "a[" << i << "]: " << a[i] << "(";
        if(a[i]){
            cout << *(a[i]);
        } else {
            cout << "NULL";
        }
        cout << ")" << endl;
    }
}

template <class T>
int HashArray<T>::test(){
    HashArray<int>* a = new HashArray<int>(10);
    int ip = 0;
    do {
        cout << "###HASH###" << endl;
        cout << "0: Print the array" << endl;
        cout << "1: Insert into the array" << endl;
        cout << "2: Search for a value in the array" << endl;
        cout << "-1: Quit" << endl;
        cout << "Choose an option: ";
        cin >> ip;
        switch(ip){
        case 0:
            a->print();
            break;
        case 1:
            cout << "Enter value to insert: ";
            cin >> ip;
            searchResult* res = a->put(ip);
            if(res->found){
                cout << ip << " was inserted at index "
                cout << res->atIndex << " . Colliding "
                cout << res->collisions << " times" << endl;
            }
            ip = 1;
            delete res;
            break;

        }
    }while(ip >= 0);

    delete a;
    return 0;
}
