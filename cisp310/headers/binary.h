#ifndef BINARY
#define BINARY

/*
The system archetecture,
dictating how many bits
will be stored in a binary
string. This is usually

(2^n) * 8 for some integer
n 0, 1, or 2

*/
extern const int SYS_ARCH;

/*
Character array, just '0' and '1'.
Used to convert ints to chars
*/
extern const char BIN_ALPHABET[];

/*
Not really needed, but this gives the
length of BIN_ALPHABET
*/
extern const int BIN_ALPHABET_SIZE;

int testBinary();

/*
Converts the given binary character
to its integer value, or -1 if
the given character is invalid
*/
int binCharToInt(char binChar);

/*
Creates a new binary string.
Note this is allocated on the
heap, and must therefore be
freed to prevent memory leaks.
*/
char* newBinStr();

/*
Converts the given cString into
a binary string, ensuring only
valid characters are included,
and the binary string is of
appropriate length.
As per newBinStr, the returned
value is heap allocated.
*/
char* toBinStr(char* cString);

char* intToBinStr(int val);

/*
Frees the given pointer to a binary
string, and realigns the pointer to
null. Returns whether or not anything
was freed.
*/
int deleteBinStr(char** binStr);

/*
Calculates the integer value of
the given binary string.
*/
int binStrToInt(char* binStr);

char* binaryAdd(char* binString1, char* binString2);

#endif
