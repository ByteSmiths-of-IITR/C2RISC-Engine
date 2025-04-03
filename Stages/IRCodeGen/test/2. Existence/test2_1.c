// using less than required arguments in function call
int func(int a, char ch){
    {
        int a = 2;
    }
    return a;
}

int main(){
    int a;
    func(a); // error: too few arguments to function ‘func’
    return 0;
}