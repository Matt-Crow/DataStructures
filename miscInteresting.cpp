bool containsDelete(string s){
    bool ret = false;
    string checking = "delete";
    int onChar = 0;

    if(s.length() < checking.length()){
        return false;
    }

    //                 something is going wrong with this part
    for(int i = 0; i < s.length() - checking.length() && !ret; i++){
        if(s[i] == checking[0]){
            ret = true;
            for(int j = i; j < s.length() && onChar < checking.length() && ret; j++){
                ret = s[j] == checking[onChar];
                onChar++;
            }
        }
    }

    return ret;
}

bool containsNum(string s){
    bool ret = false;
    for(int i = 0; i < s.length() && !ret; i++){
        ret = isdigit(s[i]);
    }
    return ret;
}

int extractNum(string s){
    int ret = 0;
    for(int i = 0; i < s.length(); i++){
        if(isdigit(s[i])){
            ret *= 10;
            ret += s[i] - 48; //account for ASCII conversion
        }
    }
    return ret;
}

void commaRecur(long long num){
    if(num < 1000){
        cout << num;
    } else {
        commaRecur(num / 1000);
        cout << ',';
        if(num % 1000 < 10){
            cout << "00";
        } else if(num % 1000 < 100){
            cout << "0";
        }
        cout << num % 1000;
    }
}

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
