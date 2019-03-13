/*
int sumRecur(int num){
    if(num < 10){
        return num;
    } else {
        return sumRecur(num / 10 + num % 10);
    }
}*/

int sumRecur(int num, int digits){
    if(digits == 0){
        return num;
    } else {
        return num % 10 + sumRecur(num / 10, digits - 1);
    }
}

int sumRecur(int num){
    int numDigits = 0;
    int absNum = (num >= 0) ? num : -num;
    int divNum = absNum;
    while(divNum > 0){
        numDigits++;
        divNum /= 10;
    }

    //      preserves sign (+-) of original number
    return (num / absNum) * sumRecur(absNum, numDigits);
}

