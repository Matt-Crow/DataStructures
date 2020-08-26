#ifndef BASE_CONVERTER
#define BASE_CONVERTER

//https://stackoverflow.com/questions/17764661/multiple-definition-of-linker-error
extern const int MAX_DIGITS;
extern const char ALPHABET[];
extern const int MAX_BASE;

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
