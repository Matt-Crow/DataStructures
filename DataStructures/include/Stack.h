#ifndef STACK_H
#define STACK_H


template <class T>
class Stack
{
    public:
        Stack<T>();
        ~Stack<T>();
        void push(T val);
        T pop();
    private:
        Stack<T>* top;
};

#endif // STACK_H
