// union existence 
int main(){
    union U obj; // error: storage size of ‘obj’ isn’t known
    return 0;
}

union U{
    int a;
    int b;
}; 