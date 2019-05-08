#include <iostream>
#include <fstream>

using namespace std;

//temp
void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << i << ": " << a[i] << endl;
    }
}

void put(int a[], int length, int i);

const int NULL_VALUE = 0;



int main(){
    int size = 10;
    int a[size] = {NULL_VALUE};
    ifstream in = ifstream("input.txt");
    int ip;
    int ipCount = 0;

    while(in >> ip && ipCount < size){
        put(a, size, ip);
        ipCount++;
    }
    in.close();

    print(a, size);
    return 0;
}
/*
If you are still colliding, use linear probing.
At the end of each insert,
display the number of collisions.
Also,
allow the user to search for a value by prompting the user.
Use the same set of hash functions to look for the item.
If the item has not been found,
then display not in the list.
*/
void put(int a[], int length, int i){
    int collisionCount = 0;
    int address = i%length;
    cout << "Modulo hash for " << i << " is " << address << endl;
    if(address >= length || a[address] != NULL_VALUE){
        //slot is not empty
        collisionCount++;
        cout << "need to double hash" << endl;
        address = address - i%address;
        cout << "new address is " << address << endl;
    }
    if(address >= length || a[address] != NULL_VALUE){
        collisionCount++;
        cout << "need to quadratic probe" << endl;
        int newAddr = 0;
        for(int i = 0; i < 3; i++){
            newAddr = (address + i * i)%length;
            if(a[newAddr] == NULL_VALUE){
                address = newAddr;
                cout << "Yay! Quad probe found " << newAddr << endl;
                i = 3; //breaks out of loop
            } else {
                collisionCount++;
            }
        }
    }
    if(address >= length || a[address] != NULL_VALUE){
        cout << "need to linear probe" << endl;
        address = 0;
        while(address < length && a[address] != NULL_VALUE){
            address++;
            collisionCount++;
        }
    }
    if(address < length){
        a[address] = i;
    } else {
        cout << "Cannot insert " << i << "into array. There are no empty indexes." << endl;
    }

    //return collisionCount;
}
