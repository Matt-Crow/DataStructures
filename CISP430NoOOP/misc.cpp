char toChar(int i){
    //supports hexadecimal
    char ret = (char)(48 + i);
    if(i >= 10){
        ret = (char)(65 + i - 10);
    }
    return ret;
}
