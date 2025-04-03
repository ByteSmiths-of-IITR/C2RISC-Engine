// function and function name collision

int func1(){
    int a = 10;
    return a;
}

float func1(){ // error: conflicting types for ‘func1’; have ‘float()’
    float a = 10.0;
    return a;
}

int func1(int x){ // error: redefinition of ‘func1’
    return x;
}

int main(){
    return 0;
}