#include <iostream>


struct q{
    q* next;
    int value;
}; //queue is reserved

//could have sworn I'd done this before
struct masterQ{
    q* head;
    q* tail;
};

masterQ* newMasterQ();
void enqueue(masterQ* master, int val);
int dequeue(masterQ* master);
void printQueue(masterQ* master);

void radixSort(int a[], int length, bool ascending);
void radixSort(int a[], int length, int tenToSomePow);
void print(int a[], int length);






void reverseArray(int a[], int length){
    int temp;
    for(int i = 0; i < length / 2; i++){
        temp = a[i];
        a[i] = a[length - i - 1];
        a[length - i - 1] = temp;
    }
}











// Queue stuffs down here
masterQ* newMasterQ(){
    masterQ* ret = new masterQ;
    ret->head = 0;
    ret->tail = 0;
    return ret;
}

void enqueue(masterQ* master, int val){
    q* newRear = new q;
    newRear->value = val;
    newRear->next = 0;

    if(!master->head){
        //no elements
        master->head = newRear;
        master->tail = newRear;
    } else {
        master->tail->next = newRear;
        master->tail = newRear;
    }
}

int dequeue(masterQ* master){
    int ret = 0; //what should I default to if no elements?
    if(master->head){
       ret = master->head->value;
       master->head = master->head->next;

       if(!master->head){
            //no more elements
            master->tail = 0;
       }
    }
    return ret;
}

void printQueue(masterQ* master){
    q* current = master->head;
    while(current){
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

//radix stuff down here
void radixSort(int a[], int length, bool ascending){
    radixSort(a, length, 1);
    if(!ascending){
        //???
    }
}
void radixSort(int a[], int length, int tenToSomePow){
    bool higherPow = false; //wow. c++ is an atheist

    masterQ* sigFigs[10];
    for(int i = 0; i < 10; i++){
        sigFigs[i] = newMasterQ();
    }


    for(int i = 0; i < length; i++){
        //       significant digit
        if(!higherPow && a[i] > tenToSomePow / 10){
            higherPow = true;
            //will need to sort again
        }
        //              gets the digit we are checking
        enqueue(sigFigs[(a[i]/tenToSomePow)%10], a[i]);
    }

    int aIdx = 0;
    for(int i = 0; i < 10; i++){
        while(sigFigs[i]->tail){
            a[aIdx] = dequeue(sigFigs[i]);
            aIdx++;
        }
    }

    if(higherPow){
        radixSort(a, length, tenToSomePow * 10);
    }
}

void print(int a[], int length){
    for(int i = 0; i < length; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}
