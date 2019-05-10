#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

struct SearchResult{
    bool found;
    int atIndex;
    int collisions;
};

//temp
void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << i << ": " << a[i] << endl;
    }
}

SearchResult* quadraticProbe(int a[], int length, int searchFor, int startAddress);
SearchResult* linearProbe(int a[], int length, int searchFor);

bool isPrime(int num);
int prevPrime(int num);
SearchResult* put(int a[], int length, int i);
SearchResult* get(int a[], int length, int i);


const int NULL_VALUE = INT_MIN;


int main(){
    int size = 10; //size is supposed to be a prime number
    int a[size];
    ifstream in = ifstream("input.txt");
    int ip;
    int ipCount = 0;
    SearchResult* sr;

    for(int i = 0; i < size; i++){
        a[i] = NULL_VALUE; //can't do memset or initializer list
    }

    while(in >> ip && ipCount < size){
        sr = put(a, size, ip);
        if(sr->found){
            cout << "Inserted " << ip << " into the array, colliding " << sr->collisions << " times." << endl;
        } else {
            cout << "Cannot insert " << ip << " into the array: there are no empty indexes. " << endl;
        }

        ipCount++;
    }
    in.close();
    sr = 0;

    delete sr;

    print(a, size);

    return 0;
}
/*
Also,
allow the user to search for a value by prompting the user.
Use the same set of hash functions to look for the item.
If the item has not been found,
then display not in the list.
*/
bool isPrime(int num){
    bool ret = true;
    ret = !(num%2 == 0); //get rid of evens
    //doesn't enter loop with 1, but defaults to true
    for(int i = 3; ret && i < num; i+=2){
        ret = !(num%i == 0);
    }
    return ret;
}

int prevPrime(int num){
    int ret = num - 1;
    while(ret > 1){
        if(isPrime(ret)){
            break;
        } else {
            ret--;
        }
    }
    return ret;
}

SearchResult* quadraticProbe(int a[], int length, int searchFor, int startAddress){
    SearchResult* ret = new SearchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;

    int newAddr = 0;
    for(int i = 1; !ret->found && i <= 3; i++){
        newAddr = (startAddress + i * i)%length;
        if(a[newAddr] == searchFor){
            ret->found = true;
            ret->atIndex = newAddr;
        } else {
            ret->collisions++;
        }
    }

    return ret;
}

SearchResult* linearProbe(int a[], int length, int searchFor){
    SearchResult* ret = new SearchResult;
    ret->found = false;
    ret->atIndex = -1;
    ret->collisions = 0;
    for(int i = 0; !ret->found && i < length; i++){
        if(a[i] == searchFor){
            ret->found = true;
            ret->atIndex = i;
            ret->collisions = i;
            //will collide once for each item we've checked thus far
        }
    }
    return ret;
}

SearchResult* put(int a[], int length, int i){
    SearchResult* searchResult = new SearchResult;
    searchResult->found = false;
    searchResult->atIndex = -1;
    searchResult->collisions = 0;
    int address = i%length;

    if(a[address] == NULL_VALUE){
        searchResult->found = true;
        searchResult->atIndex = address;
    } else {
        //slot is not empty
        searchResult->collisions++;
    }

    if(!searchResult->found){
        //double hash
        int p = prevPrime(length);
        address = p - i%p;
        if(a[address] == NULL_VALUE){
            searchResult->found = true;
            searchResult->atIndex = address;
        } else {
            searchResult->collisions++;
        }
    }

    if(!searchResult->found){
        //quadratic probe
        SearchResult* qp = quadraticProbe(a, length, NULL_VALUE, address);
        searchResult->collisions += qp->collisions;
        if(qp->found){
            searchResult->found = true;
            searchResult->atIndex = qp->atIndex;
        }
    }
    if(!searchResult->found){
        //linear probe
        SearchResult* lp = linearProbe(a, length, NULL_VALUE);
        searchResult->collisions += lp->collisions;

        if(lp->found){
            searchResult->found = true;
            searchResult->atIndex = lp->atIndex;
        }
    }

    if(searchResult->found){
        a[searchResult->atIndex] = i;
    }

    return searchResult;
}

SearchResult* get(int a[], int length, int i){
    SearchResult* searchResult = new SearchResult;
    searchResult->found = false;
    searchResult->atIndex = -1;
    searchResult->collisions = 0;
    int address = i % length;

    if(a[address] == i){
        searchResult->found = true;
        searchResult->atIndex = address;
    } else {
        searchResult->collisions++;
    }

    if(!searchResult->found){
        //double hash
        int p = prevPrime(length);
        address = p - i%p;
        if(a[address] == i){
            searchResult->found = true;
            searchResult->atIndex = address;
        } else {
            searchResult->collisions++;
        }
    }

    if(!searchResult->found){
        //quadratic probe
        SearchResult* qp = quadraticProbe(a, length, i, address);
        searchResult->collisions += qp->collisions;
        if(qp->found){
            searchResult->found = true;
            searchResult->atIndex = qp->atIndex;
        }

        qp = 0;
        delete qp;
    }

    if(!searchResult->found){
        //linear probe
        SearchResult* lp = linearProbe(a, length, i);
        searchResult->collisions += lp->collisions;

        if(lp->found){
            searchResult->found = true;
            searchResult->atIndex = lp->atIndex;
        }
    }

    return searchResult;
}
