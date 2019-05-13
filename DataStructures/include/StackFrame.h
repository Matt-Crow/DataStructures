#ifndef STACKFRAME_H
#define STACKFRAME_H


template <class T>
class StackFrame
{
    public:
        StackFrame(T data);
        ~StackFrame();
        T get();
    private:
        T data;
        StackFrame<T>* prev;
};

#endif // STACKFRAME_H
