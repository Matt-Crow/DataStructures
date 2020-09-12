#ifndef BASE
#define BASE

/*
The system archetecture,
dictating how many bits
will be stored in a binary
string. This is usually
(2^n) * 8 for some integer
n 0, 1, or 2
*/
extern const int SYS_ARCH;

int charToInt(char character, const char* alphabet, int alphabetLength);
char intToChar(int decimal, const char* alphabet, int alphabetLength);

char* newStr(int length, char defaultChar);
int delStr(char** str);

char* parseStr(char* str, char* initializer(), int charToIdxFunc(char), char intToCharFunc(int));
int strToInt(char* str, int base, int intVal(char));
char* intToStr(int value, int base, char* initializer(), char intToCharFunc(int));

#endif
