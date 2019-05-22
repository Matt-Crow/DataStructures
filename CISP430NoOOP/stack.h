#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include "misc.h"

template <typename T>
struct stack{
    stack<T>* next;
    T value;
};

template <typename T>
void push(stack<T>* &top, T value);

template <typename T>
T pop(stack<T>* &top);

template <typename T>
void print(stack<T>* top, ostream &out);

#endif // STACK_H_INCLUDED
