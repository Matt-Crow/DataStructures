#ifndef BASE_CONVERTER
#define BASE_CONVERTER

/*
Converts the given number string from the first base
to the second. Note the returned value is allocated on
the heap, and must therefore be manually freed.
*/
char* convert(char ip[], int fromBase, int toBase);

int testBaseConverter();

#endif
