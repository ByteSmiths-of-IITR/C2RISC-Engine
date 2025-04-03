// function and variable name collision

int func = 10;

int func(){ // error: ‘func’ redeclared as different kind of symbol
    int x = 10;
    return x;
}

int main(){
    int func = 30; // no error
    return 0;
}