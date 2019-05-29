#ifndef HASHARRAY_H
#define HASHARRAY_H

struct searchResult{
    bool found;
    int atIndex;
    int collisions;
};

class HashArray
{
    public:
        HashArray(int size);
        ~HashArray();
        searchResult* put(int val);
        searchResult* get(int val);
        void print();
        static int test();
    private:
        int size;
        int** a; //array of int pointers
        searchResult* quadraticProbe(int fromIndex, int searchFor);
        searchResult* qpForEmpty(int fromIndex);
};

#endif // HASHARRAY_H
