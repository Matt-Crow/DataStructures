#ifndef HEX
#define HEX

extern const int HEX_LEN;
extern const char HEX_ALPHABET[];
extern const int HEX_ALPHABET_SIZE;

int hexIdx(char c);
char intToHexChar(int i);

char* newHex();
int deleteHex(char** hexStr);

char* toHexStr(char* str);

int hexStrToInt(char* hexStr);



int testHex();

#endif
