#include <iostream>

void radixSort(int a[], int length, int tenToSomePow){
    bool higherPow = false;
    int b[length];

    //https://www.geeksforgeeks.org/radix-sort/
    int count[10] = {0}; //number of occurrences of each number (0-9)

    for(int i = 0; i < length; i++){
        //       significant digit
        if(!higherPow && a[i] > tenToSomePow / 10){
            higherPow = true;
            //will need to sort again
        }
        count[(a[i]/tenToSomePow)%10]++;
    }

    //now that we know the number of times each digit occurs,
    //we need to mark which index each digit starts at
    for(int i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    for(int i = length - 1; i >= 0; i--){
        b[count[(a[i]/tenToSomePow)%10] - 1] = a[i];
        count[(a[i]/tenToSomePow)%10]--;
        // O... K...
    }

    for(int i = 0; i < length; i++){
        a[i] = b[i];
    }

    if(higherPow){
        radixSort(a, length, tenToSomePow * 10);
    }
}

void reverseArray(int a[], int length){
    int temp;
    for(int i = 0; i < length / 2; i++){
        temp = a[i];
        a[i] = a[length - i - 1];
        a[length - i - 1] = temp;
    }
}

void radixSort(int a[], int length, bool ascending){
    radixSort(a, length, 1);
    if(!ascending){
        reverseArray(a, length);
    }
}

void print(int a[], int length){
    for(int i = 0; i < length; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}
