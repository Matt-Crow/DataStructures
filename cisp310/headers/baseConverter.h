#ifndef BASE_CONVERTER
#define BASE_CONVERTER

/*
Returns the integer
value of c when it
is interprated as a
hexadecimal digit
*/
int intVal(char c);

/*
Converts the given string ip (written in
base fromBase) to a decimal integer.
*/
int calcIntValue(char ip[], int fromBase);

/*
Converts the given number string from the first base
to the second. Note the returned value is allocated on
the heap, and must therefore be manually freed.
*/
char* convert(char ip[], int fromBase, int toBase);

int testBaseConverter();

#endif
