#include "HashArray.h"
#include "../misc.h"
#include <iostream>
#include <cstring>

using namespace std;

HashArray::HashArray(int size)
{
    this->size = size;
    this->a = (int**)(malloc(sizeof(int*) * size));
    memset(a, 0, size);
}

HashArray::~HashArray()
{
    //dtor
}

searchResult* HashArray::put(int val){
    searchResult* ret = new searchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;

    //regular hash
    int address = val % size;
    if(a[address] == 0){
        ret->found = true;
        ret->atIndex = address;
    } else {
        //slot is not empty
        ret->collisions++;
    }

    if(!ret->found){
        //double hash
        int p = prevPrime(size);
        address = p - val%p;
        if(a[address] == 0){
            ret->found = true;
            ret->atIndex = address;
        } else {
            ret->collisions++;
        }
    }

    if(!ret->found){
        //quadratic probe
        searchResult* qp = qpForEmpty(address);
        ret->collisions += qp->collisions;
        if(qp->found){
            ret->found = true;
            ret->atIndex = qp->atIndex;
        }
        delete qp;
    }

    if(!ret->found){
        //linear probe
        searchResult* lp = lpForEmpty(address);
        ret->collisions += lp->collisions;
        if(lp->found){
            ret->found = true;
            ret->atIndex = lp->atIndex;
        }
        delete lp;
    }

    if(ret->found){
        a[ret->atIndex] = new int(val);
    }

    return ret;
}

searchResult* HashArray::get(int val){
    searchResult* ret = new searchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;

    int addr = val%size;
    if(a[addr] && *(a[addr]) == val){
        ret->found = true;
        ret->atIndex = addr;
    } else {
        ret->collisions++;
    }

    if(!ret->found){
        //double hash
        int p = prevPrime(size);
        addr = p - val%p;
        if(a[addr] && *(a[addr]) == val){
            ret->found = true;
            ret->atIndex = addr;
        } else {
            ret->collisions++;
        }
    }

    if(!ret->found){
        //quadratic probe
        searchResult* qp = quadraticProbe(addr, val);
        ret->collisions += qp->collisions;
        if(qp->found){
            ret->found = true;
            ret->atIndex = qp->atIndex;
        }
        delete qp;
    }

    if(!ret->found){
        //linear probe
        searchResult* lp = linearProbe(addr, val);
        ret->collisions += lp->collisions;
        if(lp->found){
            ret->found = true;
            ret->atIndex = lp->atIndex;
        }
        delete lp;
    }

    return ret;
}

void HashArray::print(){
    for(int i = 0; i < size; i++){
        cout << "a[" << i << "]: " << a[i] << " (";
        if(a[i]){
            cout << *(a[i]);
        } else {
            cout << "NULL";
        }
        cout << ")" << endl;
    }
}

searchResult* HashArray::quadraticProbe(int fromIndex, int searchFor){
    searchResult* ret = new searchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;

    int newAddr = 0;
    for(int i = 1; !ret->found && i <= 3; i++){
        newAddr = (fromIndex + i * i) % size;
        if(a[newAddr] && *(a[newAddr]) == searchFor){
            ret->found = true;
            ret->atIndex = newAddr;
        }else{
            ret->collisions++;
        }
    }

    return ret;
}

searchResult* HashArray::qpForEmpty(int fromIndex){
    searchResult* ret = new searchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;

    int newAddr = 0;
    for(int i = 1; !ret->found && i <= 3; i++){
        newAddr = (fromIndex + i * i) % size;
        if(a[newAddr] == 0){
            ret->found = true;
            ret->atIndex = newAddr;
        }else{
            ret->collisions++;
        }
    }

    return ret;
}

searchResult* HashArray::linearProbe(int fromIndex, int searchFor){
    searchResult* ret = new searchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;
    int adr = 0;
    for(int i = 0; i < size && !ret->found; i++){
        adr = (fromIndex + i) % size;
        if(a[adr] && *(a[adr]) == searchFor){
            ret->found = true;
            ret->atIndex = adr;
        } else {
            ret->collisions++;
        }
    }
    return ret;
}

searchResult* HashArray::lpForEmpty(int fromIndex){
    searchResult* ret = new searchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;
    int adr = 0;
    for(int i = 0; i < size && !ret->found; i++){
        adr = (fromIndex + i) % size;
        if(a[adr] == 0){
            ret->found = true;
            ret->atIndex = adr;
        } else {
            ret->collisions++;
        }
    }
    return ret;
}

int HashArray::test(){
    HashArray* a = new HashArray(10);
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
        case 1: {
            cout << "Enter value to insert: ";
            cin >> ip;
            searchResult* res = a->put(ip);
            if(res->found){
                cout << ip << " was inserted at index ";
                cout << res->atIndex << " . Colliding ";
                cout << res->collisions << " times" << endl;
            } else {
                cout << ip << " could not be inserted: the array is full" << endl;
            }
            ip = 1;
            delete res;
            } break;
        case 2: {
            cout << "Enter value to search for: ";
            cin >> ip;
            searchResult* s = a->get(ip);
            if(s->found){
                cout << ip << " was found at index ";
                cout << s->atIndex << " . Colliding ";
                cout << s->collisions << " times" << endl;
            } else {
                cout << ip << " is not in the array" << endl;
            }
            ip = 2;
            delete s;
            } break;
        }
    }while(ip >= 0);

    delete a;
    return 0;
}
