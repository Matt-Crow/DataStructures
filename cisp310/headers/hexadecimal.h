#ifndef HEX
#define HEX

extern const int HEX_LEN;
extern const char HEX_ALPHABET[];
extern const int HEX_ALPHABET_SIZE;

int hexIdx(char c);
char* newHex();
char* toHexStr(char* str);
int deleteHex(char** hexStr);

int testHex();

#endif
