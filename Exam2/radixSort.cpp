#include <iostream>
#include <cstdlib>

using namespace std;

struct q{
    q* next;
    int value;
}; //queue is reserved

struct stackFrame{
    stackFrame* next;
    int value;
};

//could have sworn I'd done this before
struct masterQ{
    q* head;
    q* tail;
};

masterQ* newMasterQ();
void enqueue(masterQ* master, int val);
int dequeue(masterQ* master);
void printQueue(masterQ* master);

void push(stackFrame*&f, int val);
int pop(stackFrame*&f);

void radixSort(int a[], int length, bool ascending);
void radixSort(int a[], int length, int tenToSomePow);
void posNegSort(int a[], int length);
void print(int a[], int length);

int useRadixSort(){
    //program is already big. Don't want to do array generator
    int a[] = {55, -9, 32, 11111, -5};
    int b[] = {55, -9, 32, 11111, -5};

    cout << "before: " << endl;
    print(a, 5);
    radixSort(a, 5, true);
    cout << "After: " << endl;
    print(a, 5);
    cout << "Before: " << endl;
    print(b, 5);
    radixSort(b, 5, false);
    cout << "After: " << endl;
    print(b, 5);

    return 0;
}

//lazy, I know
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


//stack stuff
void push(stackFrame*&f, int val){
    stackFrame* newF = new stackFrame;
    newF->next = f;
    newF->value = val;
    f = newF;
}
int pop(stackFrame*&f){
    int ret = 0;
    if(f){
        ret = f->value;
        f = f->next;
    }
    return ret;
}


//radix stuff down here
void radixSort(int a[], int length, bool ascending){
    radixSort(a, length, 1);
    posNegSort(a, length);
    if(!ascending){
        reverseArray(a, length);
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
        if(!higherPow && abs(a[i]) > tenToSomePow / 10){
            higherPow = true;
            //will need to sort again
        }
        //              gets the digit we are checking
        enqueue(sigFigs[(abs(a[i])/tenToSomePow)%10], a[i]);
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

void posNegSort(int a[], int length){
    /*
    a is sorted by absolute value,
    so now I need to put all the negatives at the front,
    and positives at the back
    */
    stackFrame* neg = 0;
    masterQ* pos = newMasterQ();

    for(int i = 0; i < length; i++){
        if(a[i] >= 0){
            enqueue(pos, a[i]);
        } else {
            push(neg, a[i]);
        }
    }
    int aIdx = 0;
    while(neg){
        a[aIdx] = pop(neg);
        aIdx++;
    }
    while(pos->head){
        a[aIdx] = dequeue(pos);
        aIdx++;
    }
    delete neg;
    delete pos;
}

/*
void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}
*/
