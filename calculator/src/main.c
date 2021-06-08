#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parser.h"
#include "evaluator.h"

int main(){
    int maxIp = 50;
    char ip[maxIp];

    printf("%s", "Enter a math expression: ");
    fgets(ip, maxIp, stdin);
    char* nl = strchr(ip, '\n');
    if(nl){
        *nl = '\0';
    }

    printf("You entered \"%s\"\n", ip);

    char* postfix = toPostfix(ip);
    printf("As postfix: \"%s\"\n", postfix);

    printf("%s = %d\n", ip, evaluatePostfix(postfix));

    free(postfix);
    postfix = 0;

    return 0;
}
