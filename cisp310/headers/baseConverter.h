#ifndef BASE_CONVERTER
#define BASE_CONVERTER

//https://stackoverflow.com/questions/17764661/multiple-definition-of-linker-error
extern const char* HEX_TO_BIN_TABLE[];

/*
Converts the given string ip (written in
base fromBase) to a decimal integer.
*/
//int calcIntValue(char ip[], int fromBase);

//char* decimalIntToBase(int decimalValue, int toBase);

/*
Converts the given number string from the first base
to the second. Note the returned value is allocated on
the heap, and must therefore be manually freed.
*/
//char* convert(char ip[], int fromBase, int toBase);

const char* hexCharToBinStr(char c);
char binChunkToHexChar(char* chunk);
char* hexStrToBinStr(char* hexStr);
char* binStrToHexStr(char* binStr);

int testBaseConverter();

#endif
