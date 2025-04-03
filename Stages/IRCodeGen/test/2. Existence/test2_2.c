// Function calling before declaration 

int main(){
    func(); // error: implicit declaration of function 'func'
    return 0;
}

void func(){
    int a = 1;
    return;
}