#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

//temp
void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << i << ": " << a[i] << endl;
    }
}

bool isPrime(int num);
int prevPrime(int num);
int put(int a[], int length, int i);

const int NULL_VALUE = INT_MIN;



int main(){
    int size = 10; //size is supposed to be a prime number
    int a[size];
    ifstream in = ifstream("input.txt");
    int ip;
    int ipCount = 0;
    int collisions;

    for(int i = 0; i < size; i++){
        a[i] = NULL_VALUE; //can't do memset or initializer list
    }

    while(in >> ip && ipCount < size){
        collisions = put(a, size, ip);
        cout << "Inserted " << ip << " into the array, colliding " << collisions << " times." << endl;
        ipCount++;
    }
    in.close();

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

//returns collision count
int put(int a[], int length, int i){
    int collisionCount = 0;
    int address = i%length;
    //cout << "Modulo hash for " << i << " is " << address << endl;
    if(a[address] != NULL_VALUE){
        //slot is not empty
        collisionCount++;
        int p = prevPrime(length);
        //cout << "need to double hash" << endl;
        address = p - i%p;
        //cout << "new address is " << address << endl;
    }
    if(a[address] != NULL_VALUE){
        collisionCount++;
        //cout << "need to quadratic probe" << endl;
        int newAddr = 0;
        for(int i = 0; i < 3; i++){
            newAddr = (address + i * i)%length;
            if(a[newAddr] == NULL_VALUE){
                address = newAddr;
                //cout << "Yay! Quad probe found " << newAddr << endl;
                i = 3; //breaks out of loop
            } else {
                collisionCount++;
            }
        }
    }
    if(a[address] != NULL_VALUE){
        //cout << "need to linear probe" << endl;
        address = 0;
        while(address < length && a[address] != NULL_VALUE){
            address++;
            collisionCount++;
        }
    }
    if(address < length){
        a[address] = i;
    } else {
        cout << "Cannot insert " << i << " into array. There are no empty indexes." << endl;
    }

    return collisionCount;
}
