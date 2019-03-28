#include<iostream>
#include<fstream>

using namespace std;

void quickSort(int a[], int start, int end);
int partition(int a[], int start, int end);
void print(int a[], int length);
void pad5(int a[], int length);

struct q{
    q* next;
    int value;
}; //queue is reserved

struct stackFrame{
    stackFrame* next;
    int value;
};

struct masterQ{
    q* head;
    q* tail;
};

masterQ* newMasterQ();
void enqueue(masterQ* master, int val);
int dequeue(masterQ* master);

void push(stackFrame*&f, int val);
int pop(stackFrame*&f);

void radixSort(int a[], int length, bool ascending);
void radixSort(int a[], int length, int tenToSomePow);
void posNegSort(int a[], int length);

int useQuickSort(){
    int length = 0;
    int i;
    int idx = 0;
    ifstream ip = ifstream("quickSortIp.txt");
    while(ip >> i){
        length++;
    }
    ip.close();

    int a[length];
    ip = ifstream("quickSortIp.txt");
    while(ip >> i){
        a[idx] = i;
        idx++;
    }

    cout << "Before: " << endl;
    print(a, length);
    quickSort(a, 0, length - 1);
    cout << "After: " << endl;
    print(a, length);
    cout << "Padding..." << endl;
    pad5(a, length);
    print(a, length);
    cout << "Radix sort: " << endl;
    radixSort(a, length, false);
    print(a, length);

    ofstream out = ofstream("quickSortIp.txt");
    for(int i = 0; i < length; i++){
        out << a[i] << " ";
    }

    return 0;
}



void quickSort(int a[], int start, int end){
    if(start < end){
        int mid = partition(a, start, end);
        quickSort(a, start, mid - 1);
        quickSort(a, mid + 1, end);
    }
}
int partition(int a[], int start, int end){
    int pivot = a[end];
    int i = start - 1;
    int temp;
    for(int j = start; j <= end - 1; j++){
        if(a[j] >= pivot){
            i++;
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
    }
    temp = a[i + 1];
    a[i + 1] = a[end];
    a[end] = temp;
    return i + 1;
}
/*
void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << "#" << i + 1 << ": " << a[i] << endl;
    }
}*/
void pad5(int a[], int length){
    int numDigits = 0;
    int tenPow = 1;
    while(a[0] / tenPow != 0){
        numDigits++;
        tenPow *= 10;
    }
    tenPow /= 10;

    int sign;
    for(int i = 1; i < length; i++){

        while(a[i] / tenPow == 0){
            sign = abs(a[i]) / a[i];
            a[i] = abs(a[i]) * 10 + 5;
            a[i] *= sign;
        }
    }
}

//#############################################
//RADIX SORT STUFF
//PRETTY MUCH THE SAME AS LAST ASSIGNMENT
//#############################################
/*
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

    //a is sorted by absolute value,
    //so now I need to put all the negatives at the front,
    //and positives at the back

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
*/
