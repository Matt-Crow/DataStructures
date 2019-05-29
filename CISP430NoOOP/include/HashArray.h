#ifndef HASHARRAY_H
#define HASHARRAY_H

struct searchResult{
    bool found;
    int atIndex;
    int collisions;
};

template <class T>
class HashArray
{
    public:
        HashArray(int size);
        ~HashArray();
        searchResult* put(T val);
        searchResult* get(T val);
        void print();
        static int test();
    private:
        int size;
        T** a; //array of pointers
};

template class HashArray<int>;

#endif // HASHARRAY_H
