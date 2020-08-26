#ifndef BASE_CONVERTER
#define BASE_CONVERTER

const int MAX_DIGITS = 32; // may change this to a parameter to functions later
const char ALPHABET[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
const int MAX_BASE = sizeof(ALPHABET) / sizeof(char);

char* sanitize(char* src);

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

char* decimalIntToBase(int decimalValue, int toBase);

/*
Converts the given number string from the first base
to the second. Note the returned value is allocated on
the heap, and must therefore be manually freed.
*/
char* convert(char ip[], int fromBase, int toBase);

int testBaseConverter();

#endif
